#include "game.h"

void	fill_map(void *mlx_pointer, void *mlx_window, t_map mapa)
{
	int		i;
	int		j;
	int		pixel;
	int		tile_id;

	pixel = PIXEL;
	i = 0;
	while (mapa.map[i])
	{
		j = 0;
		while (mapa.map[i][j])
		{
			tile_id = (i * j) % 10;
			if (mapa.map[i][j] == '1')
				mlx_put_image_to_window(mlx_pointer, mlx_window, mapa.window_sprite[10], j * pixel, i * pixel);
			if (mapa.map[i][j] == '0' || mapa.map[i][j] == 'P' || mapa.map[i][j] == 'C' || mapa.map[i][j] == 'E' || mapa.map[i][j] == 'F')
				mlx_put_image_to_window(mlx_pointer, mlx_window, mapa.window_sprite[tile_id], j * pixel, i * pixel);
			j++;
		}
		i++;
	}
}
