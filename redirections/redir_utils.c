/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:55:44 by fnagy             #+#    #+#             */
/*   Updated: 2025/05/01 14:29:09 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	is_redir(const char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0);
}

int	count_args(t_token *tokens)
{
	int	count = 0;

	while (tokens)
	{
		if (!is_redir(tokens->com))
			count++;
		else if (tokens->next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}

int	token_has_redir(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->com)
		{
			tokens = tokens->next;
			continue;
		}
		if (ft_strcmp(tokens->com, "<") == 0 ||
			ft_strcmp(tokens->com, ">") == 0 ||
			ft_strcmp(tokens->com, ">>") == 0 ||
			ft_strcmp(tokens->com, "<<") == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	handle_redirection_token(t_token *tokens, t_shell *shell)
{
	if (ft_strcmp(tokens->com, "<") == 0 && tokens->next)
	{
		shell->infile = ft_strtrim(tokens->next->com, " \n\t");
		shell->redir_in = open(shell->infile, O_RDONLY);
		if (shell->redir_in < 0)
			perror("redir: ");
		return (1);
	}
	else if (ft_strcmp(tokens->com, ">") == 0 && tokens->next)
	{
		shell->outfile = ft_strtrim(tokens->next->com, " \n\t");
		shell->redir_out = open(shell->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (shell->redir_out < 0)
			perror("redir: ");
		return (1);
	}
	else if (ft_strcmp(tokens->com, ">>") == 0 && tokens->next)
	{
		shell->outfile = ft_strtrim(tokens->next->com, " \n\t");
		shell->redir_out = open(shell->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (shell->redir_out < 0)
			perror("redir: ");
		return (1);
	}
	return (0);
}
void	fill_args_and_handle_redir(t_token *tokens, t_shell *shell, char **args)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (handle_redirection_token(tokens, shell))
			tokens = tokens->next;
		else
			args[i++] = ft_strdup(tokens->com);
		tokens = tokens->next;
	}
	args[i] = NULL;
}

char	**parse_args_and_redirs(t_token *tokens, t_shell *shell)
{
	char	**args;
	int		arg_count;

	shell->redir_in = -1;
	shell->redir_out = -1;
	shell->infile = NULL;
	shell->outfile = NULL;

	arg_count = count_args(tokens);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	fill_args_and_handle_redir(tokens, shell, args);
	return (args);
}

void	apply_redirection(t_shell *shell)
{	
	if (shell->redir_in != -1)
	{
		if (dup2(shell->redir_in, STDIN_FILENO) == -1)
		{
			perror("dup2 redir_in");
			exit(EXIT_FAILURE);
		}
		close(shell->redir_in);
	}
	if (shell->redir_out != -1)
	{
		if (dup2(shell->redir_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 redir_out");
			exit(EXIT_FAILURE);
		}
		close(shell->redir_out);
	}
}

void	execute_single_redir(char **cmd, t_shell *shell)
{
	char	*path;

	if (!cmd[0] || !cmd)
		return;
	path = get_cmd_path(cmd[0], shell);
	if (!path)
	{
		perror("Command not found utils.c redir");
		return;
	}
	shell->pid1 = fork();
	if (shell->pid1 == -1)
		perror("fork utils.c redir");
	else if (shell->pid1 == 0)
	{
		apply_redirection(shell);
		if (execve(path, cmd, shell->env_var) == -1)
		{
			perror("execve failed utils.c redir");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(shell->pid1, NULL, 0);
	free(path);
}

void	single_cmd_with_redir(char *command, t_token **tokens, t_shell *shell)
{
	char	**args;

	args = parse_args_and_redirs(*tokens, shell);
	free(command);
	if (!args || !args[0])
		return ;
	execute_single_redir(args, shell);
	free_array(args);
	reset_redirection(shell);
}

void	reset_redirection(t_shell *shell)
{
	if (shell->infile)
		free(shell->infile);
	if (shell->outfile)
		free(shell->outfile);
	shell->infile = NULL;
	shell->outfile = NULL;
	if (shell->redir_in != -1)
		close(shell->redir_in);
	if (shell->redir_out != -1)
		close(shell->redir_out);
	shell->redir_in = -1;
	shell->redir_out = -1;
}
