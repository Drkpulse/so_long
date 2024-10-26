#include "game.h"

int	ft_validate_map(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		janitor(1);
	if (open_map(argv[1], game))
		janitor(2);
	if (map_to_lst(game))
		janitor(3);
	if (map_to_two_d(game))
		janitor(4);
	if (map_rectangle(game))
		janitor(5);
	if (check_char(game))
		janitor(6);
	if (surrounded(game))
		janitor(7);
	if (count_char(game))
		janitor(8);
	if (map_possible(game))
		janitor(8);
	return (0);
}

int	open_map(char *map_path, t_game *game)
{
	int	path_lenght;

	path_lenght = ft_strlen(map_path);
	if (path_lenght < 4)
		return(1);
	if (ft_strcmp(&map_path[path_lenght-4], ".ber") != 0)
		return(1);
	game->map.map_fd = open(map_path, O_RDONLY);
	if (game->map.map_fd < 0)
		return (1);
	return (0);

}

int	map_to_lst(t_game *game)
{
	char	*line;

	line = "";
	while(line)
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



int map_to_two_d(t_game *game)
{
	int i;
	t_list *current;

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
	game->map.columns = ft_strlen(game->map.map[0]) - 2;
	if (game->map.columns < 4)
		return (1);
	return (0);
}


int	map_rectangle(t_game *game)
{
	if (game->map.rows == game->map.columns)
		return (1);
	return (0);
}
