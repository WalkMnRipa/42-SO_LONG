/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:27:47 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/17 17:22:31 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	check_collision(t_game *game, int x, int y)
{
	return (game->map.map[y][x] != WALL);
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map.map[game->map.player.y][game->map.player.x] = FLOOR;
	game->map.player.x = new_x;
	game->map.player.y = new_y;
	game->map.map[new_y][new_x] = PLAYER;
	game->movements++;
}

int	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player.x + dx;
	new_y = game->map.player.y + dy;
	if (!check_collision(game, new_x, new_y))
		return (0);
	if (game->map.map[new_y][new_x] == COLLECTIBLE)
	{
		game->map.collectibles--;
		game->map.map[new_y][new_x] = FLOOR;
	}
	else if (game->map.map[new_y][new_x] == EXIT)
	{
		if (game->map.collectibles > 0)
			return (0);
		game->victory = true;
		return (1);
	}
	update_player_position(game, new_x, new_y);
	return (1);
}
