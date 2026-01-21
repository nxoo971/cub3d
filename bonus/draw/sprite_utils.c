/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:42:27 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/30 00:05:42 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static
void	assign(t_data *data, char **map, const int i, const int j)
{
	static const int	values[2] = {8, 10};

	if (map[i][j] == DOOR)
	{
		data -> map.door[data -> map.nb_door].x = j;
		data -> map.door[data -> map.nb_door].y = i;
		data -> map.nb_door++;
	}
	if (map[i][j] == ITEM)
	{
		data -> sprite[data -> numsprite].x = j + 0.5;
		data -> sprite[data -> numsprite].y = i + 0.5;
		data -> sprite[data -> numsprite].texture = values[j % 2 == 0];
		data -> numsprite++;
	}
}

bool	parse_sprite(t_data *data, char **map)
{
	int					i;
	int					j;

	i = -1;
	data -> map.nb_door = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			assign(data, map, i, j);
		}
	}
	return (data -> numsprite > 0 || data -> map.nb_door > 0);
}

void	sprite_cast3(t_data *data, t_player *player, t_params *p, int i)
{
	p->sprite_y = data->sprite[data->sprite_ord[i]].x - player->x;
	p->sprite_x = data->sprite[data->sprite_ord[i]].y - player->y;
	p->invdet = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	p->transform_x = p->invdet \
	*(p->dir_y * p->sprite_x - p->dir_x * p->sprite_y);
	p->transform_y = p->invdet * (-p->plane_y * p->sprite_x + \
		p->plane_x * p->sprite_y);
	p->sprite_screen_x = (int)((WIDTH / 2) * (1 + p->transform_x \
		/ p->transform_y));
	p->vmovescreen = (int)(VMOVE / p->transform_y);
	p->sprite_height = (int)fabs((HEIGHT / p->transform_y) / VDIV);
	p->draw_start_y = -p->sprite_height / 2 + HEIGHT / 2 + p->vmovescreen;
}
