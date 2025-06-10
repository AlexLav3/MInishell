#include "Minishell.h"

char *process_word(char *word, t_shell *shell, int flag)
{
	char	*exp;

    if (flag != EXPAND || !word)
		return ft_strdup(word);
    if (ft_strchr(word, '$') != NULL)
    {
	    exp = handle_dollar(word, shell);
	    if (!exp)
		    return ft_strdup(word); 
    }
    else 
        return ft_strdup(word);
    free(word);
    return exp;
}

