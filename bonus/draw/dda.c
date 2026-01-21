/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:22:10 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/29 01:51:34 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static
void	calculate_delta(t_params *params)
{
	params -> delta_y = 1e30;
	params -> delta_x = 1e30;
	if (params -> ray_y != 0)
		params -> delta_y = fabs(1 / params -> ray_y);
	if (params -> ray_x != 0)
		params -> delta_x = fabs(1 / params -> ray_x);
}

static
void	calc_step_and_side_dist(t_player player, t_params *params, \
									int map_y, int map_x)
{
	if (params -> ray_x < 0)
	{
		params -> step_x = -1;
		params -> side_x = (player.x - map_x) * params -> delta_x;
	}
	else
	{
		params -> step_x = 1;
		params -> side_x = (map_x + 1.0 - player.x) * params -> delta_x;
	}
	if (params -> ray_y < 0)
	{
		params -> step_y = -1;
		params -> side_y = (player.y - map_y) * params -> delta_y;
	}
	else
	{
		params -> step_y = 1;
		params -> side_y = (map_y + 1.0 - player.y) * params -> delta_y;
	}
}

static
void	update_params(t_params *params, int *map_y, int *map_x)
{
	if (params -> side_x < params -> side_y)
	{
		params -> side_x += params -> delta_x;
		*map_x += params -> step_x;
		params -> side = 0;
	}
	else
	{
		params -> side_y += params -> delta_y;
		*map_y += params -> step_y;
		params -> side = 1;
	}
}

double	dda(t_data *data, t_params *params, int *map_y, int *map_x)
{
	calculate_delta(params);
	calc_step_and_side_dist(data -> player, params, *map_y, *map_x);
	while (42)
	{
		update_params(params, map_y, map_x);
		if (data -> map.map[*map_y][*map_x] == DOOR)
		{
			params -> test = 1;
			break ;
		}
		params -> test = 0;
		if (data -> map.map[*map_y][*map_x] == WALL)
			break ;
	}
	if (params -> side == 0)
		return ((*map_x - data -> player.x + (1 - params -> step_x) / 2) \
					/ params -> ray_x);
	return ((*map_y - data -> player.y + (1 - params -> step_y) / 2) \
					/ params -> ray_y);
}
