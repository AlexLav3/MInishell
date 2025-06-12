/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:21:24 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/11 18:10:45 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"
//cat test.txt | grep "42" | sort | wc -l (testing)
char	**make_args(t_token *tokens, t_shell *shell)
{
	char	**cmd;
	int		i;

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
// this function seems reduntant now
// f:	I think if you would try to added straight to make_args, you would have more than 25 lines. 
//ok but this seems a very bad way to solve it. norminette is not an excuse for bad choices. I'll see if I can come up with something else. 
char	*toks_to_args(t_token *tokens, char *cmd, t_shell *shell)
{
	(void)shell;
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
	if (ft_strcmp(cmd, "$?") == 0)
		return (ft_itoa(shell->exit_stat));
	// if (!cmd || cmd[1] == '?')
	// 	return (ft_strdup(cmd)); // I'll take care of this as discussed.
	while(cmd[i])
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
		return (free(prefix), ft_strdup(cmd));
}
