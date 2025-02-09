/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:32:44 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/09 16:07:04 by cmontaig         ###   ########.fr       */
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


int	main(int argc, char **argv)
{
	t_game	img;
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: ./so_long <map_file>\n");
		return (1);
	}
	game.mlx = mlx_init();
	read_map(&game, argv);
	game.win = mlx_new_window(game.mlx, 1000, 500, "Mims Land");
	img.img = mlx_new_image(game.mlx, 1000, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(game.mlx, game.win, img.img, 0, 0);
	
	mlx_hook(game.win, 2, 1L << 0, key_handler, &game);
	mlx_hook(game.win, 17, 1L << 0, close_window, &game);
	
	mlx_loop(game.mlx);
}

int	key_handler(int keycode, t_game *game)
{
	if (keycode == 119) //W
		printf("up\n");
	else if (keycode == 97) //A
		printf("left\n");
	else if (keycode == 115) //S
		printf("down\n");
	else if (keycode == 100) //D
		printf("right\n");
	else if (keycode == 65307) //ESC
	{
		mlx_destroy_window(game->mlx, game->win);
		printf("escape\n");
		exit(0);
	}
	else
		printf("%d\n", keycode);
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	printf("window closed\n");
	exit(0);
	return (0);
}
