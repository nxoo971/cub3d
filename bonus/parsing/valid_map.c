/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:55:04 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/28 02:03:24 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static
char	*skip_emptyline(const int fd)
{
	char	*line;
	int		tmp;
	int		i;

	tmp = 1;
	line = 0;
	while (tmp || (line && *line))
	{
		tmp = 0;
		line = readfile(fd, true);
		if (!line)
			break ;
		i = -1;
		while (ft_isspace(line[++i]))
			;
		if (line[i])
			return (line);
	}
	ft_memdel((void **)& line);
	return (0);
}

static
int	readmap(t_map *map, t_player *player, int fd)
{
	static char	*tmp_map = 0;

	tmp_map = skip_emptyline(fd);
	if (!tmp_map)
		return (EXIT_FAILURE);
	return (stock_map(map, player, fd, tmp_map));
}

static
int	readinfos(t_map *map, t_player *player, int fd)
{
	char	*line;

	line = readfile(fd, true);
	while (line)
	{
		if (parse_line(line, map))
		{
			ft_memdel((void **)& line);
			return (ft_printf("{blue}parse line: {red}FAILED{reset}\n"));
		}
		if (textures_is_set(map))
		{
			ft_memdel((void **)& line);
			return (readmap(map, player, fd));
		}
		ft_memdel((void **)& line);
		line = readfile(fd, true);
	}
	ft_memdel((void **)& line);
	return (EXIT_SUCCESS);
}

static
int	check_extension(const char *filename)
{
	const size_t	size = ft_strlen(filename);
	const size_t	ext_size = ft_strlen(EXTENSION);

	if (size >= 4)
		return (ft_strcmp((filename + size) - ext_size, EXTENSION));
	return (EXIT_FAILURE);
}

int	parse_map(t_map *map, t_player *player)
{
	int	fd;

	if (check_extension(map->filename))
		return (ft_printf("{blue}Extension: {red}FAILED{reset}\n"));
	fd = open(map -> filename, O_RDONLY, 0644);
	if (fd == -1)
		return (ft_printf("{blue}Opening file: {red}FAILED{reset}\n"));
	if (readinfos(map, player, fd))
	{
		close(fd);
		return (ft_printf("{blue}read map: {red}FAILED{reset}\n"));
	}
	close(fd);
	if (surrounded_by_walls(map -> map, player -> p))
		return (ft_printf("{blue}surrounded by walls: {red}FAILED{reset}\n"));
	return (EXIT_SUCCESS);
}
