/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:58 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/17 21:27:32 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	ft_print_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		ft_printf("%s\n", game->map.map[i]);
		i++;
	}
}

int	ft_is_valid_position(t_game *game, int x, int y)
{
	return (x >= 0 && y >= 0 && x < game->map.columns && y < game->map.rows);
}

int	ft_count_rows(char *filename)
{
	char	*line;
	int		fd;
	int		rows;

	rows = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		rows++;
		free(line);
	}
	close(fd);
	return (rows);
}

void	ft_count_map_elements(t_game *game, int i, int j)
{
	if (game->map.map[i][j] == COLLECTIBLE)
		game->map.collectibles++;
	else if (game->map.map[i][j] == PLAYER)
	{
		game->map.player.x = j;
		game->map.player.y = i;
	}
	else if (game->map.map[i][j] == EXIT)
	{
		game->map.exit.x = j;
		game->map.exit.y = i;
	}
}

int	ft_validate_map_dimensions(t_game *game)
{
	if (game->map.rows <= 0 || game->map.columns <= 0)
	{
		ft_printf("Error: Invalid map dimensions (rows %d, columns: %d)\n",
			game->map.rows, game->map.columns);
		return (0);
	}
	return (1);
}
