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
	enemy->frame = rand() % 10;
	enemy->dead = 0;
	enemy->direction = rand() % 4;
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
			enemies->dead = 1;
		}
		i++;
	}
}

int	is_valid_move(t_game *game, int new_x, int new_y)
{
	return (new_x / PIXEL >= 0 && new_x / PIXEL < game->map.width &&
			new_y / PIXEL >= 0 && new_y / PIXEL < game->map.height);
}

void	move_monsters(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.n_enemies)
	{
		t_enemy *enemy = game->map.enemies[i];
		if (!enemy->dead)
		{
			int new_x = enemy->pos_x;
			int new_y = enemy->pos_y;
			ft_printf("eny_x: %d, eny_y: %d \n", enemy->pos_x, enemy->pos_y);

			if (enemy->direction == 0)
				new_y -= MOVE_SPEED;
			else if (enemy->direction == 1)
				new_y += MOVE_SPEED;
			else if (enemy->direction == 2)
				new_x -= MOVE_SPEED;
			else if (enemy->direction == 3)
				new_x += MOVE_SPEED;

			if (is_valid_move(game, new_x, new_y))
			{
				enemy->pos_x = new_x;
				enemy->pos_y = new_y;
			}
			else
				enemy->direction = rand() % 4;
			if (!enemy->dead)
				mlx_put_image_to_window(game->mlx, game->win, game->map.enemies_sprite[0], enemy->pos_x, enemy->pos_y);
		}
		i++;
	}
}

