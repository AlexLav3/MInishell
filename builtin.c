/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:08:10 by ferenc            #+#    #+#             */
/*   Updated: 2025/04/09 11:08:26 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

bool	handle_builtin(char **cmd, t_shell *shell);

bool	ft_echo(char **cmd);
bool	ft_cd(char **cmd, t_shell *shell);
bool	ft_pwd(void);
bool	ft_export(char **cmd, t_shell *shell);
bool	ft_unset(char **cmd, t_shell *shell);
bool	ft_env(t_shell *shell);
void	ft_exit(t_shell *shell);