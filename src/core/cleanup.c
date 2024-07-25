/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:47 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/25 20:38:21 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	ft_free_map(t_game *game)
{
	int	i;

	if (!game || !game->map.map)
		return ;
	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.map[i])
			free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
	game->map.map = NULL;
}

void	ft_destroy_images(t_game *game)
{
	int	i;

	i = PLAYER_FRONT;
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->collectible.img)
		mlx_destroy_image(game->mlx, game->collectible.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->enemy_img.img)
		mlx_destroy_image(game->mlx, game->enemy_img.img);
	while (i <= PLAYER_RIGHT)
	{
		if (game->player_images[i].img)
			mlx_destroy_image(game->mlx, game->player_images[i].img);
		i++;
	}
}

void	ft_cleanup(t_game *game)
{
	if (!game)
		return ;
	ft_free_map(game);
	ft_destroy_images(game);
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	exit_game(t_game *game)
{
	ft_printf("Exiting game...\n");
	ft_cleanup(game);
	exit(0);
	return (0);
}
