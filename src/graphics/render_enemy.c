/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:03:55 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/27 01:16:32 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	render_enemy(t_game *game)
{
	draw_tile(game, game->enemy_img.img, game->enemy.position.x,
		game->enemy.position.y);
}

void	update_collectible_animation(t_game *game)
{
	static struct timeval	last_update = {0, 0};
	struct timeval			current_time;
	long					elapsed_microseconds;

	gettimeofday(&current_time, NULL);
	if (last_update.tv_sec == 0 && last_update.tv_usec == 0)
	{
		last_update = current_time;
		return ;
	}
	elapsed_microseconds = (current_time.tv_sec - last_update.tv_sec) * 1000000
		+ (current_time.tv_usec - last_update.tv_usec);
	if (elapsed_microseconds >= 100000)
	{
		game->current_collectible_frame = (game->current_collectible_frame + 1)
			% 3;
		last_update = current_time;
	}
}
