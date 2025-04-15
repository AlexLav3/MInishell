/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/15 14:47:18 by elavrich         ###   ########.fr       */
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
	char			***av;
	char			*pwd;
	int				input_fd;
	int				output_fd;
	int				pipe_fd[2];
	pid_t			pid1;
	pid_t			pipe_pid;
	int				exit;
}					t_shell;

void				init_shell(t_shell *shell, char **envp);
void				take_comm(t_token **tokens, t_shell *shell);
void				input(char *str, t_token **tokens);
char				**make_args(t_token *tokens);
char				*set_pwd(t_shell *shell);

void				execute_single_cmd(char **cmd, t_shell *shell);

// get_path
void				process_commands(char *command, t_token **tokens,
						t_shell *shell);
char				*get_cmd_path(char *cmd, t_shell *shell);

// pipes utils
int					has_seps(char **cmd, char sep);
int					count_seps(char **cmd, char sep);
int					count_segment_tokens(char **cmd, int start, char sep);
void				free_av(char ***av);

// pipes
void				split_by_pipe(t_shell *shell, char **cmd);
void				execute_command(char **cmd, int input_fd, int output_fd,
						t_shell *shell);
void				execute_pipeline(t_shell *shell);
void				handle_pipeline(t_shell *shell, int index, int input_fd);

//builtin
bool				handle_builtin(char **cmd, t_shell *shell);
// bool				ft_echo(char **cmd); //works already with execute single cmd 
void    			builtin_cd(char **cmd, t_shell *shell);

void 				builtin_pwd(char **cmd, t_shell *shell); //I figured this one out. it was using the one in bin/pwd, but interal variable didn't change.
//it updates correctly now. 
void				ft_export(char **cmd, t_shell *shell);
bool				ft_unset(char **cmd, t_shell *shell);
//bool				ft_env(t_shell *shell); //working already. - maybe needs a custom one anyway? I think it uses the one in bin rn. 

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
bool				check_for_exit(char *command);
void				ft_exit(t_shell *shell);

//for list tokens
t_token				*new_token(char *word);
void				add_token(t_token **head, char *word);

//utils
int					is_sep(char c);
char				*join_path(const char *dir, const char *cmd);
int					size_args(t_token *tokens);
//testing
void				print_list(t_token *tokens);

#endif