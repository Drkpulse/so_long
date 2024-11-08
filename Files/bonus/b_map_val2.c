/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:52:20 by joseferr          #+#    #+#             */
/*   Updated: 2024/10/29 20:21:37 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_game.h"

int	check_char(t_game *game)
{
	int	i;
	int	j;

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
				ft_printf("Invalid character at [%d][%d]: %c\n"\
					, i, j, game->map.map[i][j]);
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
		if (game->map.map[i][0] != '1' && game->map.map[i] \
			[game->map.columns - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	count_char(t_game *game, char c)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == c)
			{
				count++;
				if (c == 'P')
				{
					game->map.start_x = j;
					game->map.start_y = i;
				}
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	count_map_chars(t_game *game)
{
	int	exit;
	int	p_start;

	p_start = count_char(game, 'P');
	exit = count_char(game, 'E');
	game->map.n_collectible = count_char(game, 'C');
	game->map.n_enemies = count_char(game, 'F');
	if (p_start != 1 || exit != 1 || game->map.n_collectible < 1)
		return (1);
	return (0);
}
