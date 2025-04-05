/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/05 18:59:13 by fnagy            ###   ########.fr       */
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
	char			**envp; //add by Ferenc temp
	char			*com;
	struct s_token	*next;
	// struct s_token	*prev;
}					t_token;

//state of shell and more, idk yet.
typedef struct s_shell
{
	int				exit;
	pid_t 			status; //possibily, for wait() bc getpid() is not allowed.
}					t_shell;

void				init_shell(t_shell *shell); //init shell values
void				print_comm(t_token *tokens);
void				*input(char *str,  t_token **tokens); //process input

char				*find_dir(t_token *token);
void				exec_comd(void);
void				proc_string(void);

//for list tokens
t_token 			*new_token(char *word);
void 				add_token(t_token **head, char *word);

//utils 
int					is_sep(char c);
//testing
void 				print_list(t_token *tokens);


#endif