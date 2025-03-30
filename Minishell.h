/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:44:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/30 01:01:15 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

//for storing tokens (commands, for example, "ls" and "l" are 2 tokens.)
typedef struct s_token
{
	char			*token;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

//state of shell and more, idk yet.
typedef struct s_shell
{
	int				exit;
	pid_t 			pid; //possibily, for wait() bc getpid() is not allowed.
}					t_shell;

//I think the names here are pretty self-explanatory.
void				init_shell(t_shell *shell); //init shell values
void				print_comm();           //print command
char				*input(char *str,  t_token *token);
void				find_argc(void);
void				exec_comd(void);
void				proc_string(void);

#endif