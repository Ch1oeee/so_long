/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:32:44 by cmontaig          #+#    #+#             */
/*   Updated: 2025/01/27 14:22:53 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	pixel_square(t_data *img)
{
	int	square_size = 100;
	int	x_start = 50;
	int	y_start = 50;
	int	y;
	int	x;

	y = y_start;
	while(y < y_start + square_size)
	{
		x = x_start;
		while(x < x_start + square_size)
		{
			my_mlx_pixel_put(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	
}


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_vars	vars;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 500, "Mims Land");
	img.img = mlx_new_image(mlx, 1000, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	pixel_square(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
