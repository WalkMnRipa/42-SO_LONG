/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:30 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/27 01:14:25 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	ft_check_map_elements(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < game->map.columns)
		{
			if (game->map.map[i][j] != WALL && game->map.map[i][j] != PLAYER
				&& game->map.map[i][j] != EXIT && game->map.map[i][j] != FLOOR
				&& game->map.map[i][j] != COLLECTIBLE)
			{
				ft_printf("Error: Invalid map element at (%d, %d): %c\n", j, i,
					game->map.map[i][j]);
				return (0);
			}
		}
	}
	return (1);
}

static int	ft_check_map_walls(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < game->map.columns)
		{
			if ((i == 0 || i == game->map.rows - 1 || j == 0
					|| j == game->map.columns - 1)
				&& game->map.map[i][j] != WALL)
			{
				ft_printf("Error: Invalid wall at (%d, %d)\n", j, i);
				return (0);
			}
		}
	}
	return (1);
}

static int	ft_check_required_elements(t_game *game)
{
	int	i;
	int	j;

	ft_init_map_elements(game);
	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < game->map.columns)
			ft_count_map_elements(game, i, j);
	}
	if (game->map.player.x == -1 || game->map.exit.x == 0
		|| game->map.collectibles == 0)
	{
		ft_printf("Error: Invalid number of elements (P: %d, E: %d, C: %d)\n",
			game->map.player.x, game->map.exit.x, game->map.collectibles);
		return (0);
	}
	return (1);
}

int	ft_validate_map(t_game *game)
{
	if (!ft_validate_map_dimensions(game))
		return (0);
	if (!ft_check_map_elements(game))
		return (0);
	if (!ft_check_map_walls(game))
		return (0);
	if (!ft_check_required_elements(game))
		return (0);
	return (1);
}

int	ft_is_map_playable(t_game *game)
{
	if (!ft_validate_map(game))
		return (0);
	return (ft_perform_flood_fill(game));
}
