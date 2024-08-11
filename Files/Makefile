MAKEFLAGS 	+= -s

SRC		= main.c game_init.c map_utils.c player.c \
		collectibles.c load_image.c input.c game_loop.c \
		debug.c map_init.c

OBJS		= $(SRC:.c=.o)

RM		= rm -rf
CC		= cc
CFLAGS		= -g -Wall -Wextra -Werror
MLXFLAGS	= -L ./minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11 -g

MLX		= minilibx-linux/libmlx_Linux.a

LIBFT	= libft/bin/libft.a

NAME		= so_long

GREEN 		= \033[0;32m
RED			= \033[0;31m
YELLOW		= \033[0;33m
PURPLE		= \033[0;35m

all:  $(MLX) $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(MLXFLAGS)
	@echo "$(GREEN)Compiled no bonus."

$(MLX):
	make -C minilibx-linux

clean:
	$(RM) $(OBJS)
	make clean -C minilibx-linux
	@echo "$(RED)@\Cleaned all .o files\@"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)@\Cleaned all named files\@"

re: fclean all

.PHONY:	all clean fclean re
