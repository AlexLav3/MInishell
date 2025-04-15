/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:59:31 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 12:16:23 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Returns the last node of the list.
*/
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}
// #include <stdio.h>
// int main (void)
// {
// 	t_list l3;
// 	l3.content = "!";
// 	l3.next = NULL;
// 	t_list l2;
// 	l2.content = "World ";
// 	l2.next = &l3;
// 	t_list l1; 
// 	l1.content = "Hello ";
// 	l1.next =  &l2;

// 	t_list	*ptr = &l1;
// 	t_list	*last = ft_lstlast(ptr);

// 	printf("%s\n", (char *)last -> content);
// }