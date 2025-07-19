/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:21:24 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/19 21:28:18 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//cat test.txt | grep "42" | sort | wc -l (testing)
char	**make_args(t_token **tokens, t_shell *shell)
{
	char	**cmd;
	int		i;
	t_token	*tmp;

	i = 0;
	if (!tokens || !*tokens)
		return (NULL);
	cmd = malloc(sizeof(char *) * (size_args(*tokens) + 1));
	if (!cmd)
		return (NULL);
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->com && tmp->com[0] != '\0')
		{
			cmd[i] = toks_to_args(tmp, NULL, shell);
			if (!cmd[i])
			{
				while (i-- > 0)
					free(cmd[i]);
				free(cmd);
				return (NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	*toks_to_args(t_token *tokens, char *cmd, t_shell *shell)
{
	(void)shell;
	free(cmd);
	cmd = ft_strdup(tokens->com);
	if (!cmd)
		return (free(cmd), NULL);
	return (cmd);
}

char	*handle_dollar(char *cmd, t_shell *shell)
{
	int		idx;
	int		i;
	char	*prefix;

	i = 0;
	if (!cmd)
		return (NULL);
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
		shell->env_idx = search_env(shell, cmd + (i + 1));
		return (process_env_var(cmd, shell, prefix, i));
	}
	else
		return (free(prefix), NULL);
}
