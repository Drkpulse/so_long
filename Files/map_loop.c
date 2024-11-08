/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:52:13 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/08 20:49:20 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	fill_map(void *mlx_pointer, void *mlx_window, t_map mapa)
{
	int		i;
	int		j;
	int		pixel;
	int		tile_id;

	pixel = PIXEL;
	i = 0;
	while (mapa.map[i])
	{
		j = 0;
		while (mapa.map[i][j])
		{
			tile_id = (i * j) % 10;
			if (mapa.map[i][j] == '1')
				mlx_put_image_to_window(mlx_pointer, mlx_window, \
				mapa.window_sprite[10], j * pixel, i * pixel);
			if (mapa.map[i][j] == '0' || mapa.map[i][j] == 'P' || \
			mapa.map[i][j] == 'C' || mapa.map[i][j] == 'E')
				mlx_put_image_to_window(mlx_pointer, mlx_window, \
				mapa.window_sprite[tile_id], j * pixel, i * pixel);
			j++;
		}
		i++;
	}
}

void	ft_leave(t_game *game)
{
	game->start = 0;
	free_map(game->map.map, game->map.rows);
	free_sprites(game, game->player.sprites, 1);
	free_sprites(game, game->map.collectible_sprite, 1);
	free_sprites(game, game->map.window_sprite, 11);
	free_sprites(game, game->map.portal_sprites, 9);
	free_collectibles(game);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
