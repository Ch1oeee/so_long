/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:17:17 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/23 15:19:58 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"

void	draw_textures(t_game *game)
{
	game->tile_size = 32;
	game->textures.img_height = 32;
	game->textures.img_width = 32;
	game->textures.wall = mlx_xpm_file_to_image(game->mlx,
			"assets/Tree.xpm", &game->textures.img_width,
			&game->textures.img_height);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"assets/chick.xpm", &game->textures.img_width,
			&game->textures.img_height);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx,
			"assets/closed_log.xpm", &game->textures.img_width,
			&game->textures.img_height);
	game->textures.grass = mlx_xpm_file_to_image(game->mlx,
			"assets/Grass.xpm", &game->textures.img_width,
			&game->textures.img_height);
	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"assets/Mako.xpm", &game->textures.img_width,
			&game->textures.img_height);
	if (!game->textures.grass || !game->textures.wall || !game->textures.player
		|| !game->textures.exit || !game->textures.collectible)
	{
		ft_printf("textures not loaded");
		exit(1);
	}
}

void	draw_tile(t_game *game, int x, int y, char tile)
{
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->textures.wall,
			x * game->tile_size, y * game->tile_size);
	else if (tile == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->textures.grass,
			x * game->tile_size, y * game->tile_size);
	else if (tile == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->textures.player,
			x * game->tile_size, y * game->tile_size);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->textures.collectible,
			x * game->tile_size, y * game->tile_size);
	else if (tile == 'E')
	{
		if (game->map.collectibles == 0)
		{
			mlx_destroy_image(game->mlx, game->textures.exit);
			game->textures.exit = mlx_xpm_file_to_image(game->mlx,
					"assets/exit_log.xpm", &game->textures.img_width,
					&game->textures.img_height);
		}
		mlx_put_image_to_window(game->mlx, game->win, game->textures.exit,
			x * game->tile_size, y * game->tile_size);
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			draw_tile(game, x, y, game->map.grid[y][x]);
			x++;
		}
		y++;
	}
}
