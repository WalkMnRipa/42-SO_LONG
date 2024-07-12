/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:51:20 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/10 18:08:29 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

int	open_file(const char *filename, FILE **file)
{
	*file = fopen(filename, "r");
	if (!*file)
	{
		print_error("Cannot open file");
		return (0);
	}
	return (1);
}

int	check_line_length(char *line, t_map *map)
{
	int	line_length;

	line_length = strlen(line) - 1;
	if (map->width == 0)
		map->width = line_length;
	else if (line_length != map->width)
	{
		print_error("Map is not rectangular");
		return (0);
	}
	return (1);
}

// Fonction 1 -> check que la map est bien entourée de murs

int	ft_check_map_border(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
		{
			print_error("Map is not surrounded by walls");
			return (0);
		}
		i++;
	}
	j = 0;
	while (j < map->width)
	{
		if (map->map[0][j] != '1' || map->map[map->height - 1][j] != '1')
		{
			print_error("Map is not surrounded by walls");
			return (0);
		}
		j++;
	}
	return (1);
}

// Fonction 2 -> check que la map a un chemin valide de P à E

int	ft_check_path(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (map->map[y][x] == 'E')
		return (1);
	if (map->map[y][x] != '0' && map->map[y][x] != 'P')
		return (0);
	map->map[y][x] = 'P';
	if (ft_check_path(map, x + 1, y) || ft_check_path(map, x - 1, y)
		|| ft_check_path(map, x, y + 1) || ft_check_path(map, x, y - 1))
		return (1);
	return (0);
}
