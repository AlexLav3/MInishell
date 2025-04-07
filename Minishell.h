/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/07 15:48:21 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include "libft/src/libft.h"
# include <readline/readline.h>
# include <dirent.h>
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
	int				exit;
	pid_t 			status; 
}					t_shell;

void				init_shell(t_shell *shell, char **envp);
void				take_comm(t_token **tokens, t_shell *shell);
void				input(char *str,  t_token **tokens);
char				**make_args(t_token *tokens);

// get_path
char				*get_cmd_path(char *cmd, t_shell *shell);
void				exec_comd(void);

//env variables 
char				**copy_envp(char **envp);
void 				print_env(t_shell shell);

//for list tokens
t_token				*new_token(char *word);
void 				add_token(t_token **head, char *word);

//utils 
int					is_sep(char c);
char				*join_path(const char *dir, const char *cmd);
void				free_array(char **arr);
void				deallocate(t_token **root);

//testing
void 				print_list(t_token *tokens);

#endif