# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 23:47:56 by jcohen            #+#    #+#              #
#    Updated: 2024/07/26 22:32:10 by jcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
GAME_DIR = $(SRC_DIR)/game
MAP_DIR = $(SRC_DIR)/map
GRAPHICS_DIR = $(SRC_DIR)/graphics

SRCS = $(CORE_DIR)/main.c $(CORE_DIR)/init.c $(CORE_DIR)/cleanup.c \
       $(GAME_DIR)/game_logic.c $(GAME_DIR)/player_movement.c \
       $(MAP_DIR)/map_loader.c $(MAP_DIR)/map_validator.c $(MAP_DIR)/map_utils.c \
	   $(MAP_DIR)/map_flood_fill.c $(MAP_DIR)/map_copy.c \
       $(GRAPHICS_DIR)/render.c $(GRAPHICS_DIR)/render_enemy.c \
	   $(GAME_DIR)/enemy_movement.c $(GAME_DIR)/enemy_init.c \

OBJS_DIR = objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./minilibx-linux $(MLXFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./includes -I./libft -I./minilibx-linux -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

clean:
	make -C libft clean
	make -C minilibx-linux clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re