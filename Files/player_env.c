/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:52:22 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/08 20:49:24 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_collision(t_game *game, t_hitbox hitbox)
{
	return (game->map.map[hitbox.map_y1][hitbox.map_x1] == '1' ||
			game->map.map[hitbox.map_y1][hitbox.map_x2] == '1' ||
			game->map.map[hitbox.map_y2][hitbox.map_x1] == '1' ||
			game->map.map[hitbox.map_y2][hitbox.map_x2] == '1');
}

void	check_surroundings(t_game *game, t_hitbox hitbox)
{
	check_collectible(game, hitbox.map_x1, hitbox.map_y1);
	check_collectible(game, hitbox.map_x2, hitbox.map_y1);
	check_collectible(game, hitbox.map_x1, hitbox.map_y2);
	check_collectible(game, hitbox.map_x2, hitbox.map_y2);
	check_exit(game, hitbox.map_x1, hitbox.map_y1);
	check_exit(game, hitbox.map_x2, hitbox.map_y1);
	check_exit(game, hitbox.map_x1, hitbox.map_y2);
	check_exit(game, hitbox.map_x2, hitbox.map_y2);
	check_enemy(game, hitbox.map_x1, hitbox.map_y1);
	check_enemy(game, hitbox.map_x2, hitbox.map_y1);
	check_enemy(game, hitbox.map_x1, hitbox.map_y2);
	check_enemy(game, hitbox.map_x2, hitbox.map_y2);
}

void	check_collectible(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'C')
	{
		ft_collect(game, map_x, map_y);
		game->map.map[map_y][map_x] = '0';
	}
}

void	check_exit(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'E' && game->start != 0)
	{
		if ((game->map.n_collectible - game->map.n_collected) == 0)
		{
			ft_printf("Passaste o meu so_long! Boa!\n");
			close_window(game);
		}
	}
}

void	check_enemy(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'F')
	{
		ft_printf("You Burned\n");
		ft_printf("Collected %d of %d\n", game->map.n_collected, \
		game->map.n_collectible);
		close_window (game);
	}
}
