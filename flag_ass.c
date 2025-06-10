#include "Minishell.h"

t_words *word_node(char *str, int flag)
{
    t_words *node;

    node = malloc(sizeof(t_words));
    if (!node)
        return NULL;
    node->word = strdup(str);
    printf("word node: %s\n", node->word);
    if (!node->word)
    {
        free(str);
        return NULL;
    }
    node->flag = flag;
    node->next = NULL;
    return node;
}

void append_word(t_words **head, t_words *new_node)
{
    t_words *temp;
    if(!new_node)
        return;
    if (!*head)
        *head = new_node;
    else
    {
        temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

char *process_word(char *word, t_shell *shell, int flag)
{
    char	*pos;
	char	*exp;
	char	*res;

    printf("word: %s\n", word);
    if (flag != EXPAND || !word)
		return ft_strdup(word);
    if (ft_strchr(word, '$') != NULL)
    {
        printf("word again: %s\n", word);
        pos = ft_strchr(word, '$');
	    if (!pos)
		    return ft_strdup(word);
	    exp = handle_dollar(pos, shell);
	    if (!exp)
		    return ft_strdup(word); 
    }
    else 
        return ft_strdup(word);
    free(word);
    return exp;
}

