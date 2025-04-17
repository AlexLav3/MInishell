/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:44:55 by fnagy             #+#    #+#             */
/*   Updated: 2025/04/17 14:59:01 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	separator_len(char *s) // return 1 for | and <, but 2 for << or >>
{
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return (2);
	else if (is_sep(s[0]))
		return (1);
	return (0);
}

// I should have this in my libft already
void	insert_after_token(t_token *prev, char *word)
{
	t_token	*new;

	new = new_token(word);
	if (!new)
		return ;
	new->next = prev->next;
	prev->next = new;
}

void	split_and_insert_parts(t_token *curr, int i, int len)
{
	char	*tmp;

	if (curr->com[i + len])
	{
		tmp = ft_strdup(&curr->com[i + len]);
		insert_after_token(curr, tmp);
	}
	tmp = ft_substr(curr->com, i, len);
	insert_after_token(curr, tmp);
	if (i > 0)
	{
		tmp = ft_substr(curr->com, 0, i);
		insert_after_token(curr, tmp);
	}
}

int	split_token_content(t_token *curr)
{
	int		i;
	int		len;

	i = 0;
	while (curr->com[i])
	{
		len = separator_len(&curr->com[i]);
		if (len > 0)
		{
			split_and_insert_parts(curr, i, len);
			return (1);
		}
		i++;
	}
	return (0);
}

void	split_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (split_token_content(curr))
		{
			if (prev)
				prev->next = curr->next;
			else
				*tokens = curr->next;
			free(curr->com);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}
