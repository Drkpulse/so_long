NAME		= so_long
NAME_BONUS	= so_long_bonus

SRC			=	main.c\
				game_init.c\
				map_val.c\
				map_val2.c\
				janitor.c\
				input.c\
				load_image.c\
				player.c\
				game_loop.c\
				debug.c\
				map_loop.c\
				collectibles.c\
				player_env.c\
				map_flood.c

SRC_BONUS   =  b_main.c\
				b_game_init.c\
				b_map_val.c\
				b_map_val2.c\
				b_janitor.c\
				b_input.c\
				b_load_image.c\
				b_player.c\
				b_game_loop.c\
				b_debug.c\
				b_map_loop.c\
				b_collectibles.c\
				b_player_env.c\
				b_enemies.c\
				b_map_flood.c

OBJ_DIR = obj
OBJ_DIR_BONUS = $(OBJ_DIR)/bonus
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR_BONUS)/, $(SRC_BONUS:.c=.o))

RM      = rm -rf
CC      = cc
CFLAGS  = -g -Wall -Wextra -Werror
MLXFLAGS = -L ./minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11 -g

MLX     = minilibx-linux/libmlx_Linux.a
LIBFT   = libft/bin/libft.a

GREEN   = \033[0;32m
RED     = \033[0;31m
YELLOW  = \033[0;33m
PURPLE  = \033[0;35m

all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(MLXFLAGS)
	@echo "$(GREEN)Compiled no bonus."

$(NAME_BONUS): $(OBJS_BONUS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(MLXFLAGS)
	@echo "$(GREEN)Compiled bonus."

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: bonus/%.c | $(OBJ_DIR_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)

$(MLX):
	make -C minilibx-linux

$(LIBFT):
	make -C libft

bonus: $(NAME_BONUS)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)
	$(RM) $(OBJS_BONUS)
	$(RM) -r $(OBJ_DIR_BONUS)
	make clean -C minilibx-linux
	@echo "$(RED)@\Cleaned all .o files\@"

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(OBJ_DIR)
	$(RM) $(NAME_BONUS)
	$(RM) -r $(OBJ_DIR_BONUS)
	@echo "$(RED)@\Cleaned all named files\@"

re: fclean all

-include $(OBJ_DIR)/*.d

.PHONY: all bonus clean fclean re