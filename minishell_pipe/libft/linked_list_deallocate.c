/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_deallocate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:12:30 by ferenc            #+#    #+#             */
/*   Updated: 2025/02/25 16:26:32 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	deallocate(t_Node **root)
{
	t_Node	*curr;
	t_Node	*aux;

	if (!root)
		return ;
	curr = *root;
	while (curr != NULL)
	{
		aux = curr;
		curr = curr->next;
		free(aux);
	}
	*root = NULL;
}

/*double*/
// deallocate works as well fine with doubly linked lists
void	deallocate_double(t_Node **tail, t_Node **head)
{
	t_Node	*curr;

	if (*tail == NULL)
		return ;
	curr = *tail;
	while (curr->next != NULL)
	{
		curr = curr->next;
		free(curr->prev);
	}
	free(curr);
	*tail = NULL;
	*head = NULL;
}
