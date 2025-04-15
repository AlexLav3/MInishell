/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_insert_double.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:39:08 by ferenc            #+#    #+#             */
/*   Updated: 2025/02/25 16:29:55 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	insert_beginning_double(t_Node **tail, int value)
{
	t_Node	*new_node;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
	{
		exit (1);
		return ;
	}
	new_node->x = value;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (*tail != NULL)
		(*tail)->prev = new_node;
	*tail = new_node;
}

// use this before you use the double insert, head needs to be initialized first
void	init(t_Node **tail, t_Node **head, int value)
{
	t_Node	*new_node;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
	{
		exit (2);
		return ;
	}
	new_node->x = value;
	new_node->prev = NULL;
	new_node->next = NULL;
	*tail = new_node;
	*head = new_node;
}

void	insert_end(t_Node **head, int value)
{
	t_Node	*new_node;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
	{
		exit (3);
		return ;
	}
	new_node->x = value;
	new_node->next = NULL;
	new_node->prev = *head;
	(*head)->next = new_node;
	*head = new_node;
}

//  before last if: node->cheapest = 0;
void	append_node(t_Node **root, int value)
{
	t_Node	*new_node;
	t_Node	*last_node;

	if (!root)
		return ;
	new_node = malloc(sizeof(t_Node));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->x = value;
	if (!(*root))
	{
		*root = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last_node = find_last(*root);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}

void	insert_after_double(t_Node *node, int value)
{
	t_Node	*new_node;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
	{
		exit (4);
		return ;
	}
	new_node->x = value;
	new_node->prev = node;
	new_node->next = node->next;
	if (node->next != NULL)
		node->next->prev = new_node;
	node->next = new_node;
}
