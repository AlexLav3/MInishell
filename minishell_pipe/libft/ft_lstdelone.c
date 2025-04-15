/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:17:36 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 12:16:23 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Takes as a parameter a node and frees the memory of
the node’s content using the function ’del’ given
as a parameter and free the node. The memory of
’next’ must not be freed.
*/
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}
// #include <stdlib.h>
// #include <stdio.h>
// int main(void)
// {
// 	//t_list	*ptr;
// 	t_list	*one = (t_list *)malloc(sizeof(t_list));

// 	one -> content = malloc (sizeof(char) * 10);

// 	size_t a = ft_strlcpy(one -> content, "Hi", 10);
// 	a = 0;

// 	printf("content before deletion: %s\n", (char *)one -> content);
// 	printf("next before deletion: %p\n", one -> next);

// 	ft_lstdelone(one, delete);

// 	if (one -> content)
// 		printf("content after deletion: %s\n", (char *)one -> content);
// 	printf("next after deletion: %p\n", one -> next);

// }