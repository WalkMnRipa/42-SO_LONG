/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:05:46 by jcohen            #+#    #+#             */
/*   Updated: 2024/08/11 18:15:11 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

char	**ft_copy_map(t_game *game)
{
	char	**temp_map;
	int		i;

	temp_map = (char **)malloc(sizeof(char *) * (game->map.rows + 1));
	if (!temp_map)
		return (NULL);
	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.map[i] == NULL)
			break ;
		temp_map[i] = ft_strdup(game->map.map[i]);
		if (!temp_map[i])
		{
			while (i > 0)
				free(temp_map[i--]);
			free(temp_map);
			return (NULL);
		}
		i++;
	}
	temp_map[i] = NULL;
	return (temp_map);
}

void	ft_restore_map(t_game *game, char **temp_map)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if (temp_map[i] == NULL)
			break ;
		ft_strncpy(game->map.map[i], temp_map[i], game->map.columns);
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
}

void	ft_init_map_elements(t_game *game)
{
	game->map.collectibles = 0;
	game->map.player.x = -1;
	game->map.player.y = -1;
	game->map.exit.x = 0;
	game->map.exit.y = -1;
}
