/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:12:20 by ferenc            #+#    #+#             */
/*   Updated: 2025/03/19 13:27:58 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	has_loops(t_Node *root)
{
	t_Node	*slow;
	t_Node	*fast;

	slow = root;
	fast = root;
	while (slow != NULL && fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return (1);
	}
	return (0);
}

int	count_nodes(t_Node *root)
{
	int		c;
	t_Node	*curr;

	c = 0;
	curr = root;
	while (curr != NULL)
	{
		c++;
		curr = curr->next;
	}
	return (c);
}

bool	is_list_sorted(t_Node *root)
{
	if (!root)
		return (1);
	while (root->next)
	{
		if (root->x > root->next->x)
			return (false);
		root = root->next;
	}
	return (true);
}
