/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 00:48:54 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/26 00:51:06 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_door2(t_player *player, t_map *m, t_vect door, int *d)
{
	int	x;
	int	y;

	x = door.x - 2;
	y = door.y - 2;
	while (x <= door.x + 2)
	{
		if ((int)(player->x) == x)
			*d = 1;
		while (y <= door.y + 2)
			y++;
		x++;
	}
	if (*d == 1)
		m->map[door.y][door.x] = '0';
}

void	check_door(t_player *player, t_map *m, t_vect door)
{
	int	x;
	int	y;
	int	isdoor;

	m->map[door.y][door.x] = 'D';
	x = door.x - 2;
	y = door.y - 2;
	isdoor = 0;
	while (y <= door.y + 2)
	{
		if ((int)(player->x) == x && (int)(player->y) == y)
			isdoor = 1;
		while (x <= door.x + 2)
			x++;
		y++;
	}
	check_door2(player, m, door, &isdoor);
}
