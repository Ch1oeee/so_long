/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:21:08 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/02 17:22:09 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h" 
#include "../../Libraries/gnl/get_next_line.h"

void	free_map(t_map *map)
{
	int i;

	if (!map->grid)
		return;
	i = 0;
	while (i < map->map_y)
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
		error_map("Malloc failed", NULL);
	else
		printf("Malloc okaay\n");
}

void	fill_map(t_map *map, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_map("Map not found", NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (grid_length(line) != map->map_x)
			error_map("Map lines not the same length", NULL);
		else
			printf("all lines are the same length\n");
		map->grid[i] = line;
		printf("grid fill %s\n", map->grid[i]);
		verify_letters(line);
		i++;
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	close(fd);
}

int	read_map(t_map *map, char **argv)
{
	map->map_y = grid_height(argv[1]);
	if (map->map_y == 0)
		error_map("Empty map", NULL);
	map->map_x = grid_length(get_next_line(open(argv[1], O_RDONLY)));
	printf("height %d, length %d\n", map->map_y, map->map_x);
	allocate_map(map, map->map_y);
	fill_map(map, argv[1]);
	missing_letters(map);
	rectangle_map(map);
	return (1);
}

t_map	malloc_map(t_map *map, char **argv)
{
	
}


// int	read_map(t_map *map, char **argv)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 		error_map("Map not found", map);\n
// 	line = get_next_line(fd);
// 	if (!line)
// 		error_map("Empty map", map);
// 	map->map_x = grid_length(line);
// 	map->map_y = 0;
// 	map->grid = malloc(sizeof(char *) * (map->map_y + 1));
// 	if (!map->grid)
// 		error_map("Malloc failed", map);
// 	i = 0;
// 	while (line)
// 	{
// 		if (grid_length(line) != map->map_x)
// 			error_map("Map lines not the same length", map);
// 		map->grid[i] = line;
// 		verify_letters(line);
// 		map->map_y++;
// 		i++;
// 		line = get_next_line(fd);
// 	}
// 	map->grid[i] = NULL;
// 	rectangle_map(map);
// 	printf("height %d\n, length %d\n", map->map_y, map->map_x);
// 	close(fd);
// 	return(1);
// }
