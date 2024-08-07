/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:05:34 by jcohen            #+#    #+#             */
/*   Updated: 2024/08/07 14:28:02 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	ft_mark_as_visited(t_game *game, int x, int y,
		int *collectibles_found)
{
	if (game->map.map[y][x] == COLLECTIBLE)
		(*collectibles_found)++;
	game->map.map[y][x] = 'V';
}

static void	ft_flood_fill_recursive(t_game *game, int x, int y,
		int *collectibles_found)
{
	if (!ft_is_valid_position(game, x, y))
	{
		ft_printf("Invalid position (%d, %d)\n", x, y);
		return ;
	}
	if (game->map.map[y][x] == WALL || game->map.map[y][x] == 'V')
		return ;
	ft_mark_as_visited(game, x, y, collectibles_found);
	ft_flood_fill_recursive(game, x + 1, y, collectibles_found);
	ft_flood_fill_recursive(game, x - 1, y, collectibles_found);
	ft_flood_fill_recursive(game, x, y + 1, collectibles_found);
	ft_flood_fill_recursive(game, x, y - 1, collectibles_found);
}

int	ft_flood_fill(t_game *game)
{
	int	exit_found;
	int	collectibles_found;

	collectibles_found = 0;
	exit_found = 0;
	ft_flood_fill_recursive(game, game->map.player.x, game->map.player.y,
		&collectibles_found);
	if (game->map.map[game->map.exit.y][game->map.exit.x] == 'V')
		exit_found = 1;
	return (collectibles_found == game->map.collectibles && exit_found);
}

int	ft_perform_flood_fill(t_game *game)
{
	char	**temp_map;
	int		is_playable;

	temp_map = ft_copy_map(game);
	if (!temp_map)
		return (0);
	is_playable = ft_flood_fill(game);
	ft_restore_map(game, temp_map);
	if (!is_playable)
		ft_printf("Error: Map is not playable\n");
	return (is_playable);
}
