/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:58:49 by ferenc            #+#    #+#             */
/*   Updated: 2025/07/20 19:45:10 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

int	init_cmds_and_group(t_token **tokens, t_shell *shell,
	t_cmd **cmds, t_grouped *grp)
{
	int		cmd_count;
	int		i;

	cmd_count = count_pipes(*tokens);
	*cmds = malloc(sizeof(t_cmd) * cmd_count);
	if (!*cmds)
		return (0);
	i = 0;
	while (i < cmd_count)
		init_cmd(&(*cmds)[i++]);
	*grp = build_group(shell, *cmds, cmd_count, tokens);
	return (cmd_count);
}

void	handle_cmd_failure(t_cmd *cmds, t_token **tokens, t_shell *shell,
			int cmd_count)
{
	int	i;

	if (cmds)
	{
		i = 0;
		while (i < cmd_count)
		{
			free_array(cmds[i].args);
			reset_redirection(&cmds[i]);
			i++;
		}
		free(cmds);
	}
	deallocate(tokens);
	*tokens = NULL;
	shell->exit_stat = 1;
}

void	cleanup_pipe_cmds(t_cmd *cmds, int cmd_count, t_token **tokens,
			t_token *head)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		free_array(cmds[i].args);
		reset_redirection(&cmds[i]);
		i++;
	}
	free(cmds);
	deallocate(&head);
	*tokens = NULL;
}
