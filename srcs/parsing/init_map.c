/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:21:08 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/15 15:28:02 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h" 
#include "../../Libraries/gnl/get_next_line.h"
#include "../../Libraries/libft/libft.h"

void	free_map(t_game *game)
{
	int i;

	if (!game || !game->map.grid)
		return;

	i = 0;
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}


void	allocate_map(t_game *game, int line_count)
{
	game->map.grid = ft_calloc(sizeof(char *), (line_count + 1));
	game->map.grid_cpy = ft_calloc(sizeof(char *), (line_count + 1));
	game->map.collectibles = 0;
	if (!game->map.grid || !game->map.grid_cpy)
		error_map("Malloc failed", game);
}

void	fill_map(t_game *game, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_map("Map not found", game);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i == 0)
			game->map.width = grid_length(line);
		if (grid_length(line) != game->map.width)
		{
			free(line);
			error_map("Map lines not the same length", game);
		}
		game->map.grid[i] = ft_strdup(line);
		game->map.grid_cpy[i] = ft_strdup(line);
		assign_placement(game, line, i);
		verify_letters(line, game);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	game->map.grid[i] = NULL;
	game->map.grid_cpy[i] = NULL;
	close(fd);
}

void	assign_placement(t_game *game, char *line, int i)
{
	int	x;

	x = 0;
	while(line[x])
	{
		if (line[x] == 'P')
		{
			game->map.player_x = x;
			game->map.player_y = i;
		}
		else if (line[x] == 'E')
		{
			game->map.exit_x = x;
			game->map.exit_y = i;
		}
		else if (line[x] == 'C')
			game->map.collectibles++;
		x++;
	}
}

int	read_map(t_game *game, char **argv)
{	
	game->map.height = grid_height(argv[1]);
	if (game->map.height == 0)
		error_map("Empty map", game);
	game->map.width = 0;
	game->player_moves = 0;
	allocate_map(game, game->map.height);
	fill_map(game, argv[1]);
	rectangle_map(game);
	missing_letters(game);
	verify_paths(game);
	return (1);
}
