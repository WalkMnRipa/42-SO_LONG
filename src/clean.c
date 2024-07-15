/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:47 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/13 22:35:11 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map(t_map *map)
{
	int	i;

	if (map->map)
	{
		for (i = 0; i < map->rows; i++)
		{
			if (map->map[i])
				free(map->map[i]);
		}
		free(map->map);
	}
}

void	destroy_images(t_game *game)
{
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->collectible.img)
		mlx_destroy_image(game->mlx, game->collectible.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->player.img)
		mlx_destroy_image(game->mlx, game->player.img);
}

void	cleanup(t_game *game)
{
	if (game->map.map)
	{
		int i = 0;
		while (i < game->map.rows)
		{
			if (game->map.map[i])
				free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
	}

	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);

		// Libérer les images si elles ont été chargées
		if (game->floor.img)
			mlx_destroy_image(game->mlx, game->floor.img);
		if (game->wall.img)
			mlx_destroy_image(game->mlx, game->wall.img);
		if (game->collectible.img)
			mlx_destroy_image(game->mlx, game->collectible.img);
		if (game->exit.img)
			mlx_destroy_image(game->mlx, game->exit.img);
		if (game->player.img)
			mlx_destroy_image(game->mlx, game->player.img);

		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}