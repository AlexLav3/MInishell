/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_of_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferenc <ferenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:22:17 by ferenc            #+#    #+#             */
/*   Updated: 2025/03/03 15:56:17 by ferenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	abs_custom(int x)
{
	if (x < 0)
		return (x *= -1);
	else
		return (x);
}

int	max_of_three(int x, int y, int z)
{
	int	max;
	int	result;

	result = (x + y + abs_custom(x - y)) / 2;
	max = (result + z + abs_custom(result - z)) / 2;
	return (max);
}
