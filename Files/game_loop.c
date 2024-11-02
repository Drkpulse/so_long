/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:51:53 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/02 18:05:25 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	game_loop(t_game *game)
{
	long long	now;
	long long	diff_millisecs;

	now = millitimestamp();
	diff_millisecs = now - game->last_millitimestamp;
	if (diff_millisecs > 15 && game->start != 0)
	{
		mlx_clear_window(game->mlx, game->win);
		fill_map(game->mlx, game->win, game->map);
		ft_collectible(game);
		ft_up_exit(game);
		ft_player(game);
		game->last_millitimestamp = now;
	}
	return (1);
}

void	ft_up_exit(t_game *game)
{
	int	i;
	int	j;
	int	end;

	i = 0;
	end = game->map.n_collectible - game->map.n_collected;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.map[i][j] == 'E' && end != 0)
				mlx_put_image_to_window(game->mlx, game->win, \
				game->map.portal_sprites[0], j * PIXEL, i * PIXEL);
			else if (game->map.map[i][j] == 'E' && end == 0)
				mlx_put_image_to_window(game->mlx, game->win, \
				game->map.portal_sprites[7] \
				, j * PIXEL, i * PIXEL);
			j++;
		}
		i++;
	}
}
