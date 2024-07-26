/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:11:55 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/27 01:15:17 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	update_enemy_direction(t_game *game)
{
	int	player_dx;
	int	player_dy;

	player_dx = game->map.player.x - game->enemy.position.x;
	player_dy = game->map.player.y - game->enemy.position.y;
	if (abs(player_dx) > abs(player_dy))
	{
		game->enemy.is_vertical = false;
		if (player_dx > 0)
			game->enemy.direction = 1;
		else
			game->enemy.direction = -1;
	}
	else
	{
		game->enemy.is_vertical = true;
		if (player_dy > 0)
			game->enemy.direction = 1;
		else
			game->enemy.direction = -1;
	}
}

static bool	try_move_enemy(t_game *game, int new_x, int new_y)
{
	if (!ft_is_valid_position(game, new_x, new_y))
		return (false);
	if (game->map.map[new_y][new_x] != FLOOR && (new_x != game->map.player.x
			|| new_y != game->map.player.y))
		return (false);
	game->enemy.position.x = new_x;
	game->enemy.position.y = new_y;
	return (true);
}

void	move_enemy(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->enemy.position.x;
	new_y = game->enemy.position.y;
	update_enemy_direction(game);
	if (game->enemy.is_vertical)
		new_y += game->enemy.direction;
	else
		new_x += game->enemy.direction;
	if (!try_move_enemy(game, new_x, new_y))
	{
		game->enemy.is_vertical = !game->enemy.is_vertical;
		new_x = game->enemy.position.x;
		new_y = game->enemy.position.y;
		if (game->enemy.is_vertical)
			new_y += game->enemy.direction;
		else
			new_x += game->enemy.direction;
		try_move_enemy(game, new_x, new_y);
	}
	else if (check_enemy_collision(game))
		exit_game(game);
}
