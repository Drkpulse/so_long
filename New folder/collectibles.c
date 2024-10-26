#include "game.h"

void	ft_collectible(t_game *game, long long now)
{
	int					i;
	t_collectible		*collectible;
	static long long	last_collectible_update = 0;
	long long			diff_millisecs;

	diff_millisecs = now - last_collectible_update;
	i = 0;
	while (i < game->map.n_collectible)
	{
		collectible = game->map.collectibles[i];
		if (!collectible->collected)
			mlx_put_image_to_window(game->mlx, game->win, game->map.collectible_sprite[collectible->frame], collectible->pos_x * PIXEL, collectible->pos_y * PIXEL);
		if (diff_millisecs > 120)
		{
			if (collectible->frame < 10)
				collectible->frame++;
			else
				collectible->frame = 0;
		}
		i++;
	}
	if (diff_millisecs > 120)
		last_collectible_update = now;
}

void	ft_collect(t_game *game, int rows, int columns)
{
	int	i;

	i = 0;
	while (i < game->map.n_collectible)
	{
		t_collectible *collectible = game->map.collectibles[i];
		if (collectible->pos_x == rows && collectible->pos_y == columns && !collectible->collected)
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
	game->map.collectibles = malloc(game->map.n_collectible * sizeof(t_collectible *));
	if (!game->map.collectibles)
	{
		fprintf(stderr, "Failed to allocate memory for collectibles\n");
		exit(EXIT_FAILURE);
	}
	while (h < game->map.rows)
	{
		w = 0;
		while (w < game->map.columns)
		{
			if (game->map.map[h][w] == 'C')
			{
				game->map.collectibles[collectible_index++] = ft_create_collectible(w, h);
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
	{
		fprintf(stderr, "Failed to allocate memory for a collectible\n");
		exit(EXIT_FAILURE);
	}
	collectible->pos_x = w;
	collectible->pos_y = h;
	collectible->frame = rand() % 10;
	collectible->collected = 0;

	return collectible;
}

void	free_collectibles(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.n_collectible)
	{
		t_collectible *collectible = game->map.collectibles[i];
		free(collectible);
		i++;
	}
	free(game->map.collectibles);
}
