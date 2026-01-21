/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 00:35:35 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/29 19:20:15 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static
void	draw_buff(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			((int *)data->addr)[y * WIDTH + x] = data->buf[y][x];
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

static
void	loop(t_data *data)
{
	double	perp_wall_dist;
	int		line_height;
	int		x;
	int		*p_yx;

	x = -1;
	while (++x < WIDTH)
	{
		p_yx = (int [2]){(int)data -> player.y, (int)data -> player.x};
		data -> params.ray_x = data -> params.dir_y + data -> params.plane_y \
								* (2 * x / (double)WIDTH - 1);
		data -> params.ray_y = data -> params.dir_x + data -> params.plane_x \
								* (2 * x / (double)WIDTH - 1);
		perp_wall_dist = dda(data, & data -> params, & p_yx[0], & p_yx[1]);
		line_height = (int)(HEIGHT / perp_wall_dist);
		data -> params.draw_start = -line_height / 2 + HEIGHT / 2;
		if (data -> params.draw_start < 0)
			data -> params.draw_start = 0;
		data -> params.draw_end = line_height / 2 + HEIGHT / 2;
		if (data -> params.draw_end >= HEIGHT)
			data -> params.draw_end = HEIGHT - 1;
		begin_textures(data, x, perp_wall_dist, line_height);
		data->zbuffer[x] = perp_wall_dist;
	}
}

void	draw_gameplay(t_data *data)
{
	int	i;

	i = -1;
	data->params.test = 0;
	while (++i < data->map.nb_door)
		check_door(&data -> player, &data->map, data->map.door[i]);
	loop(data);
	begin_sprite(data, &data->player, &data->params);
	mini_map(data);
	draw_buff(data);
}
