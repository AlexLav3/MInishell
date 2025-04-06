/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/06 16:09:52 by elavrich         ###   ########.fr       */
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

//for storing tokens (commands, for example, "ls" and "l" are 2 tokens.)
typedef struct s_token
{
	char			*com;
	struct s_token	*next;
	// struct s_token	*prev; //maybe will be needed 
}					t_token;

//state of shell and more, idk yet.
typedef struct s_shell
{
	char			**env_var;
	int				exit;
	pid_t 			status; 
}					t_shell;

void				init_shell(t_shell *shell, char **envp); //init shell values
void				take_comm(t_token *tokens); //changed name 
void				*input(char *str,  t_token **tokens); //process input
char				**make_args(t_token *tokens); //make cmd and arguments as arrayvoid	add_to_array(char *cmd, int len, char *token)
char				*add_to_array(char *cmd, int len, char *token);

// get_path
char				*get_cmd_path(char *cmd, t_shell *shell);
void				exec_comd(void);

//env variables 
void 				print_env(t_shell shell); //printing
char				**copy_envp(char **envp); //copy

//for list tokens
t_token				*new_token(char *word);
void 				add_token(t_token **head, char *word);

//utils 
int					is_sep(char c);
char				*join_path(const char *dir, const char *cmd);
void				free_array(char **arr);

//testing
void 				print_list(t_token *tokens);





#endif