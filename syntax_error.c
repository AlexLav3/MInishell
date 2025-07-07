#include "Minishell.h"

//syntax_error.c
static int	is_special(char c)
{
	return (c != ';' &&
			c != '\\' &&
			c != '#' &&
			c != '!' &&
			c != '~' && 
			c != '&' &&
			c != '(' &&
			c != ')' &&
			c != '[' &&
			c != ']' &&
			c != '{' &&
			c != '}');
}
void	strip_char(char *command)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!command)
		return ;
	while (command[i])
	{	
		if (is_special(command[i]))
		{
			command[j] = command[i];
			j++;
		}	
		i++;
	}
	command[j] = '\0';
}

static int	syntax_pipe(t_token *tokens)
{
	if (is_pipe(tokens->com[0]))
		return(printf("*** Syntax error: no command before pipe. ***\n"), 3);
	while (tokens)
	{
		if (tokens->com && is_pipe(tokens->com[0]))
		{
			if (!tokens->next || is_pipe(tokens->next->com[0])
				|| is_pipe(tokens->com[1]))
				{
					printf("*** Syntax error: no command after pipe. ***\n");
					return (4);
				}
		}
		tokens = tokens->next;
	}
	return (0);
}


int	syntax_error(t_token **tokens)
{
	int	len;
	len = 0;
	print_list(*tokens);
	
	if (len == 0)
		len = syntax_pipe(*tokens);
	// if (len == 0)
	// 	len = syntax_redir(*tokens);

	// printf("\nYou typed a wrong command, which caused syntax error.\n");
	// printf("Try again!\n");
	deallocate(tokens);
	len = 1; // no need just until everything else is fixed
	return (len);
}