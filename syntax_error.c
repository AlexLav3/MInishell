#include "Minishell.h"

//syntax_error.c
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
		if (command[i] != ';' && command[i] != '\\')
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
		return(printf("*** missing command before pipe: %s ***\n", tokens->com), 3);
	else
	{
		while (tokens)
		{
			if (tokens->com && is_pipe(tokens->com[0]))
			{
				if (!tokens->next || is_pipe(tokens->next->com[0])
					|| is_pipe(tokens->com[1]))
					return(printf("*** no command after pipe ***\n"), 4);
			}
			tokens = tokens->next;
		}
	}
	return (0);
}
// static int	wrong_char(t_token *tokens)
// {
// 	int i;
	
// 	while (tokens)
// 	{	
// 		i = 0;
// 		while (tokens->com[i] != '\0')
// 		{	
// 			//these tokens need to be removed instead and return 0
// 			if (tokens->com[i] == ';' || tokens->com[i] == '\\')
// 			{
// 				return(printf("*** Not supported char: %c ***\n", tokens->com[i]), 5);
// 			}
// 			i++;
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }

int	syntax_error(t_token **tokens)
{
	int	len;
	len = 0;
	print_list(*tokens);
	
	if (len == 0)
		len = syntax_pipe(*tokens);
	// if (len == 0)
	// 	len = wrong_char(*tokens);

	// printf("You typed a wrong command, which caused syntax error.\n");
	// printf("Try again!\n");
	deallocate(tokens);
	len = 1; // no need just untile everything else is fixed
	return (len);
}