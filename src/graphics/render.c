/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:46 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/17 19:51:50 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*load_image(t_game *game, char *path)
{
	void	*img;
	int		width;
	int		height;

	img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img)
	{
		ft_printf("Error: Failed to load image %s\n", path);
		return (NULL);
	}
	return (img);
}

void	draw_tile(t_game *game, void *img, int x, int y)
{
	if (!img)
	{
		ft_printf("Error: Failed to draw tile\n");
		return ;
	}
	mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y
		* TILE_SIZE);
}

static void	draw_tile_by_type(t_game *game, int i, int j)
{
	draw_tile(game, game->floor.img, j, i);
	if (game->map.map[i][j] == WALL)
		draw_tile(game, game->wall.img, j, i);
	else if (game->map.map[i][j] == COLLECTIBLE)
		draw_tile(game, game->collectible.img, j, i);
	else if (game->map.map[i][j] == EXIT)
		draw_tile(game, game->exit.img, j, i);
	else if (game->map.map[i][j] == PLAYER)
		draw_tile(game, game->player.img, j, i);
	else if (game->map.map[i][j] != FLOOR)
		ft_printf("Error: Invalid tile at (%d, %d)\n", j, i);
}

void	render_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			draw_tile_by_type(game, i, j);
			j++;
		}
		i++;
	}
	render_movements(game);
	mlx_do_sync(game->mlx);
}

void	render_movements(t_game *game)
{
	char	*str;

	str = ft_itoa(game->movements);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "Movements: ");
	mlx_string_put(game->mlx, game->win, 100, 20, 0xFFFFFF, str);
	free(str);
}
