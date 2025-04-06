/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 00:29:49 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/06 20:14:21 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//tokenizer. will need to add error management.
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
        if(is_sep(str[i])) //for now we break, to not include what goes after a pipe as arg
            break; //in the futre, we may want to re-call this function for what is after a pipe.
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
    //print_list(*tokens); //test to check what's inside the tokens
    //free(word);
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
