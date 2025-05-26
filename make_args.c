/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:21:24 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/26 11:56:54 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//cat test.txt | grep "42" | sort | wc -l (testing)
char	**make_args(t_token *tokens, t_shell *shell)
{
	char	**cmd;
	char	*pos;
	int		i;
	char	*expanded;

	i = 0;
	cmd = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmd || !tokens)
		return (NULL);
	while (tokens)
	{
		printf("tokens com: %s\n", tokens->com);
		if (tokens->com && tokens->com[0] != '\0')
		{
			cmd[i] = toks_to_args(tokens, *cmd, shell);
			i++;
		}
		tokens = tokens->next;
	}
	cmd[i++] = NULL;
	return (cmd);
}

char	*toks_to_args(t_token *tokens, char *cmd, t_shell *shell)
{
	char	*pos;
	char	*exp;
	char	*res;

	cmd = ft_strdup(tokens->com);
	if (!cmd)
		return (free(cmd), NULL);
	printf("literal: %d\n", tokens->literal);
	if (!tokens->literal && ft_strchr(tokens->com, '$') != NULL)
	{
		pos = ft_strchr(tokens->com, '$');
		exp = handle_dollar(ft_strchr(tokens->com, '$'), shell);
		if (exp)
			return (ft_strjoin(strndup(tokens->com, pos - tokens->com),
					exp));
	}
	return (cmd);
}

static char	*expand_env(char *cmd, t_shell *shell, int i)
{
	int		idx;
	char	*value;
	char	*suf;
	char	*prefix;
	char	*tmp;

	prefix = ft_substr(cmd, 0, i);
	idx = search_env(shell, cmd + (i + 1));
	if (idx < 0) // if it comes back with -1
		return (free(prefix), ft_strdup(""));
	value = ft_strchr(shell->env_var[idx], '=' );
	if (!value)
		return (free(prefix), ft_strdup(""));
	value++;
	suf = ft_strdup(cmd + (i + 1) + shell->var_len);
	if (ft_strchr(suf, '$'))
	{
		tmp = handle_dollar(suf, shell); // free old suf and not lose pointer
		free(suf);
		suf = tmp;
	}
	return (join_and_free(prefix, join_and_free(ft_strdup(value), suf)));
}

char	*handle_dollar(char *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || cmd[1] == '?')
		return (ft_strdup(cmd));
	printf("cmd here: %s\n", cmd);
	i = 0;
	while (cmd[i])
		if (cmd[i++] == '$')
			break ;
	return (expand_env(cmd, shell, i - 1));
}
