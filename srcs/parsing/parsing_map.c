/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:40:04 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/02 17:10:33 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"
#include "../../Libraries/gnl/get_next_line.h"

void	error_map(char *str, t_map *map)
{
	(void)map;
	
	printf("Error, %s\n", str);
	// free(map);
	exit(1);
}

int	grid_length(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	grid_height(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	printf("ouvert yeah\n");
	if (fd == -1)
		error_map("Map not found", NULL);
	count = 0;
	line = get_next_line(fd);
	printf("line okaaay\n");
	while (line)
	{
		line = get_next_line(fd);
		count++;
	}
	free(line);
	close(fd);
	return (count);
}

void	verify_letters(char	*line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0'&& line[i] != 'C' && line[i] != 'E'
			&& line[i] != 'P')
			error_map("Symbol not valid", NULL);
		i++;
	}	
}

void	missing_letters(t_map *map)
{
	int		count_e = 0;
	int		count_p = 0;
	int		count_c = 0;
	int		x;
	int		y = 0;

	// x = 0;
	while (y < map->map_y)
	{
		x = 0;
		printf("%c", map->grid[y][x]);
		
		while(x < map->map_x)
		{
			if (map->grid[y][x] == 'E')
				count_e++;
			if (map->grid[y][x] == 'P')
				count_p++;
			if (map->grid[y][x] == 'C')
				count_c++;
			x++;
			printf("%c", map->grid[y][x]);
		}
		printf("\n");
		y++;
	}
	printf("player %d, exit %d, collectible %d\n", count_p, count_e, count_c);
	if (count_e > 1 || count_p > 1)
		error_map("More than one player or exit", NULL);
	if (count_c == 0 || count_e == 0 || count_p == 0)
		error_map("Missing player, exit or collectibles", NULL);
	else
		printf("Symbols are okay");

}

// verifie si la map est rectangulaire et etoure de 1
void	rectangle_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->map_x)
	{
		if (map->grid[0][x] != '1'|| map->grid[map->map_y - 1][x] != '1')
			error_map("False border", NULL);
		x++;
	}
	y = 0;
	while (y < map->map_y)
	{
		if (map->grid[y][0] != '1' || map->grid[y][map->map_x - 1] != '1')
			error_map("False border", NULL);
		y++;
	}
	if (map->map_x == map->map_y)
		error_map("Map is not a rectangle", NULL);
}
