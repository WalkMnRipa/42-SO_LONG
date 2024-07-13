/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:08:44 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/13 19:39:11 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long <map_file.ber>\n");
		return (1);
	}
	if (!mlx_init())
	{
		ft_printf("Error: MLX initialization failed\n");
		return (1);
	}
	ft_printf("MLX initialized successfully\n");

	if (!load_map(&game, argv[1]))
	{
		ft_printf("Error: Failed to load map\n");
		return (1);
	}
	ft_printf("Map loaded successfully\n");
	ft_print_map(&game);
	if (!validate_map(&game))
	{
		ft_printf("Error: Invalid map\n");
		return (1);
	}

	ft_printf("Map validated successfully\n");
	if (!init_game(&game) || !load_images(&game) || !load_map(&game, argv[1])
		|| !validate_map(&game))
	{
		ft_printf("Error\nFailed to initialize game or invalid map\n");
		// Clean up resources here
		return (1);
	}
	render_map(&game);
	render_movements(&game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}