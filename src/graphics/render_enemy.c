/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:03:55 by jcohen            #+#    #+#             */
/*   Updated: 2024/08/06 16:55:52 by jcohen           ###   ########.fr       */
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
	static int	frames = 0;

	frames++;
	if (frames >= FRAMES_PER_ANIMATION)
	{
		game->current_collectible_frame = (game->current_collectible_frame + 1)
			% 3;
		frames = 0;
	}
}
