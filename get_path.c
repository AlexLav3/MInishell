
#include "Minishell.h"

// cmd should be the first position of an array: array[0]
char	*get_cmd_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	**envp = shell->env_var;

	full_path = NULL;
	while (*envp && ft_strncmp(*envp, "PATH=", 5)) 
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
	}
	return (free_array(paths), NULL);
}
