// player.c
#include "game.h"

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
	game->player.health = HEALTH;
	game->player.steps = 0;
	game->player.move_up = 0;
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.move_sprite_index = 0;
	return (0);
}

void	ft_player(t_game *game)
{
	int			next_x;
	int			next_y;

	next_x = game->player.pos_x;
	next_y = game->player.pos_y;
	// Calculate next position based on input
	if (game->player.move_up)
		next_y -= MOVE_SPEED;
	if (game->player.move_down)
		next_y += MOVE_SPEED;
	if (game->player.move_left)
		next_x -= MOVE_SPEED;
	if (game->player.move_right)
		next_x += MOVE_SPEED;

	// Calculate map indices for the next position
	int map_x1 = next_x / PIXEL;
	int map_y1 = next_y / PIXEL;
	int map_x2 = (next_x + PIXEL - 1) / PIXEL;
	int map_y2 = (next_y + PIXEL - 1) / PIXEL;

	// Check for collision with walls
	if (game->map.map[map_y1][map_x1] != '1' && game->map.map[map_y1][map_x2] != '1' &&
		game->map.map[map_y2][map_x1] != '1' && game->map.map[map_y2][map_x2] != '1')
	{
		// Check for collectibles
		check_collectible(game, map_x1, map_y1);
		check_collectible(game, map_x2, map_y1);
		check_collectible(game, map_x1, map_y2);
		check_collectible(game, map_x2, map_y2);

		// Check for exit
		check_exit(game, map_x1, map_y1);
		check_exit(game, map_x2, map_y1);
		check_exit(game, map_x1, map_y2);
		check_exit(game, map_x2, map_y2);

		if(game->player.pos_x != next_x || game->player.pos_y != next_y)
		{
			game->player.steps += 1;
			ft_printf("Steps: %d\n", game->player.steps);
		}
		// Update player position
		game->player.pos_x = next_x;
		game->player.pos_y = next_y;
	}
	// Render the player
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
		{
			if (game->player.move_sprite_index < 10)
				game->player.move_sprite_index++;
			else
				game->player.move_sprite_index = 3;
		}
		else
		{
			if (game->player.move_sprite_index < 2)
				game->player.move_sprite_index++;
			else
				game->player.move_sprite_index = 0;
		}
		// Update the last player update time
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


