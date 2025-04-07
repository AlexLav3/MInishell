/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/07 16:55:12 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// f:07/04/25 - removed unused variables + update
void	input(char *str, t_token **tokens)
{
	int		i; 
	char	*word;
	int		start;
	int		word_len;

	i = 0;
	while(str[i])
	{
		if(str[i] == ' ')
			i++;
		if(is_sep(str[i]))
			break;
		start = i;
		while (str[i] && !is_sep(str[i]) && str[i] != ' ')
			i++;
		word_len = i - start; 
		word = malloc(word_len + 1);
		if (!word)
			return ;
		ft_strlcpy(word, &str[start], word_len + 1);
		add_token(tokens, word);
		free(word);
	}
	//print_list(*tokens); //test to check what's inside the tokens
	//free(word); //doesn't change anything in the memory leaks but creates issues.
}

t_token	*new_token(char *word)
{
	t_token	*tokens;

	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return NULL;
	tokens->com = ft_strdup(word); // f:07/04/25 - create a copy of word, so we can free it in input
	if (!tokens->com)
	{
		free(word);
		return (free(tokens), NULL);
	}
	free(word);
	tokens->next = NULL;
	return tokens;
}

void	add_token(t_token **head, char *word)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(word); //we can free the word inside new token.
	if (!new)
		return;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
