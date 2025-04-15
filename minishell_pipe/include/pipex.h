#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	int		prev_fd[2];
	pid_t	pid;
	char	**av;
	char	**envp;
}	t_pipex;

void	pipex_error(char *msg);
int		cmd_counter(char **cmds);
void	fd_handle(int i, int cmd_count, t_pipex *px);
void	which_child(int i, int cmd_count, t_pipex *px, char **cmds, char **envp); //norminette problem, more than 4 args.
void	create_pipes(char **cmds, char **envp);
void	first_child_process(t_pipex *px, char *cmd, char **envp);
void	last_child_process(t_pipex *px, char *cmd, char **envp);
void	middle_child_process(t_pipex *px, char *cmd, char **envp);
void	close_pipes_and_wait(t_pipex *px);
void	execute_cmd(char *cmd, char **envp);
char	*get_path(char *cmd, char **envp);
char	*join_path(char *dir, char *cmd);

#endif