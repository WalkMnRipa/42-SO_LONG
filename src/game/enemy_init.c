/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:26:12 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/26 23:37:50 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	count_valid_spawn_positions(t_game *game)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 1;
	while (y < game->map.rows - 1)
	{
		x = 1;
		while (x < game->map.columns - 1)
		{
			if (game->map.map[y][x] == FLOOR && (x != game->map.player.x
					|| y != game->map.player.y))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static bool	find_and_set_enemy_position(t_game *game, int target_position)
{
	int	current_position;
	int	x;
	int	y;

	current_position = 0;
	y = 1;
	while (y < game->map.rows - 1)
	{
		x = 1;
		while (x < game->map.columns - 1)
		{
			if (game->map.map[y][x] == FLOOR && (x != game->map.player.x
					|| y != game->map.player.y))
			{
				if (current_position++ == target_position)
					return (game->enemy.position.x = x,
						game->enemy.position.y = y, true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

static void	place_enemy_at_random_position(t_game *game, int valid_positions)
{
	int	random_floor;

	random_floor = rand() % valid_positions;
	if (!find_and_set_enemy_position(game, random_floor))
	{
		ft_printf("Error\nFailed to place enemy at random position\n");
		exit_game(game);
	}
}

static void	set_random_enemy_direction(t_game *game)
{
	game->enemy.direction = (rand() % 2 == 0) - 1;
	game->enemy.is_vertical = rand() % 2 == 0;
}

void	init_enemy_random(t_game *game)
{
	int			valid_spawn_positions;
	static int	seed = 0;

	if (!seed)
	{
		seed = 1;
		srand(time(NULL));
	}
	valid_spawn_positions = count_valid_spawn_positions(game);
	if (valid_spawn_positions == 0)
	{
		ft_printf("Error\nNo valid spawn positions for the enemy\n");
		exit_game(game);
	}
	place_enemy_at_random_position(game, valid_spawn_positions);
	set_random_enemy_direction(game);
}
