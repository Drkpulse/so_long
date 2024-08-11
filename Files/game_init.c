// game_init.c
#include "game.h"

void ft_ready_game(t_game *game)
{
	game->movements = 0;
	game->game_started = 0;
	game->last_millitimestamp = 0;
	game->map.n_collectible = 0;
	game->map.n_collected = 0;
	game->map.height = -1;
	game->map.width = -1;
	game->map.n_portal = 0;
	game->map.lst_map = NULL;
	game->mlx = mlx_init();
}

void	ft_init_window(t_game *game, char *path)
{
	game->win = mlx_new_window(game->mlx, game->map.width * PIXEL, game->map.height * PIXEL, path);
}

void hook_register(t_game *game)
{
	mlx_hook(game->win, 2, 1L<<0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L<<1, handle_keyrelease, game);
	mlx_hook(game->win, 17, 1L<<17, close_window, game);
}

void janitor(int error)
{
	const char *messages[] = {
		"Invalid Arguments",
		"Invalid Map File",
		"map_to_lst",
		"map_to_two_d",
		"map_size",
		"check_char",
		"surrounded",
		"count_char",
	};

	if (error >= 1 && error <= 8)
		printf("%s\n", messages[error - 1]);
	else
		printf("Unknown error\n");

	exit(EXIT_FAILURE);
}
