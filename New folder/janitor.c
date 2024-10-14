#include "game.h"

void	janitor(int error)
{
	const char *messages[] = {
		"Invalid Arguments",
		"Invalid Map File",
		"map_to_lst",
		"map_to_two_d",
		"map_size",
		"check_char",
		"surrounded",
		"count_char",
	};

	if (error >= 1 && error <= 8)
		printf("%s\n", messages[error - 1]);
	else
		printf("Unknown error\n");

	exit(EXIT_FAILURE);
}

void free_list(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void free_map(char **map, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free(map[i]);
	}
	free(map);
}

void	ft_leave(t_game *game)
{
	game->start = 0;
	free_map(game->map.map, game->map.rows);
	free_sprites(game, game->player.sprites, 11);
	free_sprites(game, game->map.collectible_sprite, 11);
	free_sprites(game, game->map.window_sprite, 11);
	free_sprites(game, game->map.portal_sprites, 9);
	free_sprites(game, game->map.enemies_sprite, 8);
	free_collectibles(game);
	free_enemies(game);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	free_sprites(t_game *game, void **sprites, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (sprites[i])
		{
			mlx_destroy_image(game->mlx, sprites[i]);
			sprites[i] = NULL;
		}
		i++;
	}
}

