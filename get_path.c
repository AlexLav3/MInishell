
#include "Minishell.h"

// this is just to know what get_cmd_path takes as args
// void	execute_cmd(char *cmd, char **envp)
// {
// 	char	**arguments;
// 	char	*path;

// 	arguments = ft_split(cmd, ' ');
// 	if (!arguments)
// 		pipex_error("Failed to split commands");
// 	path = get_cmd_path(arguments[0], envp);
// 	if (!path)
// 	{
// 		free_array(arguments);
// 		pipex_error("Command not found");
// 	}
// 	if (execve(path, arguments, envp) == -1)
// 	{
// 		perror("Command not found");
// 		free_array(arguments);
// 		free(path);
// 		exit(127);
// 	}
// }


char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// cmd should be the first position of an array: array[0]
// change argument intake to struct and after changed it back to array
char	*get_cmd_path(char *cmd, t_token *env_clone)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	**envp = env_clone->envp; //change back to array and function needs NO other modification

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
