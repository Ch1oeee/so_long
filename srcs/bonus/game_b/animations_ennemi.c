/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_ennemi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:09:47 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/27 16:32:04 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minilibx-linux/mlx.h"
#include "../../so_long.h"

void	ennemi_walking(t_game *game, int update_x, int update_y)
{
	game->map.grid[game->bonus.ennemi_y][game->bonus.ennemi_x] = '0';
	game->bonus.ennemi_x = update_x;
	game->bonus.ennemi_y = update_y;
	game->map.grid[update_y][update_x] = 'B';
	mlx_clear_window(game->mlx, game->win);
	draw_map(game);
}

void	ennemi_moves(t_game *game)
{
	int	update_x;
	int	update_y;

	update_x = game->bonus.ennemi_x;
	update_y = game->bonus.ennemi_y;
	if (handle_mov_ennemi(game, &update_x, &update_y))
	{
		if (game->map.grid[update_y][update_x] != '1' &&
			game->map.grid[update_y][update_x] != 'E' &&
			game->map.grid[update_y][update_x] != 'C' &&
			game->map.grid[update_y][update_x] != 'P')
			ennemi_walking(game, update_x, update_y);
	}
}

int	handle_mov_ennemi(t_game *game, int *update_x, int *update_y)
{
	if (game->player_moves % 5 == 0 && game->player_moves % 3 == 0)
	{
		(*update_y)++;
		game->bonus.ennemi_faces = 4;
		return (1);
	}
	else if (game->player_moves % 3 == 0)
	{
		(*update_y)--;
		game->bonus.ennemi_faces = 1;
		return (1);
	}
	else if (game->player_moves % 2 == 0)
	{
		(*update_x)--;
		game->bonus.ennemi_faces = 2;
		return (1);
	}
	else if (game->player_moves % 5 == 0)
	{
		(*update_x)++;
		game->bonus.ennemi_faces = 0;
		return (1);
	}
	return (0);
}

void	ennemi_walking_animation(t_game *game, int x, int y)
{
	if (game->bonus.ennemi_faces == 1)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bonus.ennemi_up,
			x * game->tile_size, y * game->tile_size);
	}
	if (game->bonus.ennemi_faces == 2)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bonus.ennemi_left,
			x * game->tile_size, y * game->tile_size);
	}
	if (game->bonus.ennemi_faces == 0)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->bonus.ennemi_textures,
			x * game->tile_size, y * game->tile_size);
	}
	if (game->bonus.ennemi_faces == 4)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bonus.ennemi_down,
			x * game->tile_size, y * game->tile_size);
	}
}
