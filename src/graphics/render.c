/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:46 by jcohen            #+#    #+#             */
/*   Updated: 2024/08/11 18:21:20 by jcohen           ###   ########.fr       */
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
	if (game->map.map[i][j] == FLOOR)
		draw_tile(game, game->floor.img, j, i);
	if (game->map.map[i][j] == WALL)
		draw_tile(game, game->wall.img, j, i);
	else if (game->map.map[i][j] == COLLECTIBLE)
		draw_tile(game,
			game->collectible_frames[game->current_collectible_frame].img, j,
			i);
	else if (game->map.map[i][j] == EXIT)
		draw_tile(game, game->exit.img, j, i);
	else if (game->map.map[i][j] == PLAYER)
		draw_player(game, j, i);
	else if (game->map.map[i][j] != FLOOR)
		ft_printf("Error: Invalid tile at (%d, %d)\n", j, i);
}

void	draw_player(t_game *game, int x, int y)
{
	void	*player_img;

	if (game->player_direction >= PLAYER_FRONT
		&& game->player_direction <= PLAYER_RIGHT)
		player_img = game->player_images[game->player_direction].img;
	else
		player_img = game->player_images[PLAYER_FRONT].img;
	draw_tile(game, player_img, x, y);
}

void	render_map(t_game *game)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
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
	render_enemy(game);
	str = ft_itoa(game->movements);
	mlx_string_put(game->mlx, game->win, 5, 10, 0xFFFFFF, str);
	free(str);
	mlx_do_sync(game->mlx);
}
