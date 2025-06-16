#include "Minishell.h"

char	*process_word(char *word, t_shell *shell, int flag)
{
	char	*exp;

	if (flag != EXPAND || !word)
		return (word);
	if (ft_strchr(word, '$') != NULL)
	{
		exp = handle_dollar(word, shell);
		if (!exp)
			return (word);
	}
	else
		return (word);
	free(word);
	return (exp);
}
