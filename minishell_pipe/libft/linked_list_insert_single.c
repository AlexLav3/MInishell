/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_insert_single.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:31 by ferenc            #+#    #+#             */
/*   Updated: 2025/02/25 16:25:46 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	insert_end(t_Node **root, int value)
{
	t_Node	*new_node;
	t_Node	*curr;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
		exit (1);
	new_node->next = NULL;
	new_node->x = value;
	if (*root == NULL)
	{
		*root = new_node;
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
}

void	insert_beginning(t_Node **root, int value)
{
	t_Node	*new_node;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
		exit (3);
	new_node->x = value;
	new_node->next = *root;
	*root = new_node;
}

void	insert_after(t_Node *node, int value)
{
	t_Node	*new_node;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
		exit (4);
	new_node->x = value;
	new_node->next = node->next;
	node->next = new_node;
}

void	insert_sorted(t_Node **root, int value)
{
	t_Node	*curr;

	if (*root == NULL || (*root)->x >= value)
	{
		insert_beginning(root, value);
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
	{
		if (curr->next->x >= value)
		{
			insert_after(curr, value);
			return ;
		}
		curr = curr->next;
	}
	insert_after(curr, value);
}
