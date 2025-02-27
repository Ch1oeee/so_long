/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mechanics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:57:41 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/27 13:49:48 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minilibx-linux/mlx.h"
#include "../../so_long.h"

void	update_position_b(t_game *game, int new_x, int new_y)
{
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	if (game->map.grid[new_y][new_x] == 'C')
		game->map.collectibles--;
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	game->map.grid[new_y][new_x] = 'P';
	game->player_moves++;
	if (game->map.grid[game->bonus.ennemi_y][game->bonus.ennemi_x] == 'B')
		ennemi_moves(game);
	ft_printf("Mouvements: %d\n", game->player_moves);
	mlx_clear_window(game->mlx, game->win);
	draw_map(game);
}

void	character_moves_b(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_x;
	new_y = game->map.player_y;
	if (!handle_movement_b(game, keycode, &new_x, &new_y))
		return ;
	if (game->map.grid[new_y][new_x] == 'B')
	{
		if (game->map.collectibles > 0)
			open_exit_b(game);
		else
		{
			game->bonus.nb_ennemi--;
			start_death_animation_ennemi(game);
		}
	}
	else if (game->map.grid[new_y][new_x] != '1'
		&& game->map.grid[new_y][new_x] != 'E'
		&& game->map.grid[new_y][new_x] != 'X')
		update_position_b(game, new_x, new_y);
	else if (game->map.grid[new_y][new_x] == 'E'
		&& game->map.collectibles == 0
		&& game->map.grid[game->bonus.ennemi_y][game->bonus.ennemi_x] == 'X')
		open_exit_b(game);
}

void	open_exit_b(t_game *game)
{
	game->player_moves++;
	ft_printf("Mouvements: %d\n", game->player_moves);
	if (game->map.collectibles > 0)
	{
		ft_printf("Game Over ! You died !\n");
		start_death_animation(game);
	}
	else
	{
		ft_printf("Congratulations, you've successfully escaped !\n");
		close_window(game);
	}
}

void	display_moves(t_game *game)
{
	char	*move_count;

	move_count = ft_itoa(game->player_moves);
	mlx_string_put(game->mlx, game->win, 10, 15, 0xFFFFFF, "Movements :");
	mlx_string_put(game->mlx, game->win, 80, 15, 0xFFFFFF, move_count);
	free(move_count);
}

void	walking_animation(t_game *game, int x, int y)
{
	if (game->bonus.walking == 1)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bonus.player_up,
			x * game->tile_size, y * game->tile_size);
	}
	else if (game->bonus.walking == 2)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bonus.player_left,
			x * game->tile_size, y * game->tile_size);
	}
	else if (game->bonus.walking == 3)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bonus.player_down,
			x * game->tile_size, y * game->tile_size);
	}
	else if (game->bonus.walking == 0)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->textures.player,
			x * game->tile_size, y * game->tile_size);
	}
}
