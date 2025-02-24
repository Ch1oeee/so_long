/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_ennemi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:09:47 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/24 14:38:12 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minilibx-linux/mlx.h"
#include "../../so_long.h"

void	load_ennemi_sprites(t_game *game)
{
	game->bonus.ennemi_death[0] = mlx_xpm_file_to_image(game->mlx,
		"assets/bonus_assets/ennemi_death/b_death1.xpm",
		&game->textures.img_width, &game->textures.img_height);
	game->bonus.ennemi_death[1] = mlx_xpm_file_to_image(game->mlx,
		"assets/bonus_assets/ennemi_death/b_death2.xpm",
		&game->textures.img_width, &game->textures.img_height);
	game->bonus.ennemi_death[2] = mlx_xpm_file_to_image(game->mlx,
		"assets/bonus_assets/ennemi_death/b_death3.xpm",
		&game->textures.img_width, &game->textures.img_height);
	if (!game->bonus.ennemi_death[0] || !game->bonus.ennemi_death[1] ||
		!game->bonus.ennemi_death[2])
		ft_printf("textures not loaded"), exit(1);
	game->bonus.ennemi_frame = 0;
	game->bonus.ennemi_dead = 0;
}

int	animate_death_ennemi(t_game *game)
{
	static int frame_delay;

	if (frame_delay == 0)
		frame_delay = 0;
	if (game->bonus.ennemi_frame < 3)
	{
		frame_delay++;
		if (frame_delay >= 15000)
		{
			mlx_clear_window(game->mlx, game->win);
			draw_map(game);
			mlx_put_image_to_window(game->mlx, game->win, 
				game->bonus.ennemi_death[game->bonus.ennemi_frame],
				game->bonus.ennemi_x * game->tile_size, 
				game->bonus.ennemi_y * game->tile_size);
			game->bonus.ennemi_frame++;
			frame_delay = 0;
		}
	}
	else
	{
		mlx_loop_hook(game->mlx, NULL, game);
		return (1);
	}
	return (0);
}

void start_death_animation_ennemi(t_game *game)
{
	if (game->bonus.ennemi_frame >= 3)
	{
		game->bonus.ennemi_frame = 0;
		game->map.grid[game->bonus.ennemi_y][game->bonus.ennemi_x] = 'X';
	}
	game->map.grid[game->bonus.ennemi_y][game->bonus.ennemi_x] = 'X';
	mlx_loop_hook(game->mlx, animate_death_ennemi, game);
}