#include "game.h"

void	flood_fill(t_flood_fill *flood, int x, int y)
{
	if (x < 0 || y < 0 || x >= flood->height || y >= flood->width || \
			flood->map[y][x] == '1' || flood->visited[y][x])
		return ;
	flood->visited[y][x] = 1;
	flood_fill(flood, x + 1, y);
	flood_fill(flood, x - 1, y);
	flood_fill(flood, x, y + 1);
	flood_fill(flood, x, y - 1);
}

static void	init_visited(t_flood_fill *f)
{
	int	i;
	int	j;

	i = 0;
	f->visited = ft_calloc(f->height + 1, sizeof(char *));
	while (i < f->height)
	{
		f->visited[i] = malloc(f->width * sizeof(int));
		j = 0;
		while (j < f->width)
		{
			f->visited[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	free_flood_mem(t_game *game, t_flood_fill *flood, int *flag)
{
	int	i;

	if (*flag == 1)
	{
		i = 0;
		while (i < flood->width)
			free(flood->visited[i++]);
		free(flood->visited);
		i = 0;
		while (i < flood->width)
			free(game->map.map[i++]);
		free(game->map.map);
		exit(1);
	}
	else if (*flag == 0)
	{
		i = 0;
		while (i < flood->height)
			free(flood->visited[i++]);
		free(flood->visited);
	}
}

static void	check_c_e_reachability(t_game *game, t_flood_fill *flood)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (i < flood->width)
	{
		j = 0;
		while (j < flood->height)
		{
			if ((game->map.map[i][j] == 'C' || game->map.map[i][j] == 'E') && \
					(!flood->visited[i][j]))
			{
				ft_printf("Error\n%c element is not reachable",
						game->map.map[i][j]);
				flag = 1;
				free_flood_mem(game, flood, &flag);
			}
			j++;
		}
		i++;
	}
	flag = 0;
	free_flood_mem(game, flood, &flag);
}

int	map_possible(t_game *game)
{
	t_flood_fill	flood;
	int					flag;

	flood.height = game->map.height;
	flood.width = game->map.width;
	flood.map = game->map.map;
	init_visited(&flood);
	flood_fill(&flood, game->map.player_start_x, game->map.player_start_y);
	if (flood.visited[game->map.player_start_x][game->map.player_start_y] == 0)
	{
		ft_printf("Error\nPlayer 'P' is either surrounded by walls or trapped\n");
		flag = 1;
		free_flood_mem(game, &flood, &flag);
		return(1);
	}
	check_c_e_reachability(game, &flood);
	return(0);
}
