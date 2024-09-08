# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 23:47:56 by jcohen            #+#    #+#              #
#    Updated: 2024/09/08 17:58:30 by jcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Couleurs
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

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
       $(GAME_DIR)/enemy_movement.c $(GAME_DIR)/enemy_init.c

OBJS_DIR = objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): compile_libft compile_mlx compile_project link_project
	@echo "$(GREEN)Build complete!$(RESET)"

compile_libft:
	@echo -n "$(YELLOW)Compiling libft... $(RESET)"
	@make -C libft > /dev/null 2>&1
	@for i in {1..10}; do echo -n "$(BLUE)█$(RESET)"; sleep 0.1; done
	@echo "$(GREEN) Done!$(RESET)"

compile_mlx:
	@echo -n "$(YELLOW)Compiling MLX... $(RESET)"
	@make -C minilibx-linux > /dev/null 2>&1
	@for i in {1..10}; do echo -n "$(BLUE)█$(RESET)"; sleep 0.1; done
	@echo "$(GREEN) Done!$(RESET)"

compile_project: $(OBJS)
	@echo "$(GREEN)Project files compiled!$(RESET)"

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo -n "$(YELLOW)Compiling $<... $(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I./includes -I./libft -I./minilibx-linux
	@echo "$(GREEN)Done!$(RESET)"

link_project:
	@echo -n "$(YELLOW)Linking project... $(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./minilibx-linux $(MLXFLAGS) -o $(NAME) > /dev/null 2>&1
	@for i in {1..10}; do echo -n "$(BLUE)█$(RESET)"; sleep 0.1; done
	@echo "$(GREEN) Done!$(RESET)"

clean:
	@echo -n "$(YELLOW)Cleaning up... $(RESET)"
	@make -C libft clean > /dev/null 2>&1
	@make -C minilibx-linux clean > /dev/null 2>&1
	@rm -rf $(OBJS_DIR)
	@for i in {1..10}; do echo -n "$(BLUE)█$(RESET)"; sleep 0.05; done
	@echo "$(GREEN) Done!$(RESET)"

fclean: clean
	@echo -n "$(YELLOW)Full cleanup... $(RESET)"
	@make -C libft fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@for i in {1..10}; do echo -n "$(BLUE)█$(RESET)"; sleep 0.05; done
	@echo "$(GREEN) Done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re compile_libft compile_mlx compile_project link_project
