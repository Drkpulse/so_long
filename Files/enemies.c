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

void	count_enemies(t_game *game)
{
	int	w;
	int	h;

	game->map.n_enemies = 0;
	while (h < game->map.height)
	{
		while (w < game->map.width)
		{
			if (game->map.map[h][w] == 'F')
				game->map.n_enemies++;
			w++;
		}
		h++;
	}
}

void	init_enemies(t_game *game)
{
	ft_printf("N of Enemies: %d\n", game->map.n_enemies);
	game->map.enemies = malloc(game->map.n_enemies * sizeof(t_enemy *));
	if (!game->map.enemies)
	{
		fprintf(stderr, "Failed to allocate memory for collectibles\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_check_monsters(t_game *game)
{
	int	enemy_index;
	int	w;
	int	h;

	h = 0;
	enemy_index = 0;
	init_enemies(game);
	while (h < game->map.height)
	{
		w = 0;
		while (w < game->map.width)
		{
			if (game->map.map[h][w] == 'F')
			{
				t_enemy *enemy = malloc(sizeof(t_enemy));
				if (!enemy)
				{
					fprintf(stderr, "Failed to allocate memory for a enemies\n");
					exit(EXIT_FAILURE);
				}
				default_enemy(enemy, w, h);
				game->map.enemies[enemy_index++] = enemy;
			}
			w++;
		}
		h++;
	}
}
void	default_enemy(t_enemy *enemy, int w, int h)
{
	enemy->pos_x = w;
	enemy->pos_y = h;
	enemy->frame = rand() % 8;
}


void	enemy_atk(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->map.n_enemies)
	{
		t_enemy *enemies = game->map.enemies[i];
		if (enemies->pos_x == x && enemies->pos_y == y)
			game->player.health--;
		i++;
	}
}

void	update_monsters(t_game *game, long long now)
{
	int					i;
	static long long	last_fire_update = 0;
	long long			diff_millisecs;

	diff_millisecs = now - last_fire_update;
	i = 0;
	while (i < game->map.n_enemies)
	{
		t_enemy *enemy = game->map.enemies[i];
				mlx_put_image_to_window(game->mlx, game->win, game->map.enemies_sprite[enemy->frame],
				enemy->pos_x * PIXEL, enemy->pos_y * PIXEL);
		if (diff_millisecs > 120)
		{
			if (enemy->frame < 7)
				enemy->frame++;
			else
				enemy->frame = 0;
		}
		i++;
	}
	if (diff_millisecs > 120)
		last_fire_update = now;
}
