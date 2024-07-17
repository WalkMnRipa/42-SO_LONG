/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:44 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/17 21:06:37 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	init_and_load(t_game *game, char *map_file)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	if (!load_map(game, map_file))
		return (0);
	if (!ft_is_map_playable(game))
		return (0);
	if (!init_game(game))
		return (0);
	if (!load_images(game))
		return (0);
	ft_printf("Game initialized successfully.\n");
	return (1);
}

static void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->win, key_press, game);
	mlx_hook(game->win, 17, 1L << 17, exit_game, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long <map_file.ber>\n");
		return (0);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (!init_and_load(&game, argv[1]))
	{
		ft_printf("Error: Game initialization failed\n");
		ft_cleanup(&game);
		return (1);
	}
	render_map(&game);
	render_movements(&game);
	setup_hooks(&game);
	ft_printf("Starting game loop...\n");
	mlx_loop(game.mlx);
	ft_cleanup(&game);
	return (0);
}
