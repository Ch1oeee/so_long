/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:21:08 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/09 03:47:44 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h" 
#include "../../Libraries/gnl/get_next_line.h"
#include "../../Libraries/libft/libft.h"

void	free_map(t_map *map)
{
	int i;

	if (!map || !map->grid)
		return;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	allocate_map(t_map *map, int line_count)
{
	map->grid = ft_calloc(sizeof(char *), (line_count + 1));
	if (!map->grid)
		error_map("Malloc failed", map);
}

void	fill_map(t_map *map, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_map("Map not found", map);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i == 0)
			map->width = grid_length(line);
		if (grid_length(line) != map->width)
			error_map("Map lines not the same length", map);
		map->grid[i] = ft_strdup(line);
		assign_placement(map, line, i);
		verify_letters(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	close(fd);
}

void	assign_placement(t_map *map, char *line, int i)
{
	int	x;

	x = 0;
	while(line[x])
	{
		if (line[x] == 'P')
		{
			map->player_x = x;
			map->player_y = i;
		}
		else if (line[x] == 'E')
		{
			map->exit_x = x;
			map->exit_y = i;
		}
		else if (line[x] == 'C')
			map->collectibles++;
		x++;
	}
}

int	read_map(t_game *game, char **argv)
{	
	game->map.height = grid_height(argv[1]);
	if (game->map.height == 0)
		error_map("Empty map", NULL);
	game->map.width = 0;
	allocate_map(&game->map, game->map.height);
	fill_map(&game->map, argv[1]);
	rectangle_map(&game->map);
	missing_letters(&game->map);
	verify_paths(game);
	return (1);
}

