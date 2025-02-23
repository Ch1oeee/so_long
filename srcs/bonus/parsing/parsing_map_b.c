/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:15:17 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/23 13:19:50 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minilibx-linux/mlx.h"
#include "../../so_long.h"
#include "../../../Libraries/gnl/get_next_line.h"
#include "../../../Libraries/libft/libft.h"

void	verify_letters_b(char	*line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'C' && line[i] != 'E'
			&& line[i] != 'P' && line[i] != 'B')
			error_map("Symbol not valid", game);
		i++;
	}
}

void	missing_letters(t_game *game)
{
	int	count[3];
	int	x;
	int	y;

	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.grid[y][x] == 'E')
				count[0]++;
			if (game->map.grid[y][x] == 'P')
				count[1]++;
			if (game->map.grid[y][x] == 'C')
				count[2]++;
		}
	}
	if (count[0] > 1 || count[1] > 1)
		error_map("More than one player or exit", game);
	if (count[2] == 0 || count[0] == 0 || count[1] == 0)
		error_map("Missing player, exit or collectibles", game);
}

void	rectangle_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map.width)
	{
		if (game->map.grid[0][x] != '1'
			|| game->map.grid[game->map.height - 1][x] != '1')
			error_map("False border", game);
		x++;
	}
	y = 0;
	while (y < game->map.height)
	{
		if (game->map.grid[y][0] != '1'
			|| game->map.grid[y][game->map.width - 1] != '1')
			error_map("False border", game);
		y++;
	}
	if (game->map.width == game->map.height)
		error_map("Map is not a rectangle", game);
}

void	flood_fill(t_game *game, char fill, int y, int x)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return ;
	if (game->map.grid_cpy[y][x] == '1' || game->map.grid_cpy[y][x] == fill)
		return ;
	game->map.grid_cpy[y][x] = fill;
	flood_fill(game, fill, y, x - 1);
	flood_fill(game, fill, y, x + 1);
	flood_fill(game, fill, y - 1, x);
	flood_fill(game, fill, y + 1, x);
}
