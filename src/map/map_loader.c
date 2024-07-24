/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:01 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/17 20:47:41 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	ft_allocate_map(t_game *game, char *filename)
{
	game->map.rows = ft_count_rows(filename);
	if (game->map.rows <= 0)
	{
		ft_printf("Error: Invalid number of rows: %d\n", game->map.rows);
		return (0);
	}
	game->map.map = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!game->map.map)
	{
		ft_printf("Error: Failed to allocate memory for map\n");
		return (0);
	}
	return (1);
}

static int	ft_read_map_line(t_game *game, char *line, int i)
{
	game->map.map[i] = ft_strdup(line);
	if (!game->map.map[i])
		return (0);
	if (game->map.map[i][(int)ft_strlen(game->map.map[i]) - 1] == '\n')
		game->map.map[i][(int)ft_strlen(game->map.map[i]) - 1] = '\0';
	return (1);
}

static int	ft_process_map_lines(t_game *game, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_read_map_line(game, line, i))
		{
			ft_free_map(game);
			free(line);
			return (-1);
		}
		free(line);
		i++;
	}
	game->map.map[i] = NULL;
	return (i);
}

int	load_map(t_game *game, char *filename)
{
	int	fd;
	int	lines_read;

	if (!ft_allocate_map(game, filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	lines_read = ft_process_map_lines(game, fd);
	close(fd);
	if (lines_read == -1)
		return (0);
	game->map.columns = (int)ft_strlen(game->map.map[0]);
	game->map.rows = lines_read;
	return (1);
}
