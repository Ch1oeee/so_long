/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:32:44 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/19 16:23:43 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	ft_memset(&game, 0, sizeof(t_game));
	if (!read_map(&game, argv))
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
	draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, key_handler, &game);
	mlx_hook(game.win, 17, 1L << 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}

//shouldn't get a winning text if the window is closed, should changed that
int	key_handler(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		free_grid_cpy(game->map.grid, game->map.height);
		free_img(game);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		ft_printf("Congratulations, you've successfully escaped !!\n");
		exit(0);
	}
	else
		character_moves(keycode, game);
	return (0);
}

//shouldn't get a winning text if the window is closed, should changed that
int	close_window(t_game *game)
{
	ft_printf("Congratulations, you've successfully escaped !!\n");
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
}
