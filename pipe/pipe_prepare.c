/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:48:38 by ferenc            #+#    #+#             */
/*   Updated: 2025/04/16 14:22:09 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	token_has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->com && ft_strcmp(tokens->com, "|") == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

static char *str_join_free(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

char	**make_args_pipes(t_token *tokens)
{
	char	**cmds;
	char	*cmd_str;
	int		i;

	cmds = malloc(sizeof(char *) * (size_args(tokens) + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	cmd_str = NULL;
	while (tokens)
	{
		if (tokens->com && tokens->com[0] != '\0')
		{
			if (ft_strncmp(tokens->com, "|", 2) == 0)
			{
				cmds[i++] = cmd_str;
				cmd_str = NULL;
			}
			else
			{
				if (cmd_str)
					cmd_str = str_join_free(cmd_str, ft_strjoin(" ", tokens->com));
				else
					cmd_str = ft_strdup(tokens->com);
			}
		}
		tokens = tokens->next;
	}
	if (cmd_str)
		cmds[i++] = cmd_str;
	cmds[i] = NULL;
	return (cmds);
}


// void print_cmds(char **cmds)
// {
// 	int i = 0;
// 	while (cmds[i])
// 	{
// 		printf("cmds[%d]: %s\n", i, cmds[i]);
// 		i++;
// 	}
// }