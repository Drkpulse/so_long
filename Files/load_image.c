// load_image.c
#include "game.h"

void	load_xpm_sprite(t_game *game, int i, int sprite_type, char* sprite_path)
{
	int		pixel;

	pixel = PIXEL;
	if (sprite_type == 1)
		game->map.window_sprite[i] = mlx_xpm_file_to_image(game->mlx, sprite_path, &pixel, &pixel);
	if (sprite_type == 2)
		game->map.window_sprite[i] = mlx_xpm_file_to_image(game->mlx, sprite_path, &pixel, &pixel);
	if (sprite_type == 3)
		game->map.portal_sprites[i] = mlx_xpm_file_to_image(game->mlx, sprite_path, &pixel, &pixel);
	if (sprite_type == 4)
		game->player.sprites[i] = mlx_xpm_file_to_image(game->mlx, sprite_path, &pixel, &pixel);
	if (sprite_type == 5)
		game->map.collectible_sprite[i] = mlx_xpm_file_to_image(game->mlx, sprite_path, &pixel, &pixel);

}

int	ft_load_sprite(t_game *game, int n_sprt, int sprite_type, char *path)
{
	int		i;
	char	*num;
	char	*str;
	char	*filetype = {".xpm"};
	char	*filepath;

	i = 0;
	while (i < n_sprt)
	{
		num = ft_itoa(i);
		str = ft_strjoin(path, num);
		filepath = ft_strjoin(str, filetype);
		free(str);
		load_xpm_sprite(game, i, sprite_type, filepath);
		free(filepath);
		i++;
	}
	return (0);
}

int	ft_init_sprite(t_game *game)
{
	if(ft_load_sprite(game, 11, 1,"assets/map/floor"))
		return (1);
	if(ft_load_sprite(game, 9, 3, "assets/exit/exit"))
		return (1);
	if(ft_load_sprite(game, 14, 4, "assets/character/char"))
		return (1);
	if(ft_load_sprite(game, 11, 5, "assets/collect/coin"))
		return (1);
	return (0);
}

void	fill_map(void *mlx_pointer, void *mlx_window, t_map mapa)
{
	int		i;
	int		j;
	int		pixel;
	int		random;

	pixel = PIXEL;
	i = 0;
	while (mapa.map[i])
	{
		j = 0;
		while (mapa.map[i][j])
		{
			random = (i * j) % 10;
			if (mapa.map[i][j] == '1')
				mlx_put_image_to_window(mlx_pointer, mlx_window, mapa.window_sprite[10], j * pixel, i * pixel);
			if (mapa.map[i][j] == '0' || mapa.map[i][j] == 'P' || mapa.map[i][j] == 'C' || mapa.map[i][j] == 'E')
				mlx_put_image_to_window(mlx_pointer, mlx_window, mapa.window_sprite[random], j * pixel, i * pixel);
			j++;
		}
		i++;
	}
}
