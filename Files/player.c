// player.c
#include "game.h"

void	init_player_var(t_game *game)
{
	game->player.health = HEALTH;
	game->player.steps = 0;
	game->player.move_up = 0;
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.move_sprite_index = 0;
}

int	ft_init_player(t_game *game)
{
	int	w;
	int	h;

	h = 0;
	while (game->map.map[h])
	{
		w = 0;
		while (game->map.map[h][w])
		{
			if (game->map.map[h][w] == 'P')
			{
				game->player.pos_x = w * PIXEL;
				game->player.pos_y = h * PIXEL;
			}
			w++;
		}
		h++;
	}
	init_player_var(game);
	return (0);
}

void	update_player_position(t_game *game, int next_x, int next_y)
{
	if (game->player.pos_x != next_x || game->player.pos_y != next_y)
	{
		game->player.steps += 1;
		ft_printf("Steps: %d\n", game->player.steps);
	}
	game->player.pos_x = next_x;
	game->player.pos_y = next_y;
}

void	check_surroundings(t_game *game, int map_x1, int map_y1, int map_x2, int map_y2)
{
	check_collectible(game, map_x1, map_y1);
	check_collectible(game, map_x2, map_y1);
	check_collectible(game, map_x1, map_y2);
	check_collectible(game, map_x2, map_y2);
	check_exit(game, map_x1, map_y1);
	check_exit(game, map_x2, map_y1);
	check_exit(game, map_x1, map_y2);
	check_exit(game, map_x2, map_y2);
	check_enemy(game, map_x1, map_y1);
	check_enemy(game, map_x2, map_y1);
	check_enemy(game, map_x1, map_y2);
	check_enemy(game, map_x2, map_y2);
}

int	is_collision(t_game *game, int map_x1, int map_y1, int map_x2, int map_y2)
{
	return (game->map.map[map_y1][map_x1] == '1' || game->map.map[map_y1][map_x2] == '1' ||
			game->map.map[map_y2][map_x1] == '1' || game->map.map[map_y2][map_x2] == '1');
}

void	calculate_next_position(t_game *game, int *next_x, int *next_y)
{
	*next_x = game->player.pos_x;
	*next_y = game->player.pos_y;
	if (game->player.move_up)
		*next_y -= MOVE_SPEED;
	if (game->player.move_down)
		*next_y += MOVE_SPEED;
	if (game->player.move_left)
		*next_x -= MOVE_SPEED;
	if (game->player.move_right)
		*next_x += MOVE_SPEED;
}

void	ft_player(t_game *game)
{
	int	next_x;
	int	next_y;
	int	map_x1, map_y1, map_x2, map_y2;

	calculate_next_position(game, &next_x, &next_y);

	map_x1 = next_x / PIXEL;
	map_y1 = next_y / PIXEL;
	map_x2 = (next_x + PIXEL - 1) / PIXEL;
	map_y2 = (next_y + PIXEL - 1) / PIXEL;

	if (!is_collision(game, map_x1, map_y1, map_x2, map_y2))
	{
		check_surroundings(game, map_x1, map_y1, map_x2, map_y2);
		update_player_position(game, next_x, next_y);
	}

	mlx_put_image_to_window(game->mlx, game->win, game->player.sprites[game->player.move_sprite_index], game->player.pos_x, game->player.pos_y);
}


void	sprite_player_up(t_game *game, long long now)
{
	static long long last_player_update = 0;
	long long diff_millisecs;

	diff_millisecs = now - last_player_update;

	// Update the sprite only if 120 milliseconds have passed
	if (diff_millisecs > 120)
	{
		if (game->player.move_up || game->player.move_down || game->player.move_left || game->player.move_right)
			if (game->player.move_sprite_index < 10)
				game->player.move_sprite_index++;
			else
				game->player.move_sprite_index = 3;
		else
			if (game->player.move_sprite_index < 2)
				game->player.move_sprite_index++;
			else
				game->player.move_sprite_index = 0;
		last_player_update = now;
	}
}

void	check_collectible(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'C') {
		ft_collect(game, map_x, map_y);
		game->map.map[map_y][map_x] = '0';
	}
}

void	check_exit(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'E')
	{
		if ((game->map.n_collectible - game->map.n_collected) == 0)
			exit(EXIT_SUCCESS);
	}
}

void	check_enemy(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'F')
	{
			exit(EXIT_SUCCESS);
	}
}
