/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/06/17 20:37:19 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/src/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define IN_FILE 1
# define OUT_FILE 2

# define EXPAND 3
# define NO_EXP 4

typedef struct token_b
{
	char			*builder;
}					t_token_b;

typedef struct s_token
{
	char			*com;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char			**env_var;
	int				var_len;
	int				exit_stat;
	char			*pwd;
	pid_t			pid1;
	int				pipe_fd[2];
	int				prev_fd[2];
	pid_t			pid;
	char			**av;
	char			**envp;
	int				exit;
	char			*infile;
	char			*outfile;
	int				redir_in;
	int				redir_out;
	int				env_idx;
}					t_shell;

// test run program in program
char				*get_right_path(char *cmd, void *either_shell, int is_pipe);

char				*process_word(char *word, t_shell *shell, int flag);

int					handle_q(t_token_b **tks, char *str, int i, t_shell *shell);
int					simple_word(t_token_b **tks, char *str, int i,
						t_shell *shell);

char				*join_and_free(char *s1, char *s2);
void				heredoc_do(t_shell *shell, char *delimiter);
void				readirs(int dir, t_shell *shell, char *com);

void				init_shell(t_shell *shell, char **envp);
void				take_comm(t_token **tokens, t_shell *shell);
int					input(char *str, t_token **tokens, t_shell *shell);
char				**make_args(t_token *tokens, t_shell *shell);
char				*set_pwd(t_shell *shell);
void				execute_single_cmd(char **cmd, t_shell *shell);

// get_path
void				process_commands(char *command, t_token **tokens,
						t_shell *shell);
char				*get_cmd_path(char *cmd, t_shell *shell);
void				single_cmd(char *command, t_token **tokens, t_shell *shell);
void				pipe_cmds(char *command, t_token **tokens, t_shell *shell);

// pipes utils
int					token_has_pipe(t_token *tokens);
char				**make_args_pipes(t_token *tokens);
char				*get_path_in(char *cmd, t_shell *px);
char				*str_join_free(char *s1, char *s2);
void				process_token(t_token *token, char **cmd_str, char **cmds,
						int *i);

// pipes
void				pipex_error(char *msg);
int					cmd_counter(char **cmds);
void				fd_handle(int i, int cmd_count, t_shell *px);
void				which_child(int i, int cmd_count, t_shell *px, char **cmds);
void				create_pipes(char **cmds, t_shell *shell);
void				first_child_process(t_shell *px, char *cmd);
void				last_child_process(t_shell *px, char *cmd);
void				middle_child_process(t_shell *px, char *cmd);
void				close_pipes_and_wait(t_shell *px);
void				execute_cmd(char *cmd, t_shell *px);

//dollar sign
char				*handle_dollar(char *cmd, t_shell *shell);

// handle redir (COPY_REDIR)
int					handle_redirection_token(t_token *tokens, t_shell *shell);
int					is_redir(const char *s);
int					count_args(t_token *tokens);
int					token_has_redir(t_token *tokens);
char				**parse_args_and_redirs(t_token *tokens, t_shell *shell);
void				apply_redirection(t_shell *shell);
void				execute_single_redir(char **cmd, t_shell *shell);
void				single_cmd_with_redir(char *command, t_token **tokens,
						t_shell *shell);
void				reset_redirection(t_shell *shell);

void				pipe_cmds_with_redir(char *command, t_token **tokens,
						t_shell *shell);
void				handle_last_redir_child(t_shell *shell, t_shell *px,
						char *cmd);
void				handle_first_redir_child(t_shell *shell, t_shell *px,
						char *cmd);
void				strip_redirection_tokens(t_token **tokens);
void				init_pipex(t_shell *px, t_shell *shell);
void				execute_piped_commands(t_shell *px, char **cmds,
						int cmd_count, t_shell *shell);

void				heredoc_child_process(int write_fd, char *delimiter);
void				setup_shell_signals(void);
void				handle_sigint_prompt(int sig);
void				setup_heredoc_signals(void);
void				handle_sigint_heredoc(int sig);

//builtin
bool				handle_builtin(char **cmd, t_shell *shell);
void				builtin_cd(char **cmd, t_shell *shell);
void				builtin_pwd(t_shell *shell);
void				ft_export(char **cmd, t_shell *shell);
void				builtin_unset(char **cmd, t_shell *shell);
int					ft_echo(char **cmd);
void				ft_exit(char **cmd, t_shell *shell);

//builtin utils
int					is_valid_directory(char *path);

//env variables
char				**copy_envp(char **envp, char *new_var);
void				print_env(t_shell shell);
void				add_env(t_shell *shell, char *var);
int					search_env(t_shell *shell, char *var);
void				update_env(t_shell *shell, char *var, char *name);

//close & free
void				close_free(t_token *tokens, t_shell *shell);
void				free_array(char **arr);
void				deallocate(t_token **root);

//for list tokens
t_token				*new_token(char *word);
void				add_token(t_token **head, char *word);

//utils
int					is_meta(char c);
char				*join_path(char *dir, char *cmd);
int					size_args(t_token *tokens);
int					make_tok(t_token **tokens, char *str, int i,
						t_shell *shell);
int					is_pipe(char c);
int					size_cmd_arg(char **cmd);
char				*toks_to_args(t_token *tokens, char *cmd, t_shell *shell);

//var utils
void				set_var(char **cmd, t_shell *shell, char *equal, int i);
int					copy_env_vars(char **dest, char **src, int count);
char				*process_env_var(char *cmd, t_shell *shell, char *prefix,
						int i);

//testing
void				print_list(t_token *tokens);

#endif