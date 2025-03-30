/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:17:31 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/30 16:16:55 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//find directory/path
char	*find_dir(t_token *token)
{
	DIR				*folder;
	struct dirent	*dir;
	char			*path;
	char			*bin_dir;

	bin_dir = "/usr/bin";
	while (token)
	{
		folder = opendir(bin_dir);
		if (!folder)
			return (NULL);
		while ((dir = readdir(folder)) != NULL)
		{
			if (token->com != NULL)
			{
				if (strcmp(dir->d_name, token->com) == 0) //create ft_strcmp
				{
					path = malloc(strlen(bin_dir) + strlen(dir->d_name) + 2);
					if (!path)
						return (closedir(folder), NULL);
                    ft_strlcpy(path, bin_dir, strlen(bin_dir) + 1);
					closedir(folder);
					return (path);
				}
			}
		}
		closedir(folder);
		token = token->next;
	}
	return (NULL);
}
