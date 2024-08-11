// collectibles.c
#include "game.h"

void	ft_collectible(t_game *game, long long now)
{
	int	i;
	t_collectible *collectible;
	i = 0;

	long long diff_millisecs;

	diff_millisecs = now - last_collectible_update;
	while (i < game->map.n_collectible)
	{
		collectible = game->map.collectibles[i];
		if (!collectible->collected)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->map.collectible_sprite[collectible->frame], collectible->pos_x * PIXEL, collectible->pos_y * PIXEL);
		}
		if (diff_millisecs > 240)
		{
			if (collectible->frame < 11)
				collectible->frame++;
			if (collectible->frame == 11)
				collectible->frame = 0;
		}
		i++;
	}
}

void	ft_collect(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->map.n_collectible)
	{
		t_collectible *collectible = game->map.collectibles[i];
		if (collectible->pos_x == x && collectible->pos_y == y && !collectible->collected)
		{
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

	collectible_index = 0;
	game->map.collectibles = malloc(game->map.n_collectible * sizeof(t_collectible *));
	if (!game->map.collectibles)
	{
		fprintf(stderr, "Failed to allocate memory for collectibles\n");
		exit(EXIT_FAILURE);
	}
	for (h = 0; h < game->map.height; h++)
	{
		for (w = 0; w < game->map.width; w++)
		{
			if (game->map.map[h][w] == 'C')
			{
				t_collectible *collectible = malloc(sizeof(t_collectible));
				if (!collectible)
				{
					fprintf(stderr, "Failed to allocate memory for a collectible\n");
					exit(EXIT_FAILURE);
				}

				collectible->pos_x = w;
				collectible->pos_y = h;
				collectible->frame = rand() % 10;
				collectible->collected = 0;

				game->map.collectibles[collectible_index++] = collectible;
			}
		}
	}

}
