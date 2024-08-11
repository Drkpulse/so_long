#include "game.h"

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
