/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 08:02:21 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/src/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define IN_FILE 1
# define OUT_FILE 2

typedef struct s_token
{
	char			*com;
	struct s_token	*next;
	bool			literal;
}					t_token;

typedef struct s_shell
{
	char			**env_var;
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
}					t_shell;

int					simple_word(t_token **tokens, char *str, int i);

void				heredoc_do(t_token *tokens, t_shell *shell,
						char *delimiter);
void				readirs(int dir, t_shell *shell, char *com);

void				init_shell(t_shell *shell, char **envp);
void				take_comm(t_token **tokens, t_shell *shell);
int					input(char *str, t_token **tokens);
char				**make_args(t_token *tokens, t_shell *shell);
char				*set_pwd(t_shell *shell);
int					handle_single_q(t_token **tokens, char *str, int i);
void				execute_single_cmd(char **cmd, t_shell *shell);

// split tokens
int					separator_len(char *s);
void				insert_after_token(t_token *prev, char *word);
void				split_and_insert_parts(t_token *curr, int i, int len);
int					split_token_content(t_token *curr);
void				split_tokens(t_token **tokens);

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

//builtin
bool				handle_builtin(char **cmd, t_shell *shell);
void				builtin_cd(char **cmd, t_shell *shell);
void				builtin_pwd(char **cmd, t_shell *shell);
void				ft_export(char **cmd, t_shell *shell);
void				builtin_unset(char **cmd, t_shell *shell);
int					ft_echo(char **cmd, t_shell *shell);
void				ft_exit(char **cmd, t_shell *shell);

//builtin utils
int					is_valid_directory(char *path);

//env variables
char				**copy_envp(char **envp);
void				print_env(t_shell shell);
void				add_env(t_shell *shell, char *var);
int					search_env(t_shell *shell, char *var);
void				update_env(t_shell *shell, char *var, char *name);

//signals
void				sig_handle(int sig);
void				setup_sig(void);

//close & free
void				close_free(t_token *tokens, t_shell *shell);
void				free_array(char **arr);
void				deallocate(t_token **root);

//for list tokens
t_token				*new_token(char *word);
void				add_token(t_token **head, char *word, int literal);

//utils
int					is_meta(char c);
char				*join_path(char *dir, char *cmd);
int					size_args(t_token *tokens);
int					make_tok(t_token **tokens, char *str, int i);
int					is_pipe(char c);
int					size_cmd_arg(char **cmd);
char				*toks_to_args(t_token *tokens, char *cmd, t_shell *shell);

//testing
void				print_list(t_token *tokens);

#endif