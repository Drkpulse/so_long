/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   janitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:52:04 by joseferr          #+#    #+#             */
/*   Updated: 2024/10/29 20:08:30 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	janitor(int error)
{
	const char	*messages[] = {
		"Invalid Arguments",
		"Invalid Map",
		"map_to_lst",
		"map_to_two_d",
		"map_size",
		"check_char",
		"surrounded",
		"count_char",
		"Failed to allocate memory for Enemies",
		"Failed to allocate memory for collectibles",
		"Memory allocation failed for visited.",
	};

	if (error >= 1 && error <= 11)
		printf("%s\n", messages[error - 1]);
	else
		printf("Unknown error\n");
	exit(EXIT_FAILURE);
}

void	free_wrong_map(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	janitor(2);
}

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_sprites(t_game *game, void **sprites, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (sprites[i])
		{
			mlx_destroy_image(game->mlx, sprites[i]);
			sprites[i] = NULL;
		}
		i++;
	}
}
