NAME		= so_long

SRC		= main.c game_init.c map_val.c map_val2.c janitor.c input.c load_image.c player.c game_loop.c debug.c map_loop.c collectibles.c player_env.c enemies.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

RM		= rm -rf
CC		= cc
CFLAGS		= -g -Wall -Wextra -Werror
MLXFLAGS	= -L ./minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11 -g

MLX		= minilibx-linux/libmlx_Linux.a

LIBFT	= libft/bin/libft.a

GREEN 		= \033[0;32m
RED			= \033[0;31m
YELLOW		= \033[0;33m
PURPLE		= \033[0;35m

all:  $(MLX) $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(MLXFLAGS)
	@echo "$(GREEN)Compiled no bonus."

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	make -C minilibx-linux

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)
	make clean -C minilibx-linux
	@echo "$(RED)@\Cleaned all .o files\@"

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(OBJ_DIR)
	@echo "$(RED)@\Cleaned all named files\@"

re: fclean all

-include $(OBJ_DIR)/*.d

.PHONY:	all clean fclean re

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
