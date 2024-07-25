/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:43 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/25 20:03:06 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	init_game(t_game *game)
{
	game->window_width = game->map.columns * TILE_SIZE;
	game->window_height = game->map.rows * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "so_long");
	if (!game->win)
	{
		ft_printf("Error: Failed to create window\n");
		return (0);
	}
	game->movements = 0;
	game->victory = false;
	game->player_direction = PLAYER_FRONT;
	return (1);
}

int	load_images(t_game *game)
{
	game->floor.img = load_image(game, "textures/floor.xpm");
	game->wall.img = load_image(game, "textures/wall.xpm");
	game->collectible.img = load_image(game, "textures/collectible.xpm");
	game->exit.img = load_image(game, "textures/exit.xpm");
	game->player_images[PLAYER_FRONT].img = load_image(game,
			"textures/player_front.xpm");
	game->player_images[PLAYER_BACK].img = load_image(game,
			"textures/player_back.xpm");
	game->player_images[PLAYER_LEFT].img = load_image(game,
			"textures/player_left.xpm");
	game->player_images[PLAYER_RIGHT].img = load_image(game,
			"textures/player_right.xpm");
	game->enemy_img.img = load_image(game, "textures/enemy.xpm");
	if (!game->floor.img || !game->wall.img || !game->collectible.img
		|| !game->exit.img || !game->player_images[PLAYER_FRONT].img
		|| !game->player_images[PLAYER_BACK].img
		|| !game->player_images[PLAYER_LEFT].img
		|| !game->player_images[PLAYER_RIGHT].img || !game->enemy_img.img)
	{
		ft_printf("Error: Failed to load images\n");
		return (0);
	}
	return (1);
}

void	init_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.map[i][j] == PLAYER)
			{
				game->map.player.x = j;
				game->map.player.y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	*get_player_image(t_game *game)
{
	return (game->player_images[game->player_direction].img);
}
