/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrounded_by_walls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 01:10:20 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/30 00:25:45 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static
bool	isok_vertical(char **map, int y, int x, int add)
{
	int	i;

	i = y;
	while (i >= 0 && map[i])
	{
		if (map[i][x] == WALL)
			return (true);
		i += add;
	}
	return (false);
}

static
bool	isok_horizontal(const char *line, int x, int add)
{
	int	i;

	i = x;
	while (i >= 0 && line[i])
	{
		if (line[i] == WALL)
			return (true);
		i += add;
	}
	return (false);
}

static
bool	isok_chars(const char c)
{
	static const char	chars[6] = {
		WALL, BLANK, NORTH, WEST, EAST, SOUTH
	};
	int					i;

	i = -1;
	while (chars[++i])
		if (c == chars[i])
			return (true);
	return (false);
}

static
bool	isok(char **map, const size_t y, const size_t x)
{
	return ((ft_strlen(map[y - 1]) >= x && (isok_chars(map[y - 1][x]) \
		|| (map[y - 1][x] == BLANK && isok_vertical(map, y - 1, x, -1))))
			&& (ft_strlen(map[y + 1]) >= x && (isok_chars(map[y + 1][x]) \
		|| (map[y + 1][x] == BLANK && isok_vertical(map, y + 1, x, +1))))
			&& (isok_chars(map[y][x - 1]) \
		|| (map[y][x - 1] == BLANK && isok_horizontal(map[y], x - 1, -1)))
			&& (isok_chars(map[y][x + 1]) || \
		(map[y][x + 1] == BLANK && isok_horizontal(map[y], x + 1, +1))));
}

bool	surrounded_by_walls(char **map, const char perso)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == BLANK || map[i][j] == perso)
			{
				if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1]
					|| !isok(map, i, j))
				{
					ft_printf(\
		"{blue}surrounded by walls: {red}Failed at: %lu:%lu{reset}\n", i, j);
					return (EXIT_FAILURE);
				}
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
