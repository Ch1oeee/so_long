/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:32:44 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/13 17:45:09 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"


int	main(int argc, char **argv)
{
	t_game	game;
	(void)argc;

	// if (argc != 2)
	// {
	// 	printf("Usage: ./so_long <map_file>\n");
	// 	return (1);
	// }
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		printf("mlx fail\n");
		exit(1);
	}
	read_map(&game, argv);
	if (!game.map.grid)
	{
		printf("Can't print map\n");
		exit(1);
	}
	game.win = mlx_new_window(game.mlx, game.map.width * 32, game.map.height * 32, "Mims Land");
	if (!game.win)
	{
		printf("Can't create window\n");
		exit(1);
	}
	draw_textures(&game);
	draw_map(&game);
	
	mlx_hook(game.win, 2, 1L << 0, key_handler, &game);
	mlx_hook(game.win, 17, 1L << 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	key_handler(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		free_grid_cpy(game->map.grid, game->map.height);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		printf("escape\n");
		exit(0);
	}
	else
		character_moves(keycode, game);
	return (0);
}


int	close_window(t_game *game)
{
	printf("window closed\n");
	free_grid_cpy(game->map.grid, game->map.height);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

void	draw_textures(t_game *game)
{
	int	img_height = 32;
	int	img_width = 32;
	
	game->textures.wall = mlx_xpm_file_to_image(game->mlx, "assets/Tree.xpm", &img_width, &img_height);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx, "assets/chick.xpm", &img_width, &img_height);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx, "assets/exit_log.xpm", &img_width, &img_height);
	game->textures.grass = mlx_xpm_file_to_image(game->mlx, "assets/Grass.xpm", &img_width, &img_height);
	game->textures.player = mlx_xpm_file_to_image(game->mlx, "assets/Mako.xpm", &img_width, &img_height);

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



