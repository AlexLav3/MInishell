/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:41:21 by elavrich          #+#    #+#             */
/*   Updated: 2025/05/17 07:29:47 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../Minishell.h>

int	handle_redirection_token(t_token *tokens, t_shell *shell)
{
	char	*delimiter;

	if (ft_strcmp(tokens->com, "<") == 0 && tokens->next)
		return (readirs(1, shell, tokens->next->com), 1);
	else if (ft_strcmp(tokens->com, ">") == 0 && tokens->next)
		return (readirs(2, shell, tokens->next->com), 1);
	else if (ft_strcmp(tokens->com, ">>") == 0 && tokens->next)
	{
		shell->outfile = ft_strtrim(tokens->next->com, " \n\t");
		shell->redir_out = open(shell->outfile, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (shell->redir_out < 0)
			perror("redir: ");
		return (1);
	}
	else if (ft_strcmp(tokens->com, "<<") == 0 && tokens->next->com)
		return (heredoc_do(tokens, shell, tokens->next->com), 1);
	return (0);
}

void	heredoc_do(t_token *tokens, t_shell *shell, char *delimiter)
{
	t_shell	px;
	char	*line;

	px.envp = shell->env_var;
	px.pipe_fd[1] = -1;
	if (pipe(px.pipe_fd) == -1)
	{
		pipex_error("Error creating pipe");
		return ;
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(px.pipe_fd[1], line, ft_strlen(line));
		write(px.pipe_fd[1], "\n", 1);
		free(line);
	}
	close(px.pipe_fd[1]);
	shell->redir_in = px.pipe_fd[0];
}

void	readirs(int dir, t_shell *shell, char *com)
{
	if (dir == IN_FILE)
	{
		shell->infile = ft_strtrim(com, " \n\t");
		shell->redir_in = open(shell->infile, O_RDONLY);
		if (shell->redir_in < 0)
			perror("redir: ");
	}
	else if (dir == OUT_FILE)
	{
		shell->outfile = ft_strtrim(com, " \n\t");
		shell->redir_out = open(shell->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (shell->redir_out < 0)
			perror("redir: ");
	}
}
