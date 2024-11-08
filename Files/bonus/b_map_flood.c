/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_map_flood.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:52:11 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/08 20:48:59 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_game.h"

void	flood_fill(t_flood_fill *flood, int columns, int rows)
{
	if (flood->map == NULL || flood->visited == NULL)
	{
		printf("Error: flood->map or flood->visited is uninitialized!\n");
		return ;
	}
	if (columns < 0 || rows < 0 || columns >= flood->columns \
	|| rows >= flood->rows)
	{
		printf("Out of bounds: x=%d, y=%d\n", columns, rows);
		return ;
	}
	if (flood->map[rows][columns] == '1' || flood->visited[rows][columns] ||
		flood->map[rows][columns] == 'F')
		return ;
	flood->visited[rows][columns] = 1;
	flood_fill(flood, columns + 1, rows);
	flood_fill(flood, columns - 1, rows);
	flood_fill(flood, columns, rows + 1);
	flood_fill(flood, columns, rows - 1);
}

void	free_flood_mem(t_game *game, t_flood_fill *flood, int flag)
{
	int	i;

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
		free_wrong_map(game, 0);
	}
	else if (flag == 0)
	{
		i = 0;
		while (i < flood->rows)
			free(flood->visited[i++]);
		free(flood->visited);
	}
}

static void	init_visited(t_flood_fill *f)
{
	int	i;
	int	j;

	f->visited = (int **)ft_calloc(f->rows, sizeof(int *));
	if (!f->visited)
		janitor(11);
	i = 0;
	while (i < f->rows)
	{
		f->visited[i] = (int *)ft_calloc(f->columns, sizeof(int));
		if (!f->visited[i])
			janitor(11);
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
	if (flood.visited[game->map.start_y][game->map.start_x] == 0)
	{
		ft_printf("Error\nPlayer 'P' is either surrounded \
		by walls or trapped\n");
		flag = 1;
		free_flood_mem(game, &flood, flag);
		return (1);
	}
	check_reachability(game, &flood);
	return (0);
}
