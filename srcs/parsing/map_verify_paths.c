/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:28:32 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/27 17:21:42 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"

void	verify_paths(t_game *game)
{
	flood_fill(game, 'F', game->map.player_y, game->map.player_x);
	verify_exit(game);
	verify_collectibles(game);
	free_grid_cpy(game->map.grid_cpy, game->map.height);
}

void	verify_exit(t_game *game)
{
	int		i;
	int		j;
	char	**grid;

	grid = game->map.grid_cpy;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (grid[i][j] == 'E')
				error_map("Exit not accessible", game);
			j++;
		}
		i++;
	}
}

void	verify_collectibles(t_game *game)
{
	int		i;
	int		j;
	char	**grid;

	grid = game->map.grid_cpy;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (grid[i][j] == 'C')
				error_map("Not all collectibles are accessible", game);
			j++;
		}
		i++;
	}
}
