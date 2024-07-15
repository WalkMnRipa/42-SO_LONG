/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:45 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/13 22:56:26 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	count_rows(char *filename)
{
	char	*line;

	int fd, rows = 0;
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

int	load_map(t_game *game, char *filename)
{
	char	*line;

	int fd, i = 0;
	game->map.rows = count_rows(filename);
	if (game->map.rows <= 0)
		return (0);
	game->map.map = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!game->map.map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map.map[i] = ft_strdup(line);
		if (!game->map.map[i])
		{
			while (i > 0)
				free(game->map.map[i--]);
			free(game->map.map);
			free(line);
			close(fd);
			return (0);
		}
		if (game->map.map[i][(int)ft_strlen(game->map.map[i]) - 1] == '\n')
			game->map.map[i][(int)ft_strlen(game->map.map[i]) - 1] = '\0';
		free(line);
		i++;
	}
	game->map.map[i] = NULL;
	close(fd);
	game->map.columns = (int)ft_strlen(game->map.map[0]);
	return (1);
}

void	ft_print_map(t_game *game)
{
	int	i;

	ft_printf("Map contents:\n");
	i = 0;
	while (i < game->map.rows)
	{
		ft_printf("%s", game->map.map[i]);
		if (game->map.map[i][ft_strlen(game->map.map[i]) - 1] != '\n')
			ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

int	validate_map(t_game *game)
{
	int		first_row_length;
	char	current;

	int i, j, player, exit, collectibles;
	i = 0;
	player = 0;
	exit = 0;
	collectibles = 0;
	first_row_length = ft_strlen(game->map.map[0]);
	while (i < game->map.rows)
	{
		if ((int)ft_strlen(game->map.map[i]) != first_row_length)
		{
			ft_printf("Error: Map is not rectangular (row %d)\n", i + 1);
			return (0);
		}
		j = 0;
		while (j < game->map.columns)
		{
			current = game->map.map[i][j];
			if (i == 0 || i == game->map.rows - 1 || j == 0
				|| j == game->map.columns - 1)
			{
				if (current != WALL)
				{
					ft_printf("Error: Map not by walls at (%d,% d)\n ", i, j);
					return (0);
				}
			}
			if (current == PLAYER)
			{
				player++;
				game->map.player.x = j;
				game->map.player.y = i;
			}
			else if (current == EXIT)
			{
				exit++;
				game->map.exit.x = j;
				game->map.exit.y = i;
			}
			else if (current == COLLECTIBLE)
			{
				collectibles++;
			}
			else if (current != FLOOR && current != WALL)
			{
				ft_printf("Error: Invalid character '%c' in map at (%d, %d)\n",
					current, i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	game->map.collectibles = collectibles;
	if (player != 1 || exit != 1 || collectibles < 1)
	{
		ft_printf("Error: Invalid number of elements (P: %d, E: %d, C: %d)\n",
			player, exit, collectibles);
		return (0);
	}
	ft_printf("Map validation successful\n");
	return (1);
}

int	flood_fill(t_game *game, int x, int y, int *collectibles)
{
	char	original;
	int		reachable;

	if (game->map.map[y][x] == WALL || game->map.map[y][x] == 'V')
		return (0);
	if (game->map.map[y][x] == COLLECTIBLE)
		(*collectibles)--;
	else if (game->map.map[y][x] == EXIT)
		return (1);
	original = game->map.map[y][x];
	game->map.map[y][x] = 'V';
	reachable = flood_fill(game, x + 1, y, collectibles) || flood_fill(game, x
			- 1, y, collectibles) || flood_fill(game, x, y + 1, collectibles)
		|| flood_fill(game, x, y - 1, collectibles);
	game->map.map[y][x] = original;
	return (reachable);
}

int	is_map_playable(t_game *game)
{
	int collectibles = game->map.collectibles;
	int exit_reachable = flood_fill(game, game->map.player.x,
			game->map.player.y, &collectibles);

	return (exit_reachable && collectibles == 0);
}