/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:21:24 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/30 15:02:18 by fnagy            ###   ########.fr       */
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
		// printf("tokens com: %s\n", tokens->com);
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

//created a sep function becuase we need to free cmd and exp after use. 
static char	*expand_variable(char *token_com, char *exp, char *cmd, char *pos)
{
	char	*prefix;
	char	*result;

	prefix = strndup(token_com, pos - token_com);
	if (!prefix)
		return (free(exp), free(cmd), NULL);
	result = ft_strjoin(prefix, exp);
	free(prefix);
	free(exp);
	free(cmd);
	return (result);
}

char	*toks_to_args(t_token *tokens, char *cmd, t_shell *shell)
{
	char	*pos;
	char	*exp;
	char	*res;

	cmd = ft_strdup(tokens->com);
	if (!cmd)
		return (free(cmd), NULL);
	// printf("literal: %d\n", tokens->literal);
	if (!tokens->literal && ft_strchr(tokens->com, '$') != NULL)
	{
		pos = ft_strchr(tokens->com, '$');
		exp = handle_dollar(ft_strchr(tokens->com, '$'), shell);
		if (exp)
			return (expand_variable(tokens->com, exp, cmd, pos));
	}
	return (cmd);
}

static char	*get_env_value(t_shell *shell, char *name)
{
	int		idx;
	char	*env;
	char	*val;

	idx = search_env(shell, name);
	if (idx < 0)
		return (ft_strdup(""));
	env = shell->env_var[idx];
	val = ft_strchr(env, '=');
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val + 1));
}

char	*handle_dollar(char *cmd, t_shell *shell)
{
	int		idx;
	int		i;
	char	*prefix;

	i = 0;
	if (ft_strcmp(cmd, "$?") == 0)
		return (ft_itoa(shell->exit_stat));
	while (cmd[i])
	{
		if (cmd[i] == '$')
			break ;
		i++;
	}
	prefix = ft_substr(cmd, 0, i);
	idx = search_env(shell, cmd + (i + 1));
	if (idx >= 0)
	{
		shell->env_idx = idx;
		return (process_env_var(cmd, shell, prefix, i));
	}
	else
		return (free(prefix), ft_strdup(""));
}
