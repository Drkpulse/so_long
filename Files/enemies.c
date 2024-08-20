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
	game->map.enemies = malloc(game->map.n_enemies * sizeof(t_enemy *));
	if (!game->map.enemies)
	{
		fprintf(stderr, "Failed to allocate memory for collectibles\n");
		exit(EXIT_FAILURE);
	}
	init_enemy(game);
}

void	init_enemy(t_game *game)
{
	int	enemy_index;
	int	w;
	int	h;

	h = 0;
	w = 0;
	enemy_index = 0;
	while (h < game->map.height)
	{
		while (w < game->map.width)
		{
			if (game->map.map[h][w] == 'F')
			{
				t_enemy *enemy = malloc(sizeof(t_enemy));
				if (!enemy)
				{
					fprintf(stderr, "Failed to allocate memory for a collectible\n");
					exit(EXIT_FAILURE);
				}
				default_enemy(*enemy, w, h);
				game->map.enemies[enemy_index++] = enemy;
			}
			w++;
		}
		h++;
	}
}
void	default_enemy(t_enemy enemy, int w, int h)
{
	enemy.pos_x = w;
	enemy.pos_y = h;
	enemy.frame = rand() % 10;
	enemy.dead = 0;
	enemy.direction = rand() % 4;
}


void	enemy_atk(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->map.n_enemies)
	{
		t_enemy *enemies = game->map.enemies[i];
		if (enemies->pos_x == x && enemies->pos_y == y && !enemies->dead)
		{
			game->player.health--;
		}
		i++;
	}
}

void	move_monsters(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.n_enemies)
	{
		t_enemy *enemy = game->map.enemies[i];

		i++;
	}
}
