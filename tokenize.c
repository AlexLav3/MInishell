#include "Minishell.h"

// tokenize.c

/*
 * Allocates and returns a new t_token node with the given word.
 * Sets the `com` field using ft_strdup and initializes `next` to NULL.
 */
static t_token	*create_token(char *word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->com = ft_strdup(word);
	token->next = NULL;
	return (token);
}

/*
 * Splits a command string by spaces into words and creates a linked list of tokens.
 * Each word is wrapped in a t_token using create_token.
 * Returns the head of the token list, or NULL on failure.
 */
t_token	*tokenize_command(char *cmd_str)
{
	t_token	*head = NULL;
	t_token	*current = NULL;
	char	**words;
	int		i = 0;

	words = ft_split(cmd_str, ' ');
	if (!words)
		return (NULL);
	while (words[i])
	{
		t_token *new_token = create_token(words[i]);
		if (!new_token)
			break ;
		if (!head)
			head = new_token;
		else
			current->next = new_token;
		current = new_token;
		i++;
	}
	free_array(words);
	return (head);
}
