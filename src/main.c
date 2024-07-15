/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:44 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/13 22:57:21 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	init_and_load(t_game *game, char *map_file)
{
	if (!mlx_init())
	{
		ft_printf("Error: MLX initialization failed\n");
		return (0);
	}
	ft_printf("MLX initialized successfully\n");
	if (!load_map(game, map_file))
	{
		ft_printf("Error: Failed to load map\n");
		return (0);
	}
	ft_printf("Map loaded successfully\n");
	ft_print_map(game);
	if (!validate_map(game))
	{
		ft_printf("Error: Invalid map\n");
		cleanup(game);
		return (0);
	}
	if (!is_map_playable(game))
	{
		ft_printf("Error: Map is not playable\n");
		cleanup(game);
		return (0);
	}
	ft_printf("Map validated successfully\n");
	if (!init_game(game) || !load_images(game))
	{
		ft_printf("Error: Failed to initialize game or load images\n");
		cleanup(game);
		return (0);
	}
	ft_printf("Game initialized successfully\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long <map_file.ber>\n");
		return (1);
	}
	if (!init_and_load(&game, argv[1]))
		return (1);
	render_map(&game);
	render_movements(&game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_hook(game.win, 17, 1L << 17, (int (*)())exit, 0);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
