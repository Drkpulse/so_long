// input.c
#include "game.h"

int handle_keypress(int key, t_game *game)
{
	if (key == ESC)
		close_window(game);
	if (key == KEY_W || key == ARROW_UP)
		game->player.move_up = 1;
	if (key == KEY_S || key == ARROW_DOWN)
		game->player.move_down = 1;
	if (key == KEY_A || key == ARROW_LEFT)
		game->player.move_left = 1;
	if (key == KEY_D || key == ARROW_RIGHT)
		game->player.move_right = 1;
	return 0;
}

int handle_keyrelease(int key, t_game *game)
{
	if (key == KEY_W || key == ARROW_UP)
		game->player.move_up = 0;
	if (key == KEY_S || key == ARROW_DOWN)
		game->player.move_down = 0;
	if (key == KEY_A || key == ARROW_LEFT)
		game->player.move_left = 0;
	if (key == KEY_D || key == ARROW_RIGHT)
		game->player.move_right = 0;
	return 0;
}

int close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	ft_leave(game);
	exit(EXIT_SUCCESS);
}
