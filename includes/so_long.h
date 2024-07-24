/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:21:18 by jcohen            #+#    #+#             */
/*   Updated: 2024/07/24 21:22:53 by jcohen           ###   ########.fr       */
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
# define PLAYER_FRONT 0
# define PLAYER_BACK 1
# define PLAYER_LEFT 2
# define PLAYER_RIGHT 3
# define WALL '1'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define FLOOR '0'
# define TILE_SIZE 32
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
	t_image		player_images[4];
	int			player_direction;
}				t_game;

int				init_game(t_game *game);
int				load_images(t_game *game);
void			init_player(t_game *game);
void			*get_player_image(t_game *game);
void			ft_cleanup(t_game *game);
int				exit_game(t_game *game);

int				ft_is_valid_position(t_game *game, int x, int y);
int				ft_count_rows(char *filename);
int				load_map(t_game *game, char *file);
void			ft_free_map(t_game *game);
void			ft_print_map(t_game *game);
char			**ft_copy_map(t_game *game);
void			ft_restore_map(t_game *game, char **temp_map);
void			ft_init_map_elements(t_game *game);
int				ft_validate_map_dimensions(t_game *game);
void			ft_count_map_elements(t_game *game, int i, int j);
int				ft_perform_flood_fill(t_game *game);
int				ft_validate_map(t_game *game);
int				ft_flood_fill(t_game *game);
int				ft_is_map_playable(t_game *game);

void			*load_image(t_game *game, char *path);
void			draw_player(t_game *game, int x, int y);
void			render_map(t_game *game);
void			display_victory_message(t_game *game);

int				move_player(t_game *game, int dx, int dy);
int				key_press(int keycode, t_game *game);
void			update_player_position(t_game *game, int new_x, int new_y);
int				check_collision(t_game *game, int x, int y);
int				game_loop(t_game *game);

void			ft_destroy_images(t_game *game);
void			ft_cleanup(t_game *game);

#endif