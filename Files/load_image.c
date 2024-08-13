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
	//if (sprite_type == 6)
	//	game->enemies.sprites[i] = mlx_xpm_file_to_image(game->mlx, sprite_path, &pixel, &pixel);

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
		free(num);
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


