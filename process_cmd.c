/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:29:16 by ferenc            #+#    #+#             */
/*   Updated: 2025/05/01 16:32:08 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// changed due to REDIR
void	single_cmd(char *command, t_token **tokens, t_shell *shell, char **cmd)
{
	cmd = make_args(*tokens);
	free(command);
	if (!cmd)
	{
		deallocate(tokens);
		return ;
	}
	if (handle_builtin(cmd, shell))
	{
		free_array(cmd);
		deallocate(tokens);
		return ;
	}
	execute_single_cmd(cmd, shell);
	free_array(cmd);
}
// changed due to REDIR
void	pipe_cmds(char *command, t_token **tokens, t_shell *shell, char **cmds)
{
	cmds = make_args_pipes(*tokens);
	free(command);
	if (!cmds)
	{
		deallocate(tokens);
		return ;
	}
	create_pipes(cmds, shell);
	free_array(cmds);
}
// changed due to REDIR
void	process_commands(char *command, t_token **tokens, t_shell *shell)
{
	char	**cmd;
	char	**cmds;
	int		has_pipe;
	int		has_redir;
	
	//print_list(*tokens); // just for testing
	has_pipe = token_has_pipe(*tokens);
	has_redir = token_has_redir(*tokens);
	if (!has_pipe)
	{
		if (has_redir)
			single_cmd_with_redir(command, tokens, shell);
		else
			single_cmd(command, tokens, shell, cmd);
	}
	else
	{
		if (has_redir)
			pipe_cmds_with_redir(command, tokens, shell); // need to be devloped
		else
			pipe_cmds(command, tokens, shell, cmds);		
	}
	deallocate(tokens);
}

void	execute_single_cmd(char **cmd, t_shell *shell)
{
	char	*path;

	if (!cmd[0] || !cmd)
		return ;
	path = get_cmd_path(cmd[0], shell);
	if (!path)
	{
		perror("Command not found");
		return ;
	}
	shell->pid1 = fork();
	if (shell->pid1 == -1)
		perror("fork");
	else if (shell->pid1 == 0)
	{
		if (execve(path, cmd, shell->env_var) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(shell->pid1, NULL, 0);
	free(path);
}

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
