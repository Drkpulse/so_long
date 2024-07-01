/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:25:43 by joseferr          #+#    #+#             */
/*   Updated: 2024/07/01 13:35:42 by joseferr         ###   ########.fr       */
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
# define MOVE_SPEED 32
# define DEBUG 1

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		health;
	int		mana;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
}			t_player;

typedef struct s_enemy
{
	int		pos_x;
	int		pos_y;
	int		direction;
	int		sprite_index;
	void	*enemy_sprite[5];
}			t_enemy;


typedef struct s_map
{
	int				map_fd;
	t_list			*lst_map;
	char			**map;
	int				player_start_x;
	int				player_start_y;
	int				n_enemy;
	int				n_collectible;
	void			*collectible_sprite[5];
	void			*window_sprite[2];
	int				width;
	int				height;
}			t_map;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				movements;
	int				game_started;
	void			*player_sprite[10];
	void			*exit_sprite[5];
	long long		last_millitimestamp;
	int				fps;
	t_enemy			*enemies;
	t_player		player;
	t_map			map;
	}			t_game;


void	fill_map(void *mlx_pointer, void *mlx_window, t_map mapa)
{
	int		i;
	int		j;
	int		pixel;

	pixel = PIXEL;
	i = 0;
	while (mapa.map[i])
	{
		j = 0;
		while (mapa.map[i][j])
		{
			if (mapa.map[i][j] == '1')
				mlx_put_image_to_window(mlx_pointer, mlx_window, mapa.window_sprite[1], j * pixel, i * pixel);
			if (mapa.map[i][j] == '0' || mapa.map[i][j] == 'P' || mapa.map[i][j] == 'C' || mapa.map[i][j] == 'E')
				mlx_put_image_to_window(mlx_pointer, mlx_window, mapa.window_sprite[0], j * pixel, i * pixel);
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

	printf("Key Press: %d, %d\n", keycode, game->player.move_up); // Debugging key press

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

	printf("Key Release: %d%d\n", keycode, game->player.move_up); // Debugging key release

	return (0);
}


void	ft_ready_game(t_game *game)
{
	game->movements = 0;
	game->game_started = 0;
	game->last_millitimestamp = 0;
	game->map.n_collectible = 0;
	game->map.height = -1;
	game->map.width = -1;
	game->map.lst_map = NULL;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "So_Long");
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
		mlx_hook(game->win, 2, 1L<<0, handle_keypress, &game);
		mlx_hook(game->win, 3, 1L<<1, handle_keyrelease, &game);
		mlx_hook(game->win, 17, 1L<<17, close_window, &game);
}

void	create_collectible(t_game *game, int w, int h)
{
	int	pixel;

	pixel = PIXEL;
	mlx_put_image_to_window(game->mlx, game->win, game->map.collectible_sprite[0], h * pixel, w * pixel);
}
void	ft_collectible(t_game *game)
{
	int	w;
	int	h;

	w = 0;
	while (game->map.map[w])
	{
		h = 0;
		while (game->map.map[w][h])
		{
			if (game->map.map[w][h] == 'C')
			{
				create_collectible(game, w, h);
			}
			h++;
		}
		w++;
	}
}

void ft_player(t_game *game)
{
	int next_x;
	int next_y;

	next_x = game->player.pos_x;
	next_y = game->player.pos_y;
	// Calculate next position based on input
	if (game->player.move_up)
		next_y -= 32;
	if (game->player.move_down)
		next_y += 32;
	if (game->player.move_left)
		next_x -= 32;
	if (game->player.move_right)
		next_x += 32;

	// Debug: Log the calculated next position
	printf("Next Position: X: %d, Y: %d, Player UP: %d\n", next_x, next_y, game->player.move_up);

	// Calculate map indices for the next position
	int map_x = next_x / PIXEL;
	int map_y = next_y / PIXEL;

	// Check collision with walls
	if (game->map.map[map_y][map_x] != '1')
	{
		// Check for collectible
		if (game->map.map[map_y][map_x] == 'C')
		{
			game->map.map[map_y][map_x] = '0'; // Remove collectible from map
			game->map.n_collectible--;
		}
		// Update player position
		game->player.pos_x = next_x;
		game->player.pos_y = next_y;
	}

	// Debug: Log the updated player position
	printf("Updated Player Position: X: %d, Y: %d and next %d,%d\n", game->player.pos_x, game->player.pos_y,next_x ,next_y);

	/* Prevent player from moving out of bounds
	if (game->player.pos_x < 0)
		game->player.pos_x = 0;
	if (game->player.pos_x + PIXEL > WIDTH)
		game->player.pos_x = WIDTH - PIXEL;
	if (game->player.pos_y < 0)
		game->player.pos_y = 0;
	if (game->player.pos_y + PIXEL > HEIGHT)
		game->player.pos_y = HEIGHT - PIXEL;
	*/
	// Render the player
	mlx_put_image_to_window(game->mlx, game->win, game->player_sprite[0], game->player.pos_x, game->player.pos_y);
}

void move_monsters(t_game *game)
{
	int	i;
	int	next_x;
	int	next_y;
	int	index;

	i = 0;
	while (i < game->map.n_enemy)
	{
		index = game->enemies[i].sprite_index;
		next_x = game->enemies[i].pos_x;
		next_y = game->enemies[i].pos_y;

		if (game->enemies[i].direction == 0)
			next_y -= MOVE_SPEED;
		else if (game->enemies[i].direction == 1)
			next_y += MOVE_SPEED;
		else if (game->enemies[i].direction == 2)
			next_x -= MOVE_SPEED;
		else if (game->enemies[i].direction == 3)
			next_x += MOVE_SPEED;

		int map_x = next_x / PIXEL;
		int map_y = next_y / PIXEL;

		if (game->map.map[map_y][map_x] != '1')
		{
			game->enemies[i].pos_x = next_x;
			game->enemies[i].pos_y = next_y;
		}
		else
		{
			game->enemies[i].direction = rand() % 4;
		}
		mlx_put_image_to_window(game->mlx, game->win, game->enemies[i].enemy_sprite[index + 1], game->enemies[i].pos_x, game->enemies[i].pos_y);
		if (game->enemies[i].sprite_index < 4)
			game->enemies[i].sprite_index++;
		else
			game->enemies[i].sprite_index = 0;
		i++;
	}
}



int game_loop(t_game *game)
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
		ft_collectible(game);
		ft_player(game);
		move_monsters(game);
		if (DEBUG)
			show_fps(game);
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
		while (j < game->map.width)
		{
			if (!(game->map.map[i][j] == '0'))
				if (!(game->map.map[i][j] == 'P' || game->map.map[i][j] == 'C'
				|| game->map.map[i][j] == 'E' || game->map.map[i][j] == '1'
				|| (i == game->map.height && game->map.map[i][j] == '\n')))
					return (1);
			if (i == game->map.height && game->map.map[i][j] != '\n' )
				return (1);
			j++;
		}
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
	while (i < game->map.width)
	{
		if (game->map.map[0][i] != '1' && game->map.map[game->map.height - 1][i])
			return (1);
		i++;
	}
	i = 1;
	while (i < game->map.height)
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

int	ft_init_sprite(t_game *game)
{
	int	pixel;
	pixel = 32;

	game->map.window_sprite[0] = mlx_xpm_file_to_image(game->mlx,"img_floor32.xpm", &pixel, &pixel);
	game->map.window_sprite[1] = mlx_xpm_file_to_image(game->mlx,"img_wall32.xpm", &pixel, &pixel);
	game->player_sprite[0] = mlx_xpm_file_to_image(game->mlx,"assets/character/c1.xpm", &pixel, &pixel);
	game->map.collectible_sprite[0] = mlx_xpm_file_to_image(game->mlx,"assets/character/c1.xpm", &pixel, &pixel);
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
				printf("Player Starting Pos X: %d Y: %d\n", game->player.pos_x, game->player.pos_y);
			}
			h++;
		}
		w++;
	}
	game->player.health = HEALTH;
	game->player.mana = 0;
	game->player.move_up = 0;
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	return (0);
}

int create_monster(t_game *game, int w, int h)
{
	game->enemies[game->map.n_enemy].pos_x = h * PIXEL;
	game->enemies[game->map.n_enemy].pos_y = w * PIXEL;
	game->enemies[game->map.n_enemy].direction = rand() % 4; // Random initial direction
	game->enemies[game->map.n_enemy].sprite_index = 0;
	game->map.n_enemy++;
	return (0);
}

int ft_check_monsters(t_game *game)
{
	int w, h;

	game->map.n_enemy = 0;
	w = 0;
	while (game->map.map[w])
	{
		h = 0;
		while (game->map.map[w][h])
		{
			if (game->map.map[w][h] == 'M')
			{
				create_monster(game, w, h);
			}
			h++;
		}
		w++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_game	game;

	ft_ready_game(&game);
	ft_init_map(argc, argv, &game);
	ft_init_sprite(&game);
	ft_init_player(&game);
	ft_check_monsters(&game);
	hook_register(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	exit(EXIT_SUCCESS);
}


/*
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int handle_resize()
{
	printf("Window resized\n");
	return (0);
}

int handle_mouse_enter()
{
	printf("Hello!\n");
	return (0);
}

int handle_mouse_leave()
{
	printf("Bye!\n");
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("\n%d", keycode);
	if (keycode == 65307) // ESC key
		close_window(vars);
	return (0);
}

int	mouse_hook(int keycode)
{
	printf("\n%d", keycode);
	return (0);
}

int main(void)
{
	t_vars  vars;
	t_data  img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1280, 720, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00cd00ff);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 12, 1L<<15, handle_resize, &vars); // Expose event for resizing
	mlx_hook(vars.win, 17, 1L<<17, close_window, &vars); // DestroyNotify event (window close)
	mlx_hook(vars.win, 7, 1L<<4, handle_mouse_enter, &vars); // EnterNotify event
	mlx_hook(vars.win, 8, 1L<<5, handle_mouse_leave, &vars); // LeaveNotify event
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);

	mlx_loop(vars.mlx);
}

*/

/*
typedef struct s_data {
	void    *mlx;
	void    *win;
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
	int     color_shift;
	int     circle_x;
	int     circle_y;
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

int render_next_frame(t_data *data)
{
	int x, y;
	int color;

	// Update color shift
	data->color_shift = (data->color_shift + 1) % 1536;

	// Clear the screen with the shifting color
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			if (data->color_shift < 512)
				color = (data->color_shift << 16) | ((255 - data->color_shift) << 8);
			else if (data->color_shift < 1024)
				color = ((1023 - data->color_shift) << 8) | ((255 - (data->color_shift - 512)) << 16);
			else
				color = ((data->color_shift - 1024) << 8) | ((255 - (data->color_shift - 1024)));
			my_mlx_pixel_put(data, x, y, color);
		}
	}

	// Draw the circle at its current position
	int radius = 100;
	for (y = -radius; y <= radius; y++)
	{
		for (x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
				my_mlx_pixel_put(data, data->circle_x + x, data->circle_y + y, 0xFFFFFF);
		}
	}

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC key
		exit(0);
	if (keycode == 119) // W key
		data->circle_y -= 200;
	if (keycode == 97) // A key
		data->circle_x -= 200;
	if (keycode == 115) // S key
		data->circle_y += 200;
	if (keycode == 100) // D key
		data->circle_x += 200;
	return (0);
}

int main(void)
{
	t_data  data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Animation");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.color_shift = 0;
	data.circle_x = WIDTH / 2;
	data.circle_y = HEIGHT / 2;

	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_key_hook(data.win, handle_keypress, &data);
	mlx_loop(data.mlx);
}
*/

/*
#define WIDTH 1280
#define HEIGHT 720
#define RADIUS 50
#define ENEMY_SIZE 20
#define COLLECTIBLE_SIZE 10
#define CIRCLE_SPEED 10
#define ENEMY_SPEED 2
#define SAFE_DISTANCE 200 // Minimum distance between circle and enemy when spawning

typedef struct s_data {
	void    *mlx;
	void    *win;
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
	int     circle_x;
	int     circle_y;
	int     circle_health;
	int     enemy_x;
	int     enemy_y;
	int     collectible_x;
	int     collectible_y;
	int     has_collectible;
	int     move_up;
	int     move_down;
	int     move_left;
	int     move_right;
	int     score;
	int     window_width;
	int		window_height;
	int     game_started;
	int     frames;
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void    clear_image(t_data *data, int color)
{
	int x, y;
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}

void    draw_circle(t_data *data, int x, int y, int radius, int color)
{
	int dx, dy;
	for (dy = -radius; dy <= radius; dy++)
	{
		for (dx = -radius; dx <= radius; dx++)
		{
			if (dx * dx + dy * dy <= radius * radius)
				my_mlx_pixel_put(data, x + dx, y + dy, color);
		}
	}
}

void    draw_square(t_data *data, int x, int y, int size, int color)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
		}
	}
}

void    draw_edges(t_data *data, int color)
{
	int x, y;
	for (x = 0; x < WIDTH; x++)
	{
		my_mlx_pixel_put(data, x, 0, color);
		my_mlx_pixel_put(data, x, HEIGHT - 1, color);
	}
	for (y = 0; y < HEIGHT; y++)
	{
		my_mlx_pixel_put(data, 0, y, color);
		my_mlx_pixel_put(data, WIDTH - 1, y, color);
	}
}

void    move_enemy(t_data *data)
{
	int dx = data->circle_x - data->enemy_x;
	int dy = data->circle_y - data->enemy_y;
	float distance = sqrt(dx * dx + dy * dy);
	if (distance != 0)
	{
		data->enemy_x += (dx / distance) * ENEMY_SPEED;
		data->enemy_y += (dy / distance) * ENEMY_SPEED;
	}
}

int check_collision(int x1, int y1, int size1, int x2, int y2, int size2)
{
	return (x1 < x2 + size2 && x1 + size1 > x2 && y1 < y2 + size2 && y1 + size1 > y2);
}

void update_circle_position(t_data *data)
{
	if (data->move_up)
		data->circle_y -= CIRCLE_SPEED;
	if (data->move_down)
		data->circle_y += CIRCLE_SPEED;
	if (data->move_left)
		data->circle_x -= CIRCLE_SPEED;
	if (data->move_right)
		data->circle_x += CIRCLE_SPEED;

	// Prevent circle from moving out of bounds
	if (data->circle_x - RADIUS < 0)
		data->circle_x = RADIUS;
	if (data->circle_x + RADIUS > WIDTH)
		data->circle_x = WIDTH - RADIUS;
	if (data->circle_y - RADIUS < 0)
		data->circle_y = RADIUS;
	if (data->circle_y + RADIUS > HEIGHT)
		data->circle_y = HEIGHT - RADIUS;
}

void respawn_enemy(t_data *data)
{
	int dx, dy;
	do {
		data->enemy_x = rand() % (WIDTH - ENEMY_SIZE);
		data->enemy_y = rand() % (HEIGHT - ENEMY_SIZE);
		dx = data->circle_x - data->enemy_x;
		dy = data->circle_y - data->enemy_y;
	} while (sqrt(dx * dx + dy * dy) < SAFE_DISTANCE);
}

int render_next_frame(t_data *data)
{
	clear_image(data, 0x000000); // Clear the screen with black color

	// Draw the edges
	draw_edges(data, 0xFFFFFF);

	// Draw the circle
	draw_circle(data, data->circle_x, data->circle_y, RADIUS, 0xFFFFFF);

	// Move and draw the enemy
	if (data->game_started) {
		update_circle_position(data);
		move_enemy(data);
	}
	if (data->has_collectible)
	{

		draw_square(data, data->enemy_x, data->enemy_y, ENEMY_SIZE, 0x00FF00); // Green if has collectible
	}
	else
		draw_square(data, data->enemy_x, data->enemy_y, ENEMY_SIZE, 0xFF0000); // Red if doesn't have collectible

	// Check collision between circle and enemy
	if (check_collision(data->circle_x - RADIUS, data->circle_y - RADIUS, RADIUS * 2, data->enemy_x, data->enemy_y, ENEMY_SIZE))
	{
		if (data->has_collectible)
		{
			// Destroy enemy if circle has collectible
			respawn_enemy(data);
			data->has_collectible = 0; // Lose the collectible after attack
			data->score += 10;
			printf("Score %d\n", data->score);
		}
		else
		{
			// Reduce health if circle collides with enemy
			data->circle_health -= 1;
			data->score -= 5;
			respawn_enemy(data);
			printf("Circle Health: %d\n", data->circle_health);
			if (data->circle_health <= 0)
			{
				printf("Game Over!\nFinal Score: %d\n", data->score);
				exit(0);
			}
		}
	}

	// Draw the collectible if not collected
	if (!data->has_collectible)
		draw_square(data, data->collectible_x, data->collectible_y, COLLECTIBLE_SIZE, 0x00FF00);

	// Check collision between circle and collectible
	if (check_collision(data->circle_x - RADIUS, data->circle_y - RADIUS, RADIUS * 2, data->collectible_x, data->collectible_y, COLLECTIBLE_SIZE))
	{
		data->has_collectible = 1; // Collect the collectible
		data->collectible_x = rand() % (WIDTH - COLLECTIBLE_SIZE);
		data->collectible_y = rand() % (HEIGHT - COLLECTIBLE_SIZE);
	}

	// Display the score
	char score_str[50];
	sprintf(score_str, "Score: %d", data->score);
	mlx_string_put(data->mlx, data->win, WIDTH / 2 - 50, 10, 0xFFFFFF, score_str);

	// Display the health
	char health_str[50];
	sprintf(health_str, "Health: %d", data->circle_health);
	mlx_string_put(data->mlx, data->win, WIDTH - 150, HEIGHT - 30, 0xFFFFFF, health_str);

	// Display "press any key to start" message
	if (!data->game_started && (data->frames / 30) % 2 == 0) // Flash every 30 frames
	{
		mlx_string_put(data->mlx, data->win, WIDTH / 2 - 100, HEIGHT / 2, 0xFFFFFF, "Press any key to start");
	}

	data->frames++;

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}


int handle_keypress(int keycode, t_data *data)
{
	if (!data->game_started) {
		data->game_started = 1;
	}

	if (keycode == 65307) // ESC key
		exit(0);
	if (keycode == 119) // W key
		data->move_up = 1;
	if (keycode == 97) // A key
		data->move_left = 1;
	if (keycode == 115) // S key
		data->move_down = 1;
	if (keycode == 100) // D key
		data->move_right = 1;

	return (0);
}

int handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == 119) // W key
		data->move_up = 0;
	if (keycode == 97) // A key
		data->move_left = 0;
	if (keycode == 115) // S key
		data->move_down = 0;
	if (keycode == 100) // D key
		data->move_right = 0;

	return (0);
}

int handle_resize(int width, int height, t_data *data)
{
	data->window_width = width;
	data->window_height = height;
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, width, height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}
int main(void)
{
	t_data  data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Animation");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.window_width = WIDTH;
	data.window_height = HEIGHT;
	data.circle_x = WIDTH / 2;
	data.circle_y = HEIGHT / 2;
	data.circle_health = 3; // Initial health
	respawn_enemy(&data);
	data.collectible_x = rand() % (WIDTH - COLLECTIBLE_SIZE);
	data.collectible_y = rand() % (HEIGHT - COLLECTIBLE_SIZE);
	data.has_collectible = 0;
	data.move_up = 0;
	data.move_down = 0;
	data.move_left = 0;
	data.move_right = 0;
	data.score = 0;
	data.game_started = 0;
	data.frames = 0;

	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_hook(data.win, 2, 1L<<0, handle_keypress, &data);
	mlx_hook(data.win, 3, 1L<<1, handle_keyrelease, &data);
	mlx_hook(data.win, 17, 0, handle_resize, &data);
	mlx_loop(data.mlx);
}

*/
