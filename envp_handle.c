#include "Minishell.h"

// printing envp
void	print_env(t_shell shell)
{
	int	i;

	if (!shell.env_var)
	{
		printf("No environment variables.\n");
		return;
	}
	i = 0;
	while (shell.env_var[i] != NULL)
		printf("%s\n", shell.env_var[i++]);
}
// copy of envp
char	**copy_envp(char **envp)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (envp[count])
		count++;
	char **copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return NULL;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]); // allocate memory and copy the string, not just the address to ptr
		if (!copy[i]) // f:07/04/25 - due to malloc
		{
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return NULL;
		}
		i++;
	}
	copy[count] = NULL;
	return copy;
}
