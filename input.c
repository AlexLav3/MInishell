/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/30 16:18:52 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//tokenizer. will need to add error management.
//maybe will also need a function to check for '<<' and taking more than two < as invalid.
void	*input(char *str, t_token **tokens)
{
    int i = 0; 
    char *com;
    char *word;
    int len_w = 0;
    while(str[i])
    {
        if(str[i] == ' ')
            i++;
        if(is_sep(str[i]))
        {
            char sep[2] = {str[i], '\0'};
            add_token(tokens, sep);
            i++;
        }
        else 
        {
            //make tokenizer function instead with this
            int start = i;
            while (str[i] && !is_sep(str[i]) && str[i] != ' ')
                i++; 
            int word_len = i - start; 
            word = malloc(word_len + 1);
            if (!word)
                return NULL;
            ft_strlcpy(word, &str[start], word_len + 1);
            add_token(tokens, word);
        }
    }
    print_list(*tokens); //test
    free(word);
}

t_token *new_token(char *word)
{
    t_token *tokens = malloc(sizeof(t_token));
    if (!tokens)
        return NULL;
    tokens->com = word;  // Store the word
    tokens->next = NULL;
    return tokens;
}

void add_token(t_token **head, char *word)
{
    t_token *new = new_token(word);
    if (!new)
        return;
    if (!*head)
        *head = new;
    else
    {
        t_token *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}
