/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:12:28 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 12:16:23 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Adds the node ’new’ at the end of the list.
*/
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}
// #include <stdio.h>
// int main (void)
// {
// 	t_list new;
// 	new.content = "!";
// 	new.next = NULL;//random to see if NULL after ft
// 	t_list l2;
// 	l2.content = "World ";
// 	l2.next = NULL;
// 	t_list l1; 
// 	l1.content = "Hello ";
// 	l1.next =  &l2;

// 	t_list	*ptr = &l1;
// 	t_list	*neww = &new;

// 	ft_lstadd_back(&ptr, neww);
// 	printf("adress node 1: %p\n", &l1);
// 	printf("next in node 1: %p\n", (void *)l1.next);

// 	printf("adress node 2: %p\n", &l2);
// 	printf("next in node 2: %p\n", (void *)l2.next);

// 	printf("adress node 3: %p\n", &new);
// 	printf("next in node 3: %p\n", (void *)new.next);
// }