/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:48:11 by rferradi          #+#    #+#             */
/*   Updated: 2023/03/30 00:02:58 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	malloc_sprite(t_data *data)
{
	if (!parse_sprite(data, data->map.map))
		return (EXIT_SUCCESS);
	data -> sprite_ord = malloc(sizeof(int) * data -> numsprite);
	data -> sprite_dis = malloc(sizeof(double) * data -> numsprite);
	return (!(data -> sprite_ord && data -> sprite_dis));
}

void	sprite_casting(t_data *data, t_player *player)
{
	int	i;

	i = -1;
	while (++i < data->numsprite)
	{
		data->sprite_ord[i] = i;
		data->sprite_dis[i] = ((player->x - data->sprite[i].x) * \
			(player->x - data->sprite[i].x) + (player->y - data->sprite[i].y) \
			* (player->y - data->sprite[i].y));
	}
}

void	sprite_cast2(t_data *data, t_player *player, t_params *p, int i)
{
	sprite_cast3(data, player, p, i);
	if (p->draw_start_y < 0)
		p->draw_start_y = 0;
	p->draw_end_y = p->sprite_height / 2 + HEIGHT / 2 + p->vmovescreen;
	if (p->draw_end_y >= HEIGHT)
		p->draw_end_y = HEIGHT - 1;
	p->sprite_width = (int)fabs((HEIGHT / p->transform_y) / UDIV);
	p->draw_start_x = -p->sprite_width / 2 + p->sprite_screen_x;
	if (p->draw_start_x < 0)
		p->draw_start_x = 0;
	p->draw_end_x = p->sprite_width / 2 + p->sprite_screen_x;
	if (p->draw_end_x >= WIDTH)
		p->draw_end_x = WIDTH - 1;
}

void	cast_sprite(t_data *data, t_params *p, int stripe, int i)
{
	int	y;
	int	d;

	y = p->draw_start_y;
	while (y < p->draw_end_y)
	{
		d = (y - p->vmovescreen) * 256 - HEIGHT * 128 + p->sprite_height * 128;
		p->tex_y = ((d * TEXTURE_HEIGHT) / p->sprite_height) / 256;
		p->color = ((int **)data->texture) \
			[data->sprite[data->sprite_ord[i]].texture] \
			[TEXTURE_WIDTH * p->tex_y + p->tex_x];
		if ((p->color & 0x00FFFFFF) != 0)
			data->buf[y][stripe] = p->color;
		y++;
	}
}

void	begin_sprite(t_data *data, t_player *player, t_params *p)
{
	int	i;
	int	stripe;

	sprite_casting(data, player);
	i = -1;
	while (++i < data->numsprite)
	{
		sprite_cast2(data, player, p, i);
		stripe = p->draw_start_x;
		while (stripe < p->draw_end_x)
		{
			p->tex_x = (int)((256 * (stripe - \
				(-p->sprite_width / 2 + p->sprite_screen_x)) \
					* TEXTURE_WIDTH / p->sprite_width) / 256);
			if (p->transform_y > 0 && stripe > 0 \
				&& stripe < WIDTH && p->transform_y < data->zbuffer[stripe])
				cast_sprite(data, p, stripe, i);
			stripe++;
		}
	}
}
