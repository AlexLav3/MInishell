/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_finds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:16:28 by ferenc            #+#    #+#             */
/*   Updated: 2025/02/25 16:27:02 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_Node	*find_last(t_Node *root)
{
	t_Node	*curr;

	if (!root)
		return (NULL);
	curr = root;
	while (curr->next)
	{
		curr = curr->next;
	}
	return (curr);
}

t_Node	*find_min(t_Node *root)
{
	long	min;
	t_Node	*min_node;

	if (!root)
		return (NULL);
	min = LONG_MAX;
	while (root)
	{
		if (root->x < min)
		{
			min = root->x;
			min_node = root;
		}
		root = root->next;
	}
	return (min_node);
}

t_Node	*find_max(t_Node *root)
{
	long	max;
	t_Node	*max_node;

	if (!root)
		return (NULL);
	max = LONG_MIN;
	while (root)
	{
		if (root->x > max)
		{
			max = root->x;
			max_node = root;
		}
		root = root->next;
	}
	return (max_node);
}

/*double*/
t_Node	*find_node(t_Node *tail, int value)
{
	t_Node	*curr;

	curr = tail;
	while (curr != NULL)
	{
		if (curr->x == value)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
