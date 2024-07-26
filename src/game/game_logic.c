/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:42 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/26 23:18:12 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

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
		exit_game(game);
	render_map(game);
	if (game->victory)
		display_victory_message(game);
	return (0);
}

void	display_victory_message(t_game *game)
{
	char	*message;
	int		text_width;
	int		x;
	int		y;

	message = "You WIN!";
	text_width = ft_strlen(message) * 10;
	x = (game->window_width - text_width) / 2;
	y = game->window_height / 2;
	mlx_clear_window(game->mlx, game->win);
	mlx_string_put(game->mlx, game->win, x, y, 0xFFFFFF, message);
	ft_printf("Movements: %d\n", game->movements);
	ft_printf("YOU WIN!\n");
	mlx_do_sync(game->mlx);
	usleep(3000000);
	ft_cleanup(game);
	exit(0);
}

int	game_loop(t_game *game)
{
	static int	frames = 0;

	frames++;
	if (frames % 150 == 0)
		move_enemy(game);
	if (check_enemy_collision(game))
	{
		ft_printf("GAME OVER !!\n");
		return (exit_game(game));
	}
	render_map(game);
	return (0);
}
