/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_map_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:52:16 by joseferr          #+#    #+#             */
/*   Updated: 2024/11/08 20:51:03 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_game.h"

int	ft_validate_map(int argc, char **argv, t_game *game)
{
	(void)argv;
	if (argc != 2)
		free_wrong_map(game, 0);
	if (open_map(argv[1], game))
		free_wrong_map(game, 0);
	if (map_to_lst(game))
		free_wrong_map(game, 1);
	if (map_to_two_d(game))
		free_wrong_map(game, 1);
	if (map_rectangle(game))
		free_wrong_map(game, 1);
	if (check_char(game))
		free_wrong_map(game, 1);
	if (surrounded(game))
		free_wrong_map(game, 1);
	if (count_map_chars(game))
		free_wrong_map(game, 1);
	if (map_possible(game))
		free_wrong_map(game, 1);
	return (0);
}

int	open_map(char *map_path, t_game *game)
{
	int	path_lenght;

	path_lenght = ft_strlen(map_path);
	if (path_lenght < 4)
		return (1);
	if (ft_strcmp(&map_path[path_lenght - 4], ".ber") != 0)
		return (1);
	game->map.map_fd = open(map_path, O_RDONLY);
	if (game->map.map_fd < 0)
		return (1);
	return (0);
}

int	map_to_lst(t_game *game)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(game->map.map_fd);
		if (line == NULL)
		{
			if (game->map.columns == -1)
				return (1);
			return (0);
		}
		if (game->map.columns == -1)
			game->map.columns = ft_strlen(line) - 1;
		if (game->map.lst_map == NULL)
			game->map.lst_map = ft_lstnew(line);
		else
			ft_lstadd_back(&game->map.lst_map, ft_lstnew(line));
	}
	return (0);
}

int	map_to_two_d(t_game *game)
{
	int		i;
	t_list	*current;

	i = 0;
	game->map.rows = ft_lstsize(game->map.lst_map);
	if (game->map.rows < 3)
		return (1);
	game->map.map = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!game->map.map)
		return (1);
	current = game->map.lst_map;
	while (current)
	{
		game->map.map[i] = ft_strdup(current->content);
		if (!game->map.map[i])
			return (1);
		i++;
		current = current->next;
	}
	free_list(game->map.lst_map);
	game->map.columns = ft_strlen(game->map.map[0]) - 1;
	if (game->map.columns < 4)
		return (1);
	return (0);
}

int	map_rectangle(t_game *game)
{
	if (game->map.rows == game->map.columns)
	{
		free_map(game->map.map, game->map.rows);
		free_wrong_map(game, 1);
		return (1);
	}
	return (0);
}
