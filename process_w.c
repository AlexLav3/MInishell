#include "Minishell.h"

char *process_word(char *word, t_shell *shell, int flag)
{
    char	*pos;
	char	*exp;
	char	*res;

    if (flag != EXPAND || !word)
		return ft_strdup(word);
    if (ft_strchr(word, '$') != NULL)
    {
        // pos = ft_strchr(word, '$');
	    // if (!pos)
		//     return ft_strdup(word);
	    exp = handle_dollar(word, shell);
	    if (!exp)
		    return ft_strdup(word); 
    }
    else 
        return ft_strdup(word);
    free(word);
    return exp;
}

