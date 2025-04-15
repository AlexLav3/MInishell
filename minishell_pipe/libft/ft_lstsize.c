/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnagy <fnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:44:37 by ferenc            #+#    #+#             */
/*   Updated: 2024/10/03 12:16:23 by fnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

*/
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
/*
temp = temp->next; can be like this temp = (*temp).next;
*/
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

// 	int len = ft_lstsize(ptr);

// 	printf("len: %i\n", len);
// }