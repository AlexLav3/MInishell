/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:22:31 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 12:16:23 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Adds the node ’new’ at the beginning of the list.
*/
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
// #include <stdio.h>
// int main (void)
// {
// 	t_list l2;
// 	l2.content = "!";
// 	l2.next = NULL;
// 	t_list l1; 
// 	l1.content = "World ";
// 	l1.next =  &l2;

// 	t_list	*ptr = &l2; //if this NULL then new is first
// 	t_list	*new = ft_lstnew("Hello");

// 	ft_lstadd_front(&ptr, new);

// 	printf("%p = mem adress l2\n", &l2);
// 	printf("%p = new.next\n", new -> next);
// }