/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoeferr < joseferr@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:25:43 by jsoeferr          #+#    #+#             */
/*   Updated: 2024/06/18 15:25:43 by jsoeferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
int	main(void)
{
	void	*mlxpointer;
	void	*mlxwindow;

	mlxpointer = mlx_init();
	mlxwindow = mlx_new_window(mlxpointer, 1280 , 720, "so_long");
}
