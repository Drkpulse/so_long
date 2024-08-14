#include "game.h"

int	ft_init_map(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		janitor(1);
	if (open_map(argv[1], game))
		janitor(2);
	if (map_to_lst(game))
		janitor(3);
	if (map_to_two_d(game))
		janitor(4);
	if (map_size(game))
		janitor(5);
	if (check_char(game))
		janitor(6);
	if (surrounded(game))
		janitor(7);
	if (count_char(game))
		janitor(8);
	return (0);
}

int	surrounded(t_game *game)
{
	int	i;

	i = 0;
	printf("width: %d, height: %d\n", game->map.width, game->map.height);
	while (i < game->map.width - 1)
	{
		if (game->map.map[0][i] != '1' && game->map.map[game->map.height - 1][i])
			return (1);
		i++;
	}
	i = 0;
	while (i < game->map.height - 1)
	{
		if (game->map.map[i][0] != '1' && game->map.map[i][game->map.width - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	count_char(t_game *game)
{
	int	exit;
	int	p_start;
	int	i;
	int	j;

	i = 0;
	p_start = 0;
	exit = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'P')
				p_start++;
			if (game->map.map[i][j] == 'E')
				exit++;
			if (game->map.map[i][j] == 'C')
				game->map.n_collectible++;
			j++;
		}
		i++;
	}
	if ( p_start != 1 || exit != 1 || game->map.n_collectible < 1)
		return (1);
	return (0);
}

void	fill_map(void *mlx_pointer, void *mlx_window, t_map mapa)
{
	int		i;
	int		j;
	int		pixel;
	int		tile_id;

	pixel = PIXEL;
	i = 0;
	while (mapa.map[i])
	{
		j = 0;
		while (mapa.map[i][j])
		{
			tile_id = (i * j) % 10;
			if (mapa.map[i][j] == '1')
				mlx_put_image_to_window(mlx_pointer, mlx_window, mapa.window_sprite[10], j * pixel, i * pixel);
			if (mapa.map[i][j] == '0' || mapa.map[i][j] == 'P' || mapa.map[i][j] == 'C' || mapa.map[i][j] == 'E')
				mlx_put_image_to_window(mlx_pointer, mlx_window, mapa.window_sprite[tile_id], j * pixel, i * pixel);
			j++;
		}
		i++;
	}
}


