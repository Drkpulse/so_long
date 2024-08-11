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
