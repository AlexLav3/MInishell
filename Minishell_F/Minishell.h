/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/18 10:24:15 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/src/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_token
{
	char			*com;
	struct s_token	*next;
	// struct s_token	*prev; //maybe will be needed
}					t_token;

typedef struct s_shell
{
	char			**env_var;
	char			*pwd;
	pid_t			pid1;
	int				pipe_fd[2];
	int				prev_fd[2];
	pid_t			pid;
	char			**av;
	char			**envp;
	int				exit;
}					t_shell;

void	init_shell(t_shell *shell, char **envp);
void	take_comm(t_token **tokens, t_shell *shell);
void	input(char *str, t_token **tokens);
char	**make_args(t_token *tokens);
char	*set_pwd(t_shell *shell);

void	execute_single_cmd(char **cmd, t_shell *shell);

// split tokens
int		separator_len(char *s);
void	insert_after_token(t_token *prev, char *word);
void	split_and_insert_parts(t_token *curr, int i, int len);
int		split_token_content(t_token *curr);
void	split_tokens(t_token **tokens);

// get_path
void	process_commands(char *command, t_token **tokens, t_shell *shell);
char	*get_cmd_path(char *cmd, t_shell *shell);
void	single_cmd(char *command, t_token **tokens, t_shell *shell, char **cmd);
void	pipe_cmds(char *command, t_token **tokens, t_shell *shell, char **cmds);

// pipes utils
int		token_has_pipe(t_token *tokens);
char	**make_args_pipes(t_token *tokens);
char	*get_path_in(char *cmd, t_shell *px);
char	*str_join_free(char *s1, char *s2);
void	process_token(t_token *token, char **cmd_str, char **cmds, int *i);

// pipes
void	pipex_error(char *msg);
int		cmd_counter(char **cmds);
void	fd_handle(int i, int cmd_count, t_shell *px);
void	which_child(int i, int cmd_count, t_shell *px, char **cmds);
void	create_pipes(char **cmds, t_shell *shell);
void	first_child_process(t_shell *px, char *cmd);
void	last_child_process(t_shell *px, char *cmd);
void	middle_child_process(t_shell *px, char *cmd);
void	close_pipes_and_wait(t_shell *px);
void	execute_cmd(char *cmd, t_shell *px);

//builtin
bool	handle_builtin(char **cmd, t_shell *shell);
void	builtin_cd(char **cmd, t_shell *shell);
void	builtin_pwd(char **cmd, t_shell *shell);
void	ft_export(char **cmd, t_shell *shell);
void	builtin_unset(char **cmd, t_shell *shell);

//env variables
char	**copy_envp(char **envp);
void	print_env(t_shell shell);
void	add_env(t_shell *shell, char *var);
int		search_env(t_shell *shell, char *var);
void	update_env(t_shell *shell, char *var, char *name);
//signals
void	sig_handle(int sig);
void	setup_sig(void);

//close & free
void	close_free(t_token *tokens, t_shell *shell);
void	free_array(char **arr);
void	deallocate(t_token **root);
bool	check_for_exit(char *command);
void	ft_exit(t_shell *shell);

//for list tokens
t_token	*new_token(char *word);
void	add_token(t_token **head, char *word);

//utils
int		is_sep(char c);
char	*join_path(char *dir, char *cmd);
int		size_args(t_token *tokens);
//testing
void	print_list(t_token *tokens);

#endif