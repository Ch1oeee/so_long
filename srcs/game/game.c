/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:50:46 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/28 14:35:47 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"

int	handle_movement(int keycode, int *new_x, int *new_y)
{
	if (keycode == 119)
	{
		(*new_y)--;
		return (1);
	}
	else if (keycode == 97)
	{
		(*new_x)--;
		return (1);
	}
	else if (keycode == 115)
	{
		(*new_y)++;
		return (1);
	}
	else if (keycode == 100)
	{
		(*new_x)++;
		return (1);
	}
	else
		return (0);
}

void	update_position(t_game *game, int new_x, int new_y)
{
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	if (game->map.grid[new_y][new_x] == 'C')
		game->map.collectibles--;
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	game->map.grid[new_y][new_x] = 'P';
	game->player_moves++;
	ft_printf("Mouvements: %d\n", game->player_moves);
	mlx_clear_window(game->mlx, game->win);
	draw_map(game);
}

void	character_moves(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_x;
	new_y = game->map.player_y;
	if (handle_movement(keycode, &new_x, &new_y))
	{
		if(game->map.collectibles == 0)
		{
			if (game->map.grid[new_y][new_x] != '1'
			&& game->map.grid[new_y][new_x] != 'E')
				update_position(game, new_x, new_y);
			else if (game->map.grid[new_y][new_x] == 'E' &&
			game->map.collectibles == 0)
				open_exit(game);
		}
		else if (game->map.grid[new_y][new_x] != '1')
			update_position(game, new_x, new_y);;
	}
}

void	open_exit(t_game *game)
{
	game->player_moves++;
	ft_printf("Mouvements: %d\n", game->player_moves);
	ft_printf("Congratulations, you've successfully escaped !\n");
	close_window(game);
}
