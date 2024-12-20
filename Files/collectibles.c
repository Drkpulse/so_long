/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:51:34 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/08 20:49:09 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ft_collectible(t_game *game)
{
	int					i;
	t_collectible		*collectible;

	i = 0;
	while (i < game->map.n_collectible)
	{
		collectible = game->map.collectibles[i];
		if (!collectible->collected)
			mlx_put_image_to_window(game->mlx, game->win, \
			game->map.collectible_sprite[0], \
			collectible->pos_x * PIXEL, collectible->pos_y * PIXEL);
		i++;
	}
}

void	ft_collect(t_game *game, int rows, int columns)
{
	int				i;
	t_collectible	*collectible;

	i = 0;
	while (i < game->map.n_collectible)
	{
		collectible = game->map.collectibles[i];
		if (collectible->pos_x == rows && collectible->pos_y \
		== columns && !collectible->collected)
		{
			ft_printf("+1 Coin!\n");
			collectible->collected = 1;
			game->map.n_collected++;
		}
		i++;
	}
}

void	ft_init_collectible(t_game *game)
{
	int	collectible_index;
	int	w;
	int	h;

	h = 0;
	collectible_index = 0;
	game->map.collectibles = malloc(game->map.n_collectible * \
	sizeof(t_collectible *));
	if (!game->map.collectibles)
		janitor(10);
	while (h < game->map.rows)
	{
		w = 0;
		while (w < game->map.columns)
		{
			if (game->map.map[h][w] == 'C')
			{
				game->map.collectibles[collectible_index++] \
				= ft_create_collectible(w, h);
			}
			w++;
		}
		h++;
	}
}

t_collectible	*ft_create_collectible(int w, int h)
{
	t_collectible	*collectible;

	collectible = malloc(sizeof(t_collectible));
	if (!collectible)
		janitor(10);
	collectible->pos_x = w;
	collectible->pos_y = h;
	collectible->frame = rand() % 10;
	collectible->collected = 0;
	return (collectible);
}

void	free_collectibles(t_game *game)
{
	int				i;
	t_collectible	*collectible;

	i = 0;
	while (i < game->map.n_collectible)
	{
		collectible = game->map.collectibles[i];
		free(collectible);
		i++;
	}
	free(game->map.collectibles);
}
