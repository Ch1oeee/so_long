/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:32:44 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/11 14:19:33 by cmontaig         ###   ########.fr       */
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
	// int x;
	// int	y = 0;
	// while (y < game.map.height)
	// {
	// 	x = 0;		
	// 	while (x < game.map.width)
	// 	{
	// 		printf("%c", game.map.grid[y][x]);
	// 		x++;
	// 	}
	// 	printf("\n");
	// 	y++;
	// }
	draw_textures(&game);
	draw_map(&game);
	game.win = mlx_new_window(game.mlx, game.map.width * 32, game.map.height * 32, "Mims Land");

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

void	draw_textures(t_game *game)
{
	// game->textures.img_height = 32;
	// game->textures.img_width = 32;

	int	img_height = 32;
	int	img_width = 32;
	
	game->textures.wall = mlx_xpm_file_to_image(game->mlx, "../../assets/Tree.xpm", &img_width, &img_height);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx, "../../assets/chick.xpm", &img_width, &img_height);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx, "../../assets/exit_log.xpm", &img_width, &img_height);
	game->textures.grass = mlx_xpm_file_to_image(game->mlx, "../../assets/Grass.xpm", &img_width, &img_height);
	game->textures.player = mlx_xpm_file_to_image(game->mlx, "../../assets/Mako.xpm", &img_width, &img_height);

	if (!game->textures.grass || !game->textures.wall || !game->textures.player || !game->textures.exit || !game->textures.collectible)
	{
		printf("textures not loaded");
		exit(1);
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	tile_size = 32;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->textures.wall, x * tile_size, y * tile_size);
			else if (game->map.grid[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->textures.grass, x * tile_size, y * tile_size);
			else if (game->map.grid[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->textures.player, x * tile_size, y * tile_size);
			else if (game->map.grid[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->textures.exit, x * tile_size, y * tile_size);
			else if (game->map.grid[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->textures.collectible, x * tile_size, y * tile_size);
			x++;
		}
		y++;
	}
}

