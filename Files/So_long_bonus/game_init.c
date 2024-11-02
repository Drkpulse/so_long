/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:51:51 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/02 17:48:27 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_startup(t_game *game)
{
	game->movements = 0;
	game->last_millitimestamp = 0;
	game->map.n_collectible = 0;
	game->map.n_collected = 0;
	game->map.n_enemies = 0;
	game->map.rows = -1;
	game->map.columns = -1;
	game->map.n_portal = 0;
	game->map.lst_map = NULL;
	game->start = 1;
	game->mlx = mlx_init();
}

void	ft_init_window(t_game *game, char *path)
{
	game->win = mlx_new_window(game->mlx, game->map.columns * \
	PIXEL, game->map.rows * PIXEL, path);
}
