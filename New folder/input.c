#include "game.h"

void	hook_register(t_game *game)
{
	mlx_hook(game->win, 2, 1L<<0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L<<1, handle_keyrelease, game);
	mlx_hook(game->win, 17, 1L<<17, close_window, game);
}

int	handle_keypress(int key, t_game *game)
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

int	handle_keyrelease(int key, t_game *game)
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

int	close_window(t_game *game)
{
	ft_leave(game);
	exit(EXIT_SUCCESS);
	return (0);
}
