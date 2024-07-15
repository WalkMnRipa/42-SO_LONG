/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:43 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/13 22:28:54 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->window_width = game->map.columns * TILE_SIZE;
	game->window_height = game->map.rows * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "so_long");
	if (!game->win)
	{
		free(game->mlx);
		return (0);
	}
	game->movements = 0;
	game->victory = false;
	return (1);
}

int	load_images(t_game *game)
{
	int width, height;

	game->floor.img = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
			&width, &height);
	game->wall.img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&width, &height);
	game->collectible.img = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &width, &height);
	game->exit.img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&width, &height);
	game->player.img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&width, &height);

	if (!game->floor.img || !game->wall.img || !game->collectible.img
		|| !game->exit.img || !game->player.img)
		return (0);
	return (1);
}