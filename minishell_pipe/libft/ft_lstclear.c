/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:37:09 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 13:50:52 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Deletes and frees the given node and every
successor of that node, using the function ’del’
and free(3).
Finally, the pointer to the list must be set to
NULL.
*/
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}
// #include <stdlib.h>
// #include <stdio.h>
// int main(void)
// {
// 	t_list	*one = (t_list *)malloc(sizeof(t_list));
// 	t_list	*two = (t_list *)malloc(sizeof(t_list));

// 	//malloc space for content
// 	one -> content = malloc (sizeof(char) * 10);
// 	two -> content = malloc (sizeof(char) * 10);

// 	//connect to form list
// 	one -> next = two;

// 	//fill w content
// 	size_t a = ft_strlcpy(one -> content, "Hi", 10);
// 	a = 0;
// 	size_t b = ft_strlcpy(two -> content, "Bye", 10);
// 	b = 0;

// 	printf("content before deletion: %s\n", (char *)one -> content);
// 	printf("next before deletion: %p\n", one -> next);
// 	printf("content before deletion: %s\n", (char *)two -> content);
// 	printf("next before deletion: %p\n", two -> next);

// 	t_list	*ptr;
// 	ptr = one;
// 	ft_lstclear(&ptr, delete);

// 	if (one -> content)
// 		printf("content one after deletion: %s\n", (char *)one -> content);
// 	printf("next after deletion: %p\n", one -> next);
// 	if (two -> content)
// 		printf("content two after deletion: %s\n", (char *)two -> content);
// 	printf("next after deletion: %p\n", two -> next);

// 	if (ptr == NULL) {
//         printf("List has been cleared.\n");
//     }

// }