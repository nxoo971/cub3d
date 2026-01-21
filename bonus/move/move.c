/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 03:25:06 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/29 19:35:29 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data, const int sign_y, const int sign_x)
{
	const double	x = data -> player.x;
	const double	y = data -> player.y;
	const double	move_y = (data -> params.dir_x * MOVE_SPEED) * sign_y;
	const double	move_x = (data -> params.dir_y * MOVE_SPEED) * sign_x;

	if (data -> map.map[(int)y][(int)(x + move_x)] != WALL)
		data -> player.x = x + move_x;
	if (data -> map.map[(int)(y + move_y)][(int)x] != WALL)
		data -> player.y = y + move_y;
}

void	move_player_side(t_data *data, const int sign_y, const int sign_x)
{
	const double	x = data -> player.x;
	const double	y = data -> player.y;
	const double	move_y = (data -> params.dir_x * MOVE_SPEED) * sign_y;
	const double	move_x = (data -> params.dir_y * MOVE_SPEED) * sign_x;

	if (data -> map.map[(int)y][(int)(x + move_y)] != WALL)
		data -> player.x = x + move_y;
	if (data -> map.map[(int)(y + move_x)][(int)x] != WALL)
		data -> player.y = y + move_x;
}

// inverser dir_y et dir_x
void	move_angle(t_data *data, const int sign)
{
	const double		oldir = data -> params.dir_x;
	const double		old_plane = data -> params.plane_x;
	const double		rotation_cos = cos(ROTATION_SPEED * sign);
	const double		rotation_sin = sin(ROTATION_SPEED * sign);
	t_params			*params;

	params = & data -> params;
	params -> dir_x = params -> dir_x * rotation_cos - params -> dir_y \
						* rotation_sin;
	params -> dir_y = oldir * rotation_sin + params -> dir_y * rotation_cos;
	params -> plane_x = params -> plane_x * rotation_cos - params -> plane_y \
							* rotation_sin;
	params -> plane_y = old_plane * rotation_sin + params -> plane_y \
							* rotation_cos;
}

//void    rotate_right(t_game *game)
//{
//    game->player.angle += 3.14 / ROTATION_SPEED_RATIO;
//    if (game->player.angle > 2 * M_PI)
//        game->player.angle -= 2 * M_PI;
//    game->player.dir_x = cos(game->player.angle) * MOVE_SPEED;
//    game->player.dir_y = sin(game->player.angle) * MOVE_SPEED;
//}

//void    rotate_left(t_game *game)
//{
//    game->player.angle -= 3.14 / ROTATION_SPEED_RATIO;
//    if (game->player.angle < 0)
//        game->player.angle += 2 * M_PI;
//    game->player.dir_x = cos(game->player.angle) * MOVE_SPEED;
//    game->player.dir_y = sin(game->player.angle) * MOVE_SPEED;
//}