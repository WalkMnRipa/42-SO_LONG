/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:21:18 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/12 17:37:26 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define SPRITE_SIZE 48

typedef struct s_map
{
	char	map[WINDOW_HEIGHT][WINDOW_WIDTH];
	int		height;
	int		width;
	int		start_x;
	int		start_y;
	int		exit_x;
	int		exit_y;
	int		collectibles;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		x;
	int		y;
	int		moves;
	t_map	map;
}			t_game;

typedef struct s_player
{
	int		x;
	int		y;
}			t_player;
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_texture;

// MAP PART 
int			is_valid_char(char c);
int			check_args(int argc, char **argv);
void		print_error(const char *message);
int			open_file(const char *filename, FILE **file);
int			check_line_length(char *line, t_map *map);
int			ft_check_map_border(t_map *map);
int			ft_check_path(t_map *map, int x, int y);

// GRAPHIC PART

#endif
