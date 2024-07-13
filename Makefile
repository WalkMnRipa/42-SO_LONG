# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 23:47:56 by jcohen            #+#    #+#              #
#    Updated: 2024/07/13 18:51:55 by jcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC_DIR = src

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/map.c $(SRC_DIR)/init.c \
	   $(SRC_DIR)/game_logic.c $(SRC_DIR)/render.c \
	   $(SRC_DIR)/clean.c 

OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./minilibx-linux $(MLXFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c
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