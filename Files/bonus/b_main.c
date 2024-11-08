/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:25:43 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/08 20:48:58 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_game.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_startup(&game);
	ft_validate_map(argc, argv, &game);
	ft_init_window(&game, argv[1]);
	ft_init_sprite(&game);
	ft_init_player(&game);
	ft_init_collectible(&game);
	ft_check_monsters(&game);
	hook_register(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_map(game.map.map, game.map.rows);
	exit(EXIT_SUCCESS);
}
