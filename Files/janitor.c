#include "game.h"

void	ft_free_sprites(t_game *game, int sprite_type)
{
	int	i;
	int	sprite_count = 0;
	void **sprites = NULL;

	if (sprite_type == 1)
	{
		sprites = (void **)game->map.window_sprite;
		sprite_count = 11;
	}
	else if (sprite_type == 2)
	{
		sprites = (void **)game->map.portal_sprites;
		sprite_count = 9;
	}
	else if (sprite_type == 3)
	{
		sprites = (void **)game->player.sprites;
		sprite_count = 23;
	}
	else if (sprite_type == 4)
	{
		sprites = (void **)game->map.collectible_sprite;
		sprite_count = 11;
	}
	else if (sprite_type == 5)
	{
		sprites = (void **)game->map.enemies_sprite;
		sprite_count = 8;
	}
	if (sprites)
	{
		for (i = 0; i < sprite_count; i++)
		{
			if (sprites[i])
			{
				mlx_destroy_image(game->mlx, sprites[i]);
				sprites[i] = NULL;
			}
		}
	}
}

void	ft_free_collectibles(t_collectible **collectibles, int count)
{
	if (!collectibles)
		return;
	for (int i = 0; i < count; i++)
	{
		if (collectibles[i])
		{
			free(collectibles[i]);
			collectibles[i] = NULL;
		}
	}
	free(collectibles);
}

void	ft_free_enemies(t_enemy **enemies, int count)
{
	if (!enemies)
		return;
	for (int i = 0; i < count; i++)
	{
		if (enemies[i])
		{
			free(enemies[i]);
			enemies[i] = NULL;
		}
	}
	free(enemies);
}

void	ft_free_map(t_map *map)
{
	if (map->lst_map)
		ft_lstclear(&(map->lst_map), free);

	if (map->map)
	{
		for (int i = 0; map->map[i]; i++)
			free(map->map[i]);
		free(map->map);
	}

	ft_free_collectibles(map->collectibles, map->n_collectible);
	ft_free_enemies(map->enemies, map->n_enemies);

	ft_free_sprites((void **)map->collectible_sprite, 11);
	ft_free_sprites((void **)map->enemies_sprite, 8);
	ft_free_sprites((void **)map->window_sprite, 11);
	ft_free_sprites((void **)map->portal_sprites, 9);
}

void	ft_leave(t_game *game)
{
	if (!game)
		return;

	ft_free_sprites(game, 1);
	ft_free_sprites(game, 2);
	ft_free_sprites(game, 3);
	ft_free_sprites(game, 4);
	ft_free_sprites(game, 5);

	ft_free_map(&game->map);

	if (game->win)
		mlx_destroy_window(game->mlx, game->win);

	if (game->mlx)
		mlx_destroy_display(game->mlx);

	free(game);
}
