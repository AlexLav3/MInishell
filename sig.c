/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:53:04 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/10 02:58:40 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void    sig_handle(int sig)
{
    (void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_sig(void)
{
	signal(SIGINT, sig_handle); //this only passes the function. 
	//it's registering it as a callback function to be called by the OS when the signal arrives.
	
	signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+ slash
}
    