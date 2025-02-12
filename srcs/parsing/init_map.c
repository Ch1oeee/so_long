/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:21:08 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/12 11:41:26 by cmontaig         ###   ########.fr       */
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
	map->grid_cpy = ft_calloc(sizeof(char *), (line_count + 1));
	map->player_x = -1;
	map->player_y = -1;
	map->exit_x = -1;
	map->exit_y = -1;
	map->collectibles = 0;
	if (!map->grid || !map->grid_cpy)
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
		map->grid_cpy[i] = ft_strdup(line);
		assign_placement(map, line, i);
		verify_letters(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	map->grid_cpy[i] = NULL;
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
	game->player_moves = 0;
	allocate_map(&game->map, game->map.height);
	fill_map(&game->map, argv[1]);
	rectangle_map(&game->map);
	missing_letters(&game->map);
	verify_paths(game);
	return (1);
}

// 56 bytes in 1 blocks are still reachable in loss record 21 of 54
// ==85107==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==85107==    by 0x403EBD: ft_calloc (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85107==    by 0x403271: allocate_map (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85107==    by 0x403590: read_map (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85107==    by 0x40256F: main (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85107== 
// ==85107== 56 bytes in 1 blocks are still reachable in loss record 22 of 54
// ==85107==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==85107==    by 0x403EBD: ft_calloc (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85107==    by 0x40328F: allocate_map (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85107==    by 0x403590: read_map (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85107==    by 0x40256F: main (in /home/cmontaig/Documents/cursus/so_long/so_long)

// 102 bytes in 6 blocks are still reachable in loss record 25 of 54
// ==85820==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==85820==    by 0x40375C: ft_strdup (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85820==    by 0x4033B8: fill_map (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85820==    by 0x4035A5: read_map (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85820==    by 0x40256F: main (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85820== 
// ==85820== 102 bytes in 6 blocks are still reachable in loss record 26 of 54
// ==85820==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==85820==    by 0x40375C: ft_strdup (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85820==    by 0x4033D4: fill_map (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85820==    by 0x4035A5: read_map (in /home/cmontaig/Documents/cursus/so_long/so_long)
// ==85820==    by 0x40256F: main (in /home/cmontaig/Documents/cursus/so_long/so_long)
