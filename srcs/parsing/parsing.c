/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:32:44 by cmontaig          #+#    #+#             */
/*   Updated: 2025/01/31 11:17:01 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// int	main(int argc, char **argv)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_game	img;
// 	t_map	map;

// 	if (argc != 2)
// 	{
// 		printf("Usage: ./so_long <map_file>\n");
// 		return (1);
// 	}
// 	read_map(&map, argv);
// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, map.map_x * 32, map.map_y * 32, "Mims Land");
// 	img.img = mlx_new_image(mlx, map.map_x * 32, map.map_y * 32);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 								&img.endian);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// 	return (0);
// }


int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_game	img;
	t_map	map;

	if (argc != 2)
	{
		printf("Usage: ./so_long <map_file>\n");
		return (1);
	}
	mlx = mlx_init();
	read_map(&map, argv);
	mlx_win = mlx_new_window(mlx, 1000, 500, "Mims Land");
	img.img = mlx_new_image(mlx, 1000, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

