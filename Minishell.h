/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/28 10:14:07 by ferenc           ###   ########.fr       */
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
	bool			quoted;
	char			*builder;
}					t_token_b;

typedef struct s_token
{
	bool			quoted;
	char			*com;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**args;
	int				redir_in;
	int				redir_out;
	char			*infile;
	char			*outfile;
	int				redir_error;
}					t_cmd;

typedef struct s_pipe_context
{
	t_token			**start;
	t_token			*curr;
	t_token			*prev;
	t_cmd			*cmd;
}					t_pipe_context;

typedef struct s_info
{
	char			*cmd;
	char			**cmds;
	t_token			**tokens;
}					t_info;

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
	int				exit;
	char			*infile;
	char			*outfile;
	int				env_idx;
}					t_shell;

typedef struct s_grouped
{
	t_token			**tokens;
	t_shell			*shell;
	t_cmd			*cmds;
	int				cmd_count;
	char			*line;
	bool			heredoc_pipe;
	t_token			*heredoc_token;
}					*t_grouped;

void				free_left_pipe_side(t_token **tokens,
						t_token *heredoc_token, t_cmd *cmds, int cmd_count);
t_token				*find_heredoc_token(t_token *tokens);

void				cleanup_heredoc_and_exit(t_cmd *cmd, t_grouped group,
						int status);
t_grouped			build_group(t_shell *shell, t_cmd *cmds, int cmd_count,
						t_token **tokens);
void				cleanup(char **args, t_shell *px, t_token **tokens,
						char **cmds);
void				free_partial_args(char **args, int i);
int					token_is_redir(t_token *token);
int					init_cmds_and_group(t_token **tokens, t_shell *shell,
						t_cmd **cmds, t_grouped *grp);
void				handle_cmd_failure(t_cmd *cmds, t_token **tokens,
						t_shell *shell, int cmd_count);
void				cleanup_pipe_cmds(t_cmd *cmds, int cmd_count,
						t_token **tokens, t_token *head);
int					count_pipes(t_token *tokens);

// ---------------------------------

void				cleanup_child_and_exit(t_cmd *cmd, t_shell *shell,
						t_token **tokens, int status);

int					syntax_error(t_token **tokens, t_shell *shell);
int					valid_name(char *name);

char				*get_right_path(char *cmd, void *either_shell, int is_pipe);

char				*process_word(char *word, t_shell *shell, int flag);

int					handle_q(t_token_b **tks, char *str, int i, t_shell *shell);
int					simple_word(t_token_b **tks, char *str, int i,
						t_shell *shell);

char				*join_and_free(char *s1, char *s2);

void				init_shell(t_shell *shell, char **envp);
void				take_comm(t_token **tokens, t_shell *shell);
int					input(char *str, t_token **tokens, t_shell *shell);
char				**make_args(t_token **tokens, t_shell *shell);
char				*set_pwd(t_shell *shell);
void				execute_single_cmd(char **cmd, t_shell *shell,
						t_token **tokens);

// get_path
void				process_commands(t_token **tokens, t_shell *shell);
char				*get_cmd_path(char *cmd, t_shell *shell);
void				single_cmd(t_token **tokens, t_shell *shell);
void				pipe_cmds(t_token **tokens, t_shell *shell);

// pipes utils
int					token_has_pipe(t_token **tokens);
char				**make_args_pipes(t_token **tokens);
char				*get_path_in(char *cmd, t_shell *px);
char				*process_token(t_token *token, char *cmd_str, char **cmds,
						int *i);

// pipes
void				pipex_error(char *msg);
void				fd_handle(int i, int cmd_count, t_shell *px);
void				which_child(int i, int cmd_count, t_shell *px,
						t_info *info);
void				create_pipes(char **cmds, t_shell *shell, t_token **tokens);
void				first_child_process(t_shell *px, char *cmd,
						t_token **tokens, char **cmds);
void				last_child_process(t_shell *px, char *cmd, t_token **tokens,
						char **cmds);
void				middle_child_process(t_shell *px, char *cmd,
						t_token **tokens, char **cmds);
void				close_pipes_and_wait(t_shell *px, int cmd_count);
void				execute_cmd(char *cmd, t_shell *px, t_token **tokens,
						char **cmds);

//dollar sign
char				*handle_dollar(char *cmd, t_shell *shell);

// handle redir (COPY_REDIR)
//executor_main.c (static: 2)
void				execute_piped_commands(t_shell *px, t_grouped grp);
void				single_cmd_with_redir(t_token **tokens, t_shell *shell);
void				execute_single_redir(t_cmd *cmd, t_shell *shell,
						t_token **tokens);
// executor_utils.c
void				handle_exit_status(t_shell *shell, int status);
int					prep_command_path(t_cmd *cmd, t_shell *shell, char **path);
void				run_child_redir(char *path, t_cmd *cmd, t_shell *shell,
						t_token **tokens);
void				execve_cmd(t_cmd *cmd, t_shell *shell, t_token **tokens);
void				close_all_pipe_fds(t_shell *px);
//heredoc.c (static: 4)
void				heredoc_do(t_cmd *cmd, t_grouped group, char *delimiter);
//parser_redir_utils.c
int					redir_token_in_out(t_token **tokens, t_cmd *cmd);
int					redir_token_append(t_token **tokens, t_cmd *cmd);
int					handle_arg_token(t_token **token, char **args, int *i);
void				readirs(int dir, t_cmd *cmd, char *com);
//parser_redir.c
char				**parse_args_and_redirs(t_token **tokens, t_cmd *cmd,
						t_grouped group);
int					handle_redirection_token(t_token **delim, t_cmd *cmd,
						t_grouped group);
// void				fill_args_and_handle_redir(t_token **tokens, t_cmd *cmd,
// 						char **args, t_shell *shell);
//pipeline.c (static: 1)
void				pipe_cmds_with_redir(t_token **tokens, t_shell *shell);
//redir_apply.c (static: 2)
void				apply_redirection(t_cmd *cmd);
void				reset_redirection(t_cmd *cmd);
//token_utils.c (static: 1)
int					is_redir(const char *s);
int					token_has_redir(t_token *tokens);

int					count_args(t_token *tokens);
void				init_cmd(t_cmd *cmd);
void				init_pipex(t_shell *px, t_shell *shell);

// signals

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
void				close_free(t_token **tokens, t_shell *shell);
void				free_array(char **arr);
void				deallocate(t_token **root);

//for list tokens
t_token				*new_token(char *word, int quoted);
void				add_token(t_token **head, char *word, int quoted);

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
int					copy_env_vars(char **dest, char **src, size_t count);
char				*process_env_var(char *cmd, t_shell *shell, char *prefix,
						int i);

//testing
void				print_list(t_token *tokens);

#endif