/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoeferr < joseferr@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:29:23 by jsoeferr          #+#    #+#             */
/*   Updated: 2024/08/11 13:29:23 by jsoeferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "game.h"
/*
int create_monster(t_game *game, int w, int h)
{
	game->maps.enemies[game->map.n_enemy].pos_x = h * PIXEL;
	game->enemies[game->map.n_enemy].pos_y = w * PIXEL;
	game->enemies[game->map.n_enemy].direction = rand() % 4;
	game->enemies[game->map.n_enemy].sprite_index = 0;
	game->map.n_enemy++;
	return (0);
}
*/
int ft_check_monsters(t_game *game)
{
	game->map.n_enemy = 0;
	return (1);
}
