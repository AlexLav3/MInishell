#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "../include/pipex.h"

void	pipex_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int		cmd_counter(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	fd_handle(int i, int cmd_count, t_pipex *px)
{
	if (i > 0)
		close(px->prev_fd[0]);
	if (i < cmd_count - 1)
		close(px->pipe_fd[1]);
	if (i < cmd_count - 1)
		px->prev_fd[0] = px->pipe_fd[0];
}

void	which_child(int i, int cmd_count, t_pipex *px, char **cmds, char **envp)
{
	if (i == 0)
		first_child_process(px, cmds[i], envp);
	else if (i == cmd_count - 1)
		last_child_process(px, cmds[i], envp);
	else
		middle_child_process(px, cmds[i], envp);
	if (i > 0)
		close(px->prev_fd[0]);
	if (i < cmd_count - 1)
		close(px->pipe_fd[1]);
}

void	create_pipes(char **cmds, char **envp)
{
	int		i;
	int		cmd_count;
	t_pipex	px;
	
	i = -1;
	px.pipe_fd[0] = -1;
	px.pipe_fd[1] = -1;
	cmd_count = cmd_counter(cmds);
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1)
			if (pipe(px.pipe_fd) == -1)
				pipex_error("Error creating pipe");
		px.pid = fork();
		if (px.pid == -1)
			pipex_error("Fork failed");
		if (px.pid == 0)
		{
			which_child(i, cmd_count, &px, cmds, envp);
			exit(0);
		}
		fd_handle(i, cmd_count, &px);
	}
	close_pipes_and_wait(&px);
}

void	first_child_process(t_pipex *px, char *cmd, char **envp)
{
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 failed for first child");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, envp);
}

void	last_child_process(t_pipex *px, char *cmd, char **envp)
{
	if (dup2(px->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 failed for last child");
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, envp);
}

void	middle_child_process(t_pipex *px, char *cmd, char **envp)
{
	if (dup2(px->prev_fd[0], STDIN_FILENO) == -1)
		pipex_error("dup2 failed for intermediate child (stdin)");
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("dup2 failed for intermediate child (stdout)");
	close(px->prev_fd[0]);
	close(px->pipe_fd[1]);
	execute_cmd(cmd, envp);
	exit(0);
}

void	close_pipes_and_wait(t_pipex *px)
{
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	while (wait(NULL) > 0)
		;
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		pipex_error("split");
	path = get_path(args[0], envp);
	if (!path)
		pipex_error("command not found");
	if (execve(path, args, envp) == -1)
		pipex_error("execve");
}

char	*get_path(char *cmd, char **envp)
{
	int		i = 0;
	char	*full_path = NULL;
	char	**paths;

	while (envp[i] && strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
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

int	main(int ac, char **av, char **envp)
{
	if (ac < 2)
	{
		write(2, "Usage: ./pipex \"cmd1\" \"cmd2\" ...\n", 33);
		return (1);
	}
	create_pipes(&av[1], envp);
	return (0);
}
