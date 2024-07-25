/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:03:55 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/25 21:00:25 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	render_enemy(t_game *game)
{
	draw_tile(game, game->enemy_img.img, game->enemy.position.x,
		game->enemy.position.y);
}
