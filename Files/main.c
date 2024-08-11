// main.c
#include "game.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_ready_game(&game);
	ft_init_map(argc, argv, &game);
	ft_init_window(&game, argv[1]);
	ft_init_sprite(&game);
	ft_init_player(&game);
	ft_init_collectible(&game);
	//ft_check_monsters(&game);
	hook_register(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	exit(EXIT_SUCCESS);
}
