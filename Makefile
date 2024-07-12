# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 23:47:56 by jcohen            #+#    #+#              #
#    Updated: 2024/07/12 17:28:55 by jcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

# Compilateur et flags
CC := cc
CFLAGS := -Wall -Wextra -Werror

# Chemins
SRC_DIR = game
GRAPH_DIR = graphique
INC_DIR = includes
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

# Sources
SRC = $(wildcard $(SRC_DIR)/*.c)
GRAPH = $(wildcard $(GRAPH_DIR)/*.c)
OBJ = $(SRC:.c=.o) $(GRAPH:.c=.o)

# Bibliothèques
LIBFT := $(LIBFT_DIR)/libft.a
MLX := $(MLX_DIR)/libmlx.a

# Flags pour les bibliothèques
LIBS := -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Inclusions
INC := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Règle par défaut
all: $(NAME)

# Compilation du programme
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

# Compilation des objets
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compilation de la MiniLibX
$(MLX):
	make -C $(MLX_DIR)

# Nettoyage
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

# Nettoyage complet
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Recompilation
re: fclean all

# Règles spéciales
.PHONY: all clean fclean re