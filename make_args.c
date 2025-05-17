/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:21:24 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 08:59:48 by elavrich         ###   ########.fr       */
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

	cmd = ft_strdup(tokens->com);
	if (!cmd)
		return (free(cmd), NULL);
	if (!tokens->literal && ft_strchr(tokens->com, '$') != NULL )
	{
		pos = ft_strchr(tokens->com, '$');
		exp = handle_dollar(ft_strchr(tokens->com, '$'), shell);
		if (exp)
			return (ft_strjoin(strndup(tokens->com, pos - tokens->com),
					exp));
	}
	return (cmd);
}

char	*handle_dollar(char *cmd, t_shell *shell)
{
	int		idx;
	char	*env;
	char	*value;
	int		i;

	i = 0;
	if (!cmd || cmd[1] == '?')
		return (ft_strdup(cmd));
	while (cmd[i])
	{
		if (cmd[i] == '$')
			break ;
		i++;
	}
	idx = search_env(shell, cmd + (i + 1));
	if (idx >= 0)
	{
		env = shell->env_var[idx];
		value = ft_strchr(env, '=');
		if (!value)
			return (ft_strdup(""));
		return (ft_strdup(value + 1));
	}
	else
		return (ft_strdup(""));
}

int	simple_word(t_token **tokens, char *str, int i)
{
	char	*word;
	int		start;

	start = i;
	while (str[i] && str[i] != ' ' && !is_meta(str[i]) && str[i] != '"'
		&& str[i] != '\'' && str[i] != '\0')
		i++;
	word = ft_substr(str, start, i - start);
	add_token(tokens, word, 0);
	return (i);
}
