#include "game.h"

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
			if (game->map.width == -1)
				return (1);
			return (0);
		}
		if (game->map.width == -1)
			game->map.width = ft_strlen(line) - 1;
		if (game->map.lst_map == NULL)
			game->map.lst_map = ft_lstnew(line);
		else
			ft_lstadd_back(&game->map.lst_map, ft_lstnew(line));
	}
	return (0);
}

int	map_to_two_d(t_game *game)
{
	int	i;

	i = 0;
	game->map.height = ft_lstsize(game->map.lst_map);
	if (game->map.height < 3)
		return (1);
	game->map.map = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.map)
		exit(EXIT_FAILURE);
	while(game->map.lst_map)
	{
		game->map.map[i] = ft_strdup(game->map.lst_map->content);
		if (!game->map.map[i])
			exit(EXIT_FAILURE);
		i++;
		game->map.lst_map = game->map.lst_map->next;
	}
	game->map.width = ft_strlen(game->map.map[0]) - 2;
	if (game->map.width < 4)
		return (1);
	return (0);
}

int	map_size(t_game *game)
{
	if (game->map.height == game->map.width)
		return (1);
	return (0);
}

int	check_char(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (!(game->map.map[i][j] == '0'))
				if (!(game->map.map[i][j] == 'P' || game->map.map[i][j] == 'C'
				|| game->map.map[i][j] == 'E' || game->map.map[i][j] == '1'
				|| game->map.map[i][j] == 'F'
				|| (i == game->map.height && game->map.map[i][j] == '\n')))
					return (1);
			if (i == game->map.height && game->map.map[i][j] != '\n' )
				return (1);
			ft_printf("%c",game->map.map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	return (0);
}
