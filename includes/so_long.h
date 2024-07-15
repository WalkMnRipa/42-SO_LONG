/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:21:18 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/13 22:57:54 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define WALL '1'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define FLOOR '0'
# define TILE_SIZE 48
# define EVENT_EXIT 17
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			columns;
	t_position	player;
	t_position	exit;
	int			collectibles;
}				t_map;

typedef struct s_player
{
	t_position	position;
	int			moves;
}				t_player;

typedef struct s_image
{
	void		*img;
	t_position	position;
}				t_image;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			window_width;
	int			window_height;
	int			movements;
	bool		victory;
	t_map		map;
	t_image		floor;
	t_image		wall;
	t_image		collectible;
	t_image		exit;
	t_image		player;
}				t_game;

int				init_game(t_game *game);
int				load_images(t_game *game);
int				load_map(t_game *game, char *file);
void			ft_print_map(t_game *game);
int				validate_map(t_game *game);
int				flood_fill(t_game *game, int x, int y, int *visited);
int				is_map_playable(t_game *game);

void			draw_tile(t_game *game, void *img, int x, int y);
void			render_map(t_game *game);
void			render_movements(t_game *game);
void			display_victory_message(t_game *game);

int				move_player(t_game *game, int dx, int dy);
int				key_press(int keycode, t_game *game);

void			free_map(t_map *map);
void			destroy_images(t_game *game);
void			cleanup(t_game *game);

#endif