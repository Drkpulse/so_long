#include "game.h"

int	ft_init_player(t_game *game)
{
	game->player.health = HEALTH;
	game->player.steps = 0;
	game->player.move_up = 0;
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.move_sprite_index = 0;
	game->player.pos_x = game->map.start_x * PIXEL;
	game->player.pos_y = game->map.start_y * PIXEL;
	return (0);
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
