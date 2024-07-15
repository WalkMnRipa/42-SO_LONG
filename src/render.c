/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:46 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/13 22:15:24 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	draw_tile(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y
		* TILE_SIZE);
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
			draw_tile(game, game->floor.img, j, i);
			if (game->map.map[i][j] == WALL)
				draw_tile(game, game->wall.img, j, i);
			else if (game->map.map[i][j] == COLLECTIBLE)
				draw_tile(game, game->collectible.img, j, i);
			else if (game->map.map[i][j] == EXIT)
				draw_tile(game, game->exit.img, j, i);
			else if (game->map.map[i][j] == PLAYER)
				draw_tile(game, game->player.img, j, i);
			j++;
		}
		i++;
	}
}

void	render_movements(t_game *game)
{
	char	*str;

	str = ft_itoa(game->movements);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "Movements: ");
	mlx_string_put(game->mlx, game->win, 100, 20, 0xFFFFFF, str);
	free(str);
}

void	display_victory_message(t_game *game)
{
	char	*message;
	int		x;
	int		y;
	int		text_width;

	message = "You Win!";
	text_width = ft_strlen(message) * 10;
	x = (game->window_width - text_width) / 2;
	y = game->window_height / 2;
	mlx_clear_window(game->mlx, game->win);
	mlx_string_put(game->mlx, game->win, x, y, 0xFFFFFF, message);
	ft_printf("Movements: %d\n", game->movements);
	ft_printf("YOU WIN!\n");
	mlx_do_sync(game->mlx);
	usleep(3000000);
	cleanup(game);
	exit(0);
}
