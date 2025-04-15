/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_change.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:12:20 by ferenc            #+#    #+#             */
/*   Updated: 2025/02/25 16:27:30 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	remove_element(t_Node **root, int value)
{
	t_Node	*to_remove;
	t_Node	*curr;

	if (*root == NULL)
		return ;
	if ((*root)->x == value)
	{
		to_remove = *root;
		*root = (*root)->next;
		free(to_remove);
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
	{
		if (curr->next->x == value)
		{
			to_remove = curr->next;
			curr->next = curr->next->next;
			free(to_remove);
			return ;
		}
		curr = curr->next;
	}
}

void	reverse(t_Node **root)
{
	t_Node	*prev;
	t_Node	*curr;
	t_Node	*next;

	prev = NULL;
	curr = *root;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*root = prev;
}

/*double*/
// if you remove tail, you need to dereference it first to aux and back after
// t_Node *aux = tail->next;
// remove_node(tail);
// tail = aux;
void	remove_node(t_Node *node)
{
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	free(node);
}

void	reverse_double(t_Node **tail, t_Node **head)
{
	t_Node	*curr;
	t_Node	*next;
	t_Node	*aux;

	curr = *tail;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = curr->prev;
		curr->prev = next;
		curr = next;
	}
	aux = *tail;
	*tail = *head;
	*head = aux;
}
