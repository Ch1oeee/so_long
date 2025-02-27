/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:44:15 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/27 13:35:08 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minilibx-linux/mlx.h"
#include "../../so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	ft_memset(&game, 0, sizeof(t_game));
	if (!read_map_bonus(&game, argv))
		error_map("Invalid map", &game);
	game.mlx = mlx_init();
	if (!game.mlx)
		error_map("Mlx fail", &game);
	if (!game.map.grid)
		error_map("Can't print map", &game);
	game.win = mlx_new_window(game.mlx, game.map.width * 32,
			game.map.height * 32, "Mims Land");
	if (!game.win)
		error_map("Can't creat window", &game);
	draw_textures(&game);
	load_death_sprites(&game);
	load_ennemi_sprites(&game);
	load_walking_sprites(&game);
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
		free_img(game);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		ft_printf("You closed the game\n");
		exit(0);
	}
	else
		character_moves_b(keycode, game);
	return (0);
}

int	close_window(t_game *game)
{
	free_grid_cpy(game->map.grid, game->map.height);
	free_img(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

void	free_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->textures.wall);
	mlx_destroy_image(game->mlx, game->textures.collectible);
	mlx_destroy_image(game->mlx, game->textures.exit);
	mlx_destroy_image(game->mlx, game->textures.grass);
	mlx_destroy_image(game->mlx, game->textures.player);
	mlx_destroy_image(game->mlx, game->bonus.player_down);
	mlx_destroy_image(game->mlx, game->bonus.player_up);
	mlx_destroy_image(game->mlx, game->bonus.player_left);
	mlx_destroy_image(game->mlx, game->bonus.ennemi_left);
	mlx_destroy_image(game->mlx, game->bonus.ennemi_up);
	mlx_destroy_image(game->mlx, game->bonus.ennemi_down);
	mlx_destroy_image(game->mlx, game->bonus.death_sprites[0]);
	mlx_destroy_image(game->mlx, game->bonus.death_sprites[1]);
	mlx_destroy_image(game->mlx, game->bonus.death_sprites[2]);
	mlx_destroy_image(game->mlx, game->bonus.death_sprites[3]);
	mlx_destroy_image(game->mlx, game->bonus.death_sprites[4]);
	mlx_destroy_image(game->mlx, game->bonus.ennemi_textures);
	mlx_destroy_image(game->mlx, game->bonus.ennemi_death[0]);
	mlx_destroy_image(game->mlx, game->bonus.ennemi_death[1]);
	mlx_destroy_image(game->mlx, game->bonus.ennemi_death[2]);
}

int	handle_movement_b(t_game *game, int keycode, int *new_x, int *new_y)
{
	if (keycode == 119)
	{
		(*new_y)--;
		game->bonus.walking = 1;
		return (1);
	}
	else if (keycode == 97)
	{
		(*new_x)--;
		game->bonus.walking = 2;
		return (1);
	}
	else if (keycode == 115)
	{
		(*new_y)++;
		game->bonus.walking = 3;
		return (1);
	}
	else if (keycode == 100)
	{
		(*new_x)++;
		game->bonus.walking = 0;
		return (1);
	}
	return (0);
}
