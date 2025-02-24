/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:37:43 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/24 12:23:11 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minilibx-linux/mlx.h"
#include "../../so_long.h"

void	load_death_sprites(t_game *game)
{
	game->bonus.death_sprites[0] = mlx_xpm_file_to_image(game->mlx,
		"assets/bonus_assets/player_death/death1.xpm",
		&game->textures.img_width, &game->textures.img_height);
	game->bonus.death_sprites[1] = mlx_xpm_file_to_image(game->mlx,
		"assets/bonus_assets/player_death/death2.xpm",
		&game->textures.img_width, &game->textures.img_height);
	game->bonus.death_sprites[2] = mlx_xpm_file_to_image(game->mlx,
		"assets/bonus_assets/player_death/death3.xpm",
		&game->textures.img_width, &game->textures.img_height);
	game->bonus.death_sprites[3] = mlx_xpm_file_to_image(game->mlx,
		"assets/bonus_assets/player_death/death4.xpm",
		&game->textures.img_width, &game->textures.img_height);
	game->bonus.death_sprites[4] = mlx_xpm_file_to_image(game->mlx,
		"assets/bonus_assets/player_death/death5.xpm",
		&game->textures.img_width, &game->textures.img_height);
	if (!game->bonus.death_sprites[0] || !game->bonus.death_sprites[1] ||
		!game->bonus.death_sprites[2] || !game->bonus.death_sprites[3] ||
		!game->bonus.death_sprites[4])
		ft_printf("textures not loaded"), exit(1);
	game->bonus.death_frame = 0;
}

int	animate_death(t_game *game)
{
	static int delay;

	if (delay == 0)
		delay = 0;
	if (game->bonus.death_frame < 5)
	{
		delay++;
		if (delay >= 15000)
		{
			mlx_clear_window(game->mlx, game->win);
			draw_map(game);
			mlx_put_image_to_window(game->mlx, game->win, 
				game->bonus.death_sprites[game->bonus.death_frame],
				game->map.player_x * game->tile_size, 
				game->map.player_y * game->tile_size);
			game->bonus.death_frame++;
			delay = 0;
		}
	}
	else
		close_window(game);
	return (0);
}

void start_death_animation(t_game *game)
{
	if (game->bonus.death_frame >= 5)
		game->bonus.death_frame = 0;
	mlx_hook(game->win, 2, 1L << 0, NULL, game);
	mlx_loop_hook(game->mlx, animate_death, game);
}




