# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRCS = src/map/map_copy.c src/map/map_flood_fill.c src/map/map_loader.c src/map/map_utils.c src/map/map_validator.c src/core/cleanup.c src/core/init.c src/core/main.c src/game/enemy_init.c src/game/enemy_movement.c src/game/game_logic.c src/game/player_movement.c src/graphics/render.c src/graphics/render_enemy.c

OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo -n "$(YELLOW)Linking project... $(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./minilibx-linux $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo -n "$(YELLOW)Compiling $<... $(RESET)"
	@$(CC) $(CFLAGS) -I./includes -I./libft -I./minilibx-linux -c $< -o $@
	@echo "$(GREEN)Done!$(RESET)"

$(MLX):
	@echo "$(YELLOW)Compiling MLX...$(RESET)"
	@$(MAKE) -C minilibx-linux > /dev/null 2>&1 || (echo "$(YELLOW)MLX compilation failed. Check minilibx-linux for errors.$(RESET)" && exit 1)
	@echo "$(GREEN)MLX compilation successful!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C libft > /dev/null 2>&1 || (echo "$(YELLOW)libft compilation failed. Check libft for errors.$(RESET)" && exit 1)
	@echo "$(GREEN)libft compilation successful!$(RESET)"

clean:
	@echo -n "$(YELLOW)Cleaning up... $(RESET)"
	@$(MAKE) -C libft clean > /dev/null 2>&1
	@$(MAKE) -C minilibx-linux clean > /dev/null 2>&1
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo -n "$(YELLOW)Full cleanup... $(RESET)"
	@$(MAKE) -C libft fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
