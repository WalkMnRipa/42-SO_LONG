/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:42 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/13 22:27:53 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player.x + dx;
	new_y = game->map.player.y + dy;
	if (game->map.map[new_y][new_x] == WALL)
		return (0);
	if (game->map.map[new_y][new_x] == COLLECTIBLE)
	{
		game->map.collectibles--;
		game->map.map[new_y][new_x] = FLOOR;
	}
	if (game->map.map[new_y][new_x] == EXIT)
	{
		if (game->map.collectibles > 0)
			return (0);
		game->victory = true;
		return (1);
	}
	game->map.map[game->map.player.y][game->map.player.x] = FLOOR;
	game->map.player.x = new_x;
	game->map.player.y = new_y;
	game->map.map[new_y][new_x] = PLAYER;
	game->movements++;
	return (1);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	else if (keycode == KEY_ESC)
	{
		cleanup(game);
		exit(0);
	}
	render_map(game);
	render_movements(game);
	if (game->victory)
		display_victory_message(game);
	return (0);
}
