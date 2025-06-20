/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:25:00 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/21 01:04:14 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*get_cmd_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	**envp;

	envp = shell->env_var;
	full_path = NULL;
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
			return (free_array(paths), full_path);
		free(full_path);
	}
	return (free_array(paths), NULL);
}

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*get_right_path(char *cmd, void *either_shell, int is_pipe)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	if (is_pipe)
		return (get_path_in(cmd, (t_shell *)either_shell));
	else
		return (get_cmd_path(cmd, (t_shell *)either_shell));
}
