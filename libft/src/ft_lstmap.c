/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:09:19 by elavrich          #+#    #+#             */
/*   Updated: 2024/09/21 20:17:44 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_obj;

	new_list = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		new_obj = ft_lstnew(f(lst->content));
		if (!new_obj)
		{
			ft_lstdelone(new_obj, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_obj);
		lst = lst->next;
	}
	return (new_list);
}
