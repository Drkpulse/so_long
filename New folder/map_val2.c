#include "game.h"

int check_char(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.map[i][j] != '0' && game->map.map[i][j] != 'P' &&
				game->map.map[i][j] != 'C' && game->map.map[i][j] != 'E' &&
				game->map.map[i][j] != '1' && game->map.map[i][j] != 'F')
			{
				ft_printf("Invalid character at [%d][%d]: %c\n", i, j, game->map.map[i][j]);
				return (1);
			}
			ft_printf("%c", game->map.map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	return (0);
}



int	surrounded(t_game *game)
{
	int	i;

	i = 0;
	printf("columns: %d, rows: %d\n", game->map.columns, game->map.rows);
	while (i < game->map.columns - 1)
	{
		if (game->map.map[0][i] != '1' && game->map.map[game->map.rows - 1][i])
			return (1);
		i++;
	}
	i = 0;
	while (i < game->map.rows - 1)
	{
		if (game->map.map[i][0] != '1' && game->map.map[i][game->map.columns - 1] != '1')
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
			{
				p_start++;
				game->map.start_x = i;
				game->map.start_y = j;
			}
			if (game->map.map[i][j] == 'E')
				exit++;
			if (game->map.map[i][j] == 'C')
				game->map.n_collectible++;
			if (game->map.map[i][j] == 'F')
				game->map.n_enemies++;
			j++;
		}
		i++;
	}
	if ( p_start != 1 || exit != 1 || game->map.n_collectible < 1)
		return (1);
	return (0);
}

void print_visited(t_flood_fill *f)
{
	for (int i = 0; i < f->rows; i++) {
		for (int j = 0; j < f->columns; j++) {
			printf("%d ", f->visited[i][j]);
		}
		printf("\n");
	}
}

void flood_fill(t_flood_fill *flood, int columns, int rows)
{
	if (flood->map == NULL || flood->visited == NULL)
	{
		printf("Error: flood->map or flood->visited is uninitialized!\n");
		return;
	}
	if (columns < 0 || rows < 0 || columns >= flood->columns || rows >= flood->rows)
	{
		printf("Out of bounds: x=%d, y=%d\n", columns, rows);
		return;
	}
	if (flood->map[rows][columns] == '1' || flood->visited[rows][columns])
		return;

	flood->visited[rows][columns] = 1;
	flood_fill(flood, columns + 1, rows);
	flood_fill(flood, columns - 1, rows);
	flood_fill(flood, columns, rows + 1);
	flood_fill(flood, columns, rows - 1);
}





void free_flood_mem(t_game *game, t_flood_fill *flood, int flag)
{
	int i;

	if (flag == 1)
	{
		i = 0;
		while (i < flood->rows)
			free(flood->visited[i++]);
		free(flood->visited);

		i = 0;
		while (i < game->map.rows)
			free(game->map.map[i++]);
		free(game->map.map);
		exit(1);
	}
	else if (flag == 0)
	{
		i = 0;
		while (i < flood->rows)
			free(flood->visited[i++]);
		free(flood->visited);
	}
}

static void init_visited(t_flood_fill *f)
{
	int i, j;

	f->visited = (int **)ft_calloc(f->rows, sizeof(int *));
	if (!f->visited) {
		printf("Error: Memory allocation failed for visited.\n");
		return;
	}
	i = 0;
	while (i < f->rows)
	{
		f->visited[i] = (int *)ft_calloc(f->columns, sizeof(int));
		if (!f->visited[i])
		{
			printf("Error: Memory allocation failed for visited[%d].\n", i);
			return;
		}
		j = 0;
		while (j < f->columns)
		{
			f->visited[i][j] = 0;
			j++;
		}
		i++;
	}
}


static void	check_reachability(t_game *game, t_flood_fill *flood)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (i < flood->rows)
	{
		j = 0;
		while (j < flood->columns)
		{
			if ((game->map.map[i][j] == 'C' || game->map.map[i][j] == 'E') && \
					(!flood->visited[i][j]))
			{
				ft_printf("Error\n%c element is not reachable\n",
						game->map.map[i][j]);
				flag = 1;
				free_flood_mem(game, flood, flag);
			}
			j++;
		}
		i++;
	}
	flag = 0;
	free_flood_mem(game, flood, flag);
}


int	map_possible(t_game *game)
{
	t_flood_fill	flood;
	int				flag;

	flood.rows = game->map.rows;
	flood.columns = game->map.columns;
	flood.map = game->map.map;
	init_visited(&flood);
	flood_fill(&flood, game->map.start_x, game->map.start_y);
	print_visited(&flood);
	if (flood.visited[game->map.start_y][game->map.start_x] == 0)
	{
		ft_printf("Error\nPlayer 'P' is either surrounded by walls or trapped\n");
		flag = 1;
		free_flood_mem(game, &flood, flag);
		return(1);
	}
	check_reachability(game, &flood);
	return(0);
}
