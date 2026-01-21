/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:38:01 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/26 00:37:26 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_data *data)
{
	data -> mlx_ptr = mlx_init();
	if (!data -> mlx_ptr)
		return (EXIT_FAILURE);
	data -> win_ptr = mlx_new_window(data -> mlx_ptr, WIDTH, HEIGHT, "CubZer");
	if (!data -> win_ptr)
	{
		free(data -> mlx_ptr);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_map(t_data *data)
{
	data -> img = mlx_new_image(data -> mlx_ptr, WIDTH, HEIGHT);
	if (!data -> img)
		return (EXIT_FAILURE);
	data -> addr = mlx_get_data_addr(data -> img, \
					& data -> mlx.bits_per_pixel[MLX_IMG_MAP], \
					& data -> mlx.line_length[MLX_IMG_MAP], \
					& data -> mlx.endian);
	if (!data -> addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_minimap(t_data *data)
{
	data -> img_map = mlx_new_image(data -> mlx_ptr, \
						data -> map.width * BLOC_SIZE, \
						data -> map.height * BLOC_SIZE);
	if (!data -> img_map)
		return (EXIT_FAILURE);
	data -> map_addr = mlx_get_data_addr(data -> img_map, \
						& data -> mlx.bits_per_pixel[MLX_IMG_MINIMAP], \
						& data -> mlx.line_length[MLX_IMG_MINIMAP], \
						& data -> mlx.endian);
	if (!data -> map_addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_gameplay(t_data *data)
{
	const int	gameh = HEIGHT - (HEIGHT / 2);
	const int	gamew = WIDTH - (WIDTH / 4);

	data -> img_game = mlx_new_image(data -> mlx_ptr, gamew, gameh);
	if (!data -> img_game)
		return (EXIT_FAILURE);
	data -> game_addr = mlx_get_data_addr(data -> img_game, \
							& data -> mlx.bits_per_pixel[MLX_IMG_GAME], \
							& data -> mlx.line_length[MLX_IMG_GAME], \
							& data -> mlx.endian);
	if (!data -> game_addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
