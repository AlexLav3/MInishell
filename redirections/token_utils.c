#include "../Minishell.h"

//token_utils.c
int	is_redir(const char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0 || \
	ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
}

int	token_has_redir(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->com)
		{
			tokens = tokens->next;
			continue ;
		}
		if (ft_strcmp(tokens->com, "<") == 0 || \
			ft_strcmp(tokens->com, ">") == 0 || \
			ft_strcmp(tokens->com, ">>") == 0 || \
			ft_strcmp(tokens->com, "<<") == 0)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

static void	remove_redir(t_token **tokens, t_token **curr, t_token **prev)
{
	t_token	*to_free;
	t_token	*next_token;

	to_free = *curr;
	next_token = (*curr)->next;
	if (*prev)
		(*prev)->next = next_token->next;
	else
		*tokens = next_token->next;
	*curr = next_token->next;
	free(to_free->com);
	free(to_free);
	free(next_token->com);
	free(next_token);
}

void	strip_redirection_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

	curr = *tokens;
	prev = NULL;
	while (curr && curr->next)
	{
		if (is_redir(curr->com))
			remove_redir(tokens, &curr, &prev);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}