/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:51:53 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/02 17:48:34 by joseferr         ###   ########.fr       */
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
		fps(game);
		mlx_clear_window(game->mlx, game->win);
		fill_map(game->mlx, game->win, game->map);
		ft_collectible(game, now);
		ft_exit(game, now);
		update_monsters(game, now);
		sprite_player_up(game, now);
		ft_player(game);
		if (DEBUG)
		{
			show_steps(game);
			show_fps(game);
		}
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
				game->map.portal_sprites[game->map.n_portal] \
				, j * PIXEL, i * PIXEL);
			j++;
		}
		i++;
	}
}

void	ft_exit(t_game *game, long long now)
{
	static long long	last_portal_update = 0;
	long long			diff_millisecs;

	diff_millisecs = now - last_portal_update;
	if (diff_millisecs > 150)
	{
		if (game->map.n_portal < 7)
			game->map.n_portal++;
		else
			game->map.n_portal = 0;
		last_portal_update = now;
	}
	ft_up_exit(game);
}
