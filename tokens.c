/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:20:08 by elavrich          #+#    #+#             */
/*   Updated: 2025/07/31 16:17:23 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_token	*new_token(char *word, int quoted)
{
	t_token		*tokens;

	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->com = ft_strdup(word);
	if (!tokens->com)
	{
		free(word);
		return (free(tokens), NULL);
	}
	tokens->next = NULL;
	tokens->quoted = quoted;
	return (tokens);
}

void	add_token(t_token **head, char *word, int quoted)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(word, quoted);
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ;
}

char	*handle_var_exit_status(char *cmd, t_shell *shell,
				int i, char **suf)
{
	char	*value;

	value = ft_itoa(shell->exit_stat);
	*suf = ft_strdup(cmd + (i + 2));
	return (value);
}

char	*handle_invalid_env(char c)
{
	if (c != ' ')
		return (ft_strdup(""));
	return (ft_strdup("$"));
}

char	*handle_valid_env(t_shell *shell, char *prefix)
{
	char	*env;
	char	*value;

	env = shell->env_var[shell->env_idx];
	value = ft_strchr(env, '=');
	if (!value)
	{
		free(prefix);
		return (ft_strdup(""));
	}
	return (ft_strdup(value + 1));
}
