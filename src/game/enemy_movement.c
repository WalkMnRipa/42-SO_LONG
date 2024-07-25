/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:11:55 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/25 21:00:17 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	init_enemy(t_game *game)
{
	int	x;
	int	y;

	y = 1;
	while (y < game->map.rows - 1)
	{
		x = 1;
		while (x < game->map.columns - 1)
		{
			if (game->map.map[y][x] == FLOOR)
			{
				game->enemy.position.x = x;
				game->enemy.position.y = y;
				game->enemy.direction = 1;
				if (game->map.map[y + 1][x] == FLOOR && game->map.map[y
					- 1][x] == FLOOR)
					game->enemy.is_vertical = true;
				else
					game->enemy.is_vertical = false;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	move_enemy(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->enemy.position.x;
	new_y = game->enemy.position.y;
	if (game->enemy.is_vertical)
		new_y += game->enemy.direction;
	else
		new_x += game->enemy.direction;
	if (ft_is_valid_position(game, new_x, new_y)
		&& game->map.map[new_y][new_x] == FLOOR)
	{
		game->enemy.position.x = new_x;
		game->enemy.position.y = new_y;
	}
	else
		game->enemy.direction *= -1;
}
