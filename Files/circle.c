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
			respawn_enemy(data);
			printf("Circle Health: %d\n", data->circle_health);
			if (data->circle_health <= 0)
			{
				printf("Game Over!\n Final Score: %d\n", data->score);
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
	srand(time(0));
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
