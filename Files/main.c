/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:25:43 by joseferr          #+#    #+#             */
/*   Updated: 2024/08/05 15:13:43 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include "libft/libft.h"
# include <math.h>


# define WIDTH 1280
# define HEIGHT 720
# define PIXEL 32
# define HEALTH 5
# define MOVE_SPEED 2
# define DEBUG 1

typedef struct s_img
{
	void	*mlx_img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}			t_img;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		health;
	int		steps;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		attack;
	int		current_sprite;
	int		move_sprite_index;
	int		portal_sprite_index;
	void	*sprites[15];
}			t_player;

typedef struct s_enemy
{
	int		pos_x;
	int		pos_y;
	int		direction;
	int		frame;
}			t_enemy;

typedef struct s_collectible
{
	int		pos_x;
	int		pos_y;
	int		frame;
	int		collected;
}				t_collectible;

typedef struct s_map
{
	int				map_fd;
	t_list			*lst_map;
	char			**map;
	int				player_start_x;
	int				player_start_y;
	int				n_enemy;
	int				n_collectible;
	int				n_collected;
	t_collectible	**collectibles;
	void			*collectible_sprite[15];
	t_enemy			**enemies;
	void			*enemies_sprite[5];
	void			*window_sprite[15];
	int				n_portal;
	void			*portal_sprites[10];
	int				width;
	int				height;
}					t_map;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				movements;
	int				game_started;
	long long		last_millitimestamp;
	int				fps;
	t_player		player;
	t_map			map;
	}				t_game;


void make_black_transparent(t_img *image)
{
	int x, y;

	for (y = 0; y < image->height; y++)
	{
		for (x = 0; x < image->width; x++)
		{
			int pixel = image->data[y * image->size_line / 4 + x];
			int r = (pixel >> 16) & 0xFF;
			int g = (pixel >> 8) & 0xFF;
			int b = pixel & 0xFF;

			// Check if the pixel is black
			if (r == 0 && g == 0 && b == 0)
			{
				// Set the pixel to transparent (ARGB format, 0xAARRGGBB)
				image->data[y * image->size_line / 4 + x] = 0x00000000;
			}
		}
	}
}

t_img *load_image(void *mlx, char *path)
{
	t_img *image;

	image = malloc(sizeof(t_img));
	if (!image)
		return (NULL);
	image->mlx_img = mlx_xpm_file_to_image(mlx, path, &image->width, &image->height);
	if (!image->mlx_img)
	{
		free(image);
		return (NULL);
	}
	image->data = (int *)mlx_get_data_addr(image->mlx_img, &image->bpp, &image->size_line, &image->endian);
	make_black_transparent(image);
	return (image);
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

int close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC key
		exit(0);
	if (keycode == 119) // W key
		game->player.move_up = 1;
	if (keycode == 97) // A key
		game->player.move_left = 1;
	if (keycode == 115) // S key
		game->player.move_down = 1;
	if (keycode == 100) // D key
		game->player.move_right = 1;
	if (keycode == 13) // D key
		game->player.attack = 1;
	return (0);
}

int handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == 119) // W key
		game->player.move_up = 0;
	if (keycode == 97) // A key
		game->player.move_left = 0;
	if (keycode == 115) // S key
		game->player.move_down = 0;
	if (keycode == 100) // D key
		game->player.move_right = 0;
	if (keycode == 13) // D key
		game->player.attack = 1;
	return (0);
}


void	ft_ready_game(t_game *game)
{
	game->movements = 0;
	game->game_started = 0;
	game->last_millitimestamp = 0;
	game->map.n_collectible = 0;
	game->map.n_collected = 0;
	game->map.height = -1;
	game->map.width = -1;
	game->map.n_portal = 0;
	game->map.lst_map = NULL;
	game->mlx = mlx_init();
}

// Get timestamp in milliseconds
long long	millitimestamp(void)
{
	struct timeval	timeval;
	long long		microtime;

	gettimeofday(&timeval, NULL);
	microtime = timeval.tv_sec * 1000LL + timeval.tv_usec / 1000;
	return (microtime);
}

// Show FPS in the window
void	show_fps(t_game *game)
{
	char	*debug_msg;
	char	*fps;

	fps = ft_itoa(game->fps);
	debug_msg = ft_strjoin("FPS: ", fps);
	mlx_string_put(game->mlx, game->win, 10, 20, 11001101, debug_msg);
	free(fps);
	free(debug_msg);
}

// Calculate FPS
void	fps(t_game *game)
{
	long long	now;

	now = millitimestamp();
	if (now > game->last_millitimestamp)
	{
		game->fps = 960 / (now - game->last_millitimestamp);
		game->last_millitimestamp = now;
	}
}

void	hook_register(t_game *game)
{
		mlx_hook(game->win, 2, 1L<<0, handle_keypress, game);
		mlx_hook(game->win, 3, 1L<<1, handle_keyrelease, game);
		mlx_hook(game->win, 17, 1L<<17, close_window, game);
}

void	ft_collectible(t_game *game, long long now)
{
	int					i;
	t_collectible		*collectible;
	static long long	last_collectible_update = 0;
	long long			diff_millisecs;

	diff_millisecs = now - last_collectible_update;
	i = 0;
	while (i < game->map.n_collectible)
	{
		collectible = game->map.collectibles[i];
		if (!collectible->collected)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->map.collectible_sprite[collectible->frame], collectible->pos_x * PIXEL, collectible->pos_y * PIXEL);
		}
		if (diff_millisecs > 120)
		{
			if (collectible->frame < 10)
				collectible->frame++;
			else
				collectible->frame = 0;
		}
		i++;
	}
	// Update the last collectible update time only if the frames have been updated
	if (diff_millisecs > 120)
	{
		last_collectible_update = now;
	}
}


void	ft_collect(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->map.n_collectible)
	{
		t_collectible *collectible = game->map.collectibles[i];
		if (collectible->pos_x == x && collectible->pos_y == y && !collectible->collected)
		{
			collectible->collected = 1;
			game->map.n_collected++;
		}
		i++;
	}
}

void	check_collectible(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'C') {
		ft_collect(game, map_x, map_y);
		game->map.map[map_y][map_x] = '0';
	}
}

void	check_exit(t_game *game, int map_x, int map_y)
{
	if (game->map.map[map_y][map_x] == 'E') {
		if ((game->map.n_collectible - game->map.n_collected) == 0)
			exit(EXIT_SUCCESS);
	}
}

void	show_steps(t_game *game)
{
	char	*steps_msg;
	char	*steps;

	steps = ft_itoa(game->player.steps);
	steps_msg = ft_strjoin("Steps: ", steps);
	mlx_string_put(game->mlx, game->win, 70, 20, 11001101, steps_msg);
	free(steps);
	free(steps_msg);
}

void	ft_player(t_game *game)
{
	int			next_x;
	int			next_y;

	next_x = game->player.pos_x;
	next_y = game->player.pos_y;
	// Calculate next position based on input
	if (game->player.move_up)
		next_y -= MOVE_SPEED;
	if (game->player.move_down)
		next_y += MOVE_SPEED;
	if (game->player.move_left)
		next_x -= MOVE_SPEED;
	if (game->player.move_right)
		next_x += MOVE_SPEED;

	// Calculate map indices for the next position
	int map_x1 = next_x / PIXEL;
	int map_y1 = next_y / PIXEL;
	int map_x2 = (next_x + PIXEL - 1) / PIXEL;
	int map_y2 = (next_y + PIXEL - 1) / PIXEL;

	// Check for collision with walls
	if (game->map.map[map_y1][map_x1] != '1' && game->map.map[map_y1][map_x2] != '1' &&
		game->map.map[map_y2][map_x1] != '1' && game->map.map[map_y2][map_x2] != '1')
	{
		// Check for collectibles
		check_collectible(game, map_x1, map_y1);
		check_collectible(game, map_x2, map_y1);
		check_collectible(game, map_x1, map_y2);
		check_collectible(game, map_x2, map_y2);

		// Check for exit
		check_exit(game, map_x1, map_y1);
		check_exit(game, map_x2, map_y1);
		check_exit(game, map_x1, map_y2);
		check_exit(game, map_x2, map_y2);

		if(game->player.pos_x != next_x || game->player.pos_y != next_y)
		{
			game->player.steps += 1;
			ft_printf("Steps: %d\n", game->player.steps);
		}
		// Update player position
		game->player.pos_x = next_x;
		game->player.pos_y = next_y;


	}
	// Render the player
	mlx_put_image_to_window(game->mlx, game->win, game->player.sprites[game->player.move_sprite_index], game->player.pos_x, game->player.pos_y);
}


void	ft_exit(t_game *game, long long now)
{
	int	i;
	int	j;
	int	end;
	static long long last_portal_update = 0;
	long long diff_millisecs;

	diff_millisecs = now - last_portal_update;

	i = 0;
	end = game->map.n_collectible - game->map.n_collected;
	if (diff_millisecs > 150)
	{
		if (game->map.n_portal < 7)
			game->map.n_portal++;
		else
			game->map.n_portal = 0;
		last_portal_update = now;
	}

	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == 'E' && end != 0)
				mlx_put_image_to_window(game->mlx, game->win, game->map.portal_sprites[6], j * PIXEL, i * PIXEL);
			else if (game->map.map[i][j] == 'E' && end == 0)
				mlx_put_image_to_window(game->mlx, game->win, game->map.portal_sprites[game->map.n_portal], j * PIXEL, i * PIXEL);
			j++;
		}
		i++;
	}
}


void	sprite_player_up(t_game *game, long long now)
{
	static long long last_player_update = 0;
	long long diff_millisecs;

	diff_millisecs = now - last_player_update;

	// Update the sprite only if 120 milliseconds have passed
	if (diff_millisecs > 120)
	{
		if (game->player.move_up || game->player.move_down || game->player.move_left || game->player.move_right)
		{
			if (game->player.move_sprite_index < 10)
				game->player.move_sprite_index++;
			else
				game->player.move_sprite_index = 3;
		}
		else
		{
			if (game->player.move_sprite_index < 2)
				game->player.move_sprite_index++;
			else
				game->player.move_sprite_index = 0;
		}
		// Update the last player update time
		last_player_update = now;
	}
}


int	game_loop(t_game *game)
{
	long long now;
	long long diff_millisecs;

	now = millitimestamp();
	diff_millisecs = now - game->last_millitimestamp;
	if (diff_millisecs > 30)
	{
		fps(game);
		mlx_clear_window(game->mlx, game->win);
		fill_map(game->mlx, game->win, game->map);
		ft_collectible(game, now);
		ft_exit(game, now);
		//move_monsters(game);
		sprite_player_up(game, now);
		ft_player(game);
		if (DEBUG)
		{
			show_steps(game);
			show_fps(game);
		}

		game->last_millitimestamp = now;
	}
	return (1);
}


void	janitor(int error)
{
	if (error == 1)
		printf("Invalid Arguments\n");
	else if (error == 2)
		printf("Invalid Map File\n");
	else if (error == 3)
		printf("map_to_lst\n");
	else if (error == 4)
		printf("map_to_two_d\n");
	else if (error == 5)
		printf("map_size\n");
	else if (error == 6)
		printf("check_char\n");
	else if (error == 7)
		printf("surrounded\n");
	else if (error == 8)
		printf("count_char\n");
	else if (error == 9)
		printf("Invalid Map File\n");
	else if (error == 10)
		printf("Invalid Map File\n");
	else if (error == 11)
		printf("Invalid Map File\n");
	exit(EXIT_FAILURE);
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
	game->map.width = ft_strlen(game->map.map[0]) - 1;
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
		while (j < game->map.width - 1)
		{
			if (!(game->map.map[i][j] == '0'))
				if (!(game->map.map[i][j] == 'P' || game->map.map[i][j] == 'C'
				|| game->map.map[i][j] == 'E' || game->map.map[i][j] == '1'
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
void	ft_init_collectible(t_game *game)
{
	int	collectible_index;
	int	w;
	int	h;

	collectible_index = 0;
	game->map.collectibles = malloc(game->map.n_collectible * sizeof(t_collectible *));
	if (!game->map.collectibles)
	{
		fprintf(stderr, "Failed to allocate memory for collectibles\n");
		exit(EXIT_FAILURE);
	}
	for (h = 0; h < game->map.height; h++)
	{
		for (w = 0; w < game->map.width; w++)
		{
			if (game->map.map[h][w] == 'C')
			{
				t_collectible *collectible = malloc(sizeof(t_collectible));
				if (!collectible)
				{
					fprintf(stderr, "Failed to allocate memory for a collectible\n");
					exit(EXIT_FAILURE);
				}

				collectible->pos_x = w;
				collectible->pos_y = h;
				collectible->frame = rand() % 10;
				collectible->collected = 0;

				game->map.collectibles[collectible_index++] = collectible;
			}
		}
	}

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
				p_start++;
			if (game->map.map[i][j] == 'E')
				exit++;
			if (game->map.map[i][j] == 'C')
				game->map.n_collectible++;
			j++;
		}
		i++;
	}
	if ( p_start != 1 || exit != 1 || game->map.n_collectible < 1)
		return (1);
	return (0);
}

int	surrounded(t_game *game)
{
	int	i;

	i = 0;
	printf("width: %d, height: %d\n", game->map.width, game->map.height);
	while (i < game->map.width - 1)
	{
		if (game->map.map[0][i] != '1' && game->map.map[game->map.height - 1][i])
			return (1);
		i++;
	}
	i = 0;
	while (i < game->map.height - 1)
	{
		if (game->map.map[i][0] != '1' && game->map.map[i][game->map.width - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_map(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		janitor(1);
	if (open_map(argv[1], game))
		janitor(2);
	if (map_to_lst(game))
		janitor(3);
	if (map_to_two_d(game))
		janitor(4);
	if (map_size(game))
		janitor(5);
	if (check_char(game))
		janitor(6);
	if (surrounded(game))
		janitor(7);
	if (count_char(game))
		janitor(8);
	return (0);
}


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

int	ft_init_player(t_game *game)
{
	int	w;
	int	h;

	w = 0;
	while (game->map.map[w])
	{
		h = 0;
		while (game->map.map[w][h])
		{
			if (game->map.map[w][h] == 'P')
			{
				game->player.pos_x = w * PIXEL;
				game->player.pos_y = h * PIXEL;
			}
			h++;
		}
		w++;
	}
	game->player.health = HEALTH;
	game->player.steps = 0;
	game->player.move_up = 0;
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	return (0);
}

/*
int create_monster(t_game *game, int w, int h)
{
	game->maps.enemies[game->map.n_enemy].pos_x = h * PIXEL;
	game->enemies[game->map.n_enemy].pos_y = w * PIXEL;
	game->enemies[game->map.n_enemy].direction = rand() % 4;
	game->enemies[game->map.n_enemy].sprite_index = 0;
	game->map.n_enemy++;
	return (0);
}
*/
int ft_check_monsters(t_game *game)
{
	game->map.n_enemy = 0;
	return (1);
}


void	ft_init_window(t_game *game, char *path)
{
	game->win = mlx_new_window(game->mlx, game->map.width * PIXEL, game->map.height * PIXEL, path);
}


int	main(int argc, char **argv)
{
	t_game	game;

	ft_ready_game(&game);
	ft_init_map(argc, argv, &game);
	ft_init_window(&game, argv[1]);
	ft_init_sprite(&game);
	ft_init_player(&game);
	ft_init_collectible(&game);
	ft_check_monsters(&game);
	hook_register(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	exit(EXIT_SUCCESS);
}
