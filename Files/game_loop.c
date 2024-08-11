// game_loop.c
#include "game.h"

int	game_loop(t_game *game)
{
	long long now;
	long long diff_millisecs;

	now = millitimestamp();
	diff_millisecs = now - game->last_millitimestamp;
	if (diff_millisecs > 30)
	{
		fps(game);
		mlx_clear_window(game->mlx, game->win);
		fill_map(game->mlx, game->win, game->map);
		ft_collectible(game, now);
		ft_exit(game);
		//move_monsters(game);
		sprite_player_up(game);
		ft_player(game);
		if (DEBUG)
			show_fps(game);
		game->last_millitimestamp = now;
	}
	return (1);
}

void	ft_exit(t_game *game)
{
	int	i;
	int	j;
	int	end;

	i = 0;
	end = game->map.n_collectible - game->map.n_collected;
	if (game->map.n_portal < 8)
		game->map.n_portal++;
	else
		game->map.n_portal = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
				if (game->map.map[i][j] == 'E' && end != 0)
					mlx_put_image_to_window(game->mlx, game->win, game->map.portal_sprites[6],j * PIXEL, i * PIXEL);
				else if (game->map.map[i][j] == 'E' && end == 0)
					mlx_put_image_to_window(game->mlx, game->win, game->map.portal_sprites[game->map.n_portal],j * PIXEL, i * PIXEL);
			j++;
		}
		i++;
	}
}
