// game.h
#ifndef GAME_H
#define GAME_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include "libft/libft.h"
# include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define PIXEL 32
#define MOVE_SPEED 1
# define HEALTH 3
#define ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define ARROW_UP 65362
#define ARROW_LEFT 65361
#define ARROW_DOWN 65364
#define ARROW_RIGHT 65363
#define DEBUG 1

typedef struct s_img
{
	void	*mlx_img;
	int		*data;
	int		columns;
	int		rows;
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
	int		direction;
	int		attack;
	int		current_sprite;
	int		move_sprite_index;
	int		portal_sprite_index;
	void	*sprites[23];
}			t_player;

typedef struct s_enemy
{
	int		pos_x;
	int		pos_y;
	int		frame;
}			t_enemy;

typedef struct s_collectible
{
	int		pos_x;
	int		pos_y;
	int		frame;
	int		collected;
}				t_collectible;

typedef struct s_flood_fill
{
	char	**map;
	int		**visited;
	int		columns;
	int		rows;
}	t_flood_fill;

typedef struct s_map
{
	int				map_fd;
	t_list			*lst_map;
	char			**map;
	int				start_x;
	int				start_y;
	int				n_enemies;
	int				n_collectible;
	int				n_collected;
	t_collectible	**collectibles;
	void			*collectible_sprite[11];
	t_enemy			**enemies;
	void			*enemies_sprite[8];
	void			*window_sprite[11];
	int				n_portal;
	void			*portal_sprites[9];
	int				columns;
	int				rows
;
}					t_map;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				movements;
	long long		last_millitimestamp;
	int				fps;
	int				start;
	t_player		player;
	t_map			map;
	}				t_game;

/* Variables Start */
void	ft_startup(t_game *game);

/* Map Valiadation */
int		ft_validate_map(int argc, char **argv, t_game *game);
int	open_map(char *map_path, t_game *game);
int	map_to_lst(t_game *game);
int	map_to_two_d(t_game *game);
int	map_rectangle(t_game *game);
int	check_char(t_game *game);
int	surrounded(t_game *game);
int	count_char(t_game *game);
int	map_possible(t_game *game);

/* Window Management*/
void	ft_init_window(t_game *game, char *path);
void	hook_register(t_game *game);
int		close_window(t_game *game);

/* Sprite */
int	ft_init_sprite(t_game *game);
void	sprite_player_up(t_game *game, long long now);

/* Input */
int	handle_keypress(int key, t_game *game);
int	handle_keyrelease(int key, t_game *game);


/* Player*/
int		ft_init_player(t_game *game);
void	ft_player(t_game *game);
void	update_player_position(t_game *game, int next_x, int next_y);
void	ft_player(t_game *game);
void	calculate_next_position(t_game *game, int *next_x, int *next_y);
void	check_surroundings(t_game *game, int map_x1, int map_y1, int map_x2, int map_y2);
int		is_collision(t_game *game, int map_x1, int map_y1, int map_x2, int map_y2);
void	check_collectible(t_game *game, int map_x, int map_y);
void	check_exit(t_game *game, int map_x, int map_y);
void	check_enemy(t_game *game, int map_x, int map_y);

/* Collectible */
void	ft_collectible(t_game *game, long long now);
void	ft_collect(t_game *game, int x, int y);
void	ft_init_collectible(t_game *game);
t_collectible	*ft_create_collectible(int w, int h);

/* Enemies */
void	init_enemies(t_game *game);
void	ft_check_monsters(t_game *game);
void	default_enemy(t_enemy *enemy, int w, int h);
void	update_monsters(t_game *game, long long now);

/* Game Loop*/
int	game_loop(t_game *game);
void	ft_exit(t_game *game, long long now);
void	fill_map(void *mlx_pointer, void *mlx_window, t_map mapa);

/* Debug */
long long	millitimestamp(void);
void	show_fps(t_game *game);
void	fps(t_game *game);
void	show_steps(t_game *game);

/* Clean up*/
void	janitor(int error);
void	ft_leave(t_game *game);
void	free_list(t_list *head);
void	free_map(char **map, int rows);
void	free_sprites(t_game *game, void **sprites, int count);
void	free_collectibles(t_game *game);
void	free_enemies(t_game *game);

#endif
