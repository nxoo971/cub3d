/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:13:57 by rferradi          #+#    #+#             */
/*   Updated: 2023/03/27 19:29:44 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int sign_y, int a, void *ptr)
{
	const int	middle = WIDTH / 2;
	t_data		*data;

	(void)a;
	data = (t_data *)ptr;
	if (sign_y == middle)
		return (0);
	if (data -> mouse > sign_y)
		move_angle(data, +1);
	else
		move_angle(data, -1);
	data -> mouse = sign_y;
	return (1);
}
