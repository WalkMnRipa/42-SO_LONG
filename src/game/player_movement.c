/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:27:47 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/27 01:09:27 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	check_collision(t_game *game, int x, int y)
{
	return (game->map.map[y][x] != WALL);
}

int	check_enemy_collision(t_game *game)
{
	return (game->map.player.x == game->enemy.position.x
		&& game->map.player.y == game->enemy.position.y);
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map.map[game->map.player.y][game->map.player.x] = FLOOR;
	game->map.player.x = new_x;
	game->map.player.y = new_y;
	game->map.map[new_y][new_x] = PLAYER;
	game->movements++;
}

static void	update_player_direction(t_game *game, int dx, int dy)
{
	if (dx > 0)
		game->player_direction = PLAYER_RIGHT;
	else if (dx < 0)
		game->player_direction = PLAYER_LEFT;
	else if (dy > 0)
		game->player_direction = PLAYER_FRONT;
	else if (dy < 0)
		game->player_direction = PLAYER_BACK;
}

int	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player.x + dx;
	new_y = game->map.player.y + dy;
	if (!check_collision(game, new_x, new_y))
		return (0);
	update_player_direction(game, dx, dy);
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
	if (check_enemy_collision(game))
		return (exit_game(game));
	return (1);
}
