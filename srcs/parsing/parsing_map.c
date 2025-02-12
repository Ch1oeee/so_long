/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:40:04 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/12 11:53:11 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"
#include "../../Libraries/gnl/get_next_line.h"
#include "../../Libraries/libft/libft.h"

void	error_map(char *str, t_map *map)
{	
	printf("Error, %s\n", str);
	if (map)
		free(map);
	exit(1);
}

int	grid_length(char *str)
{
	int	i;
	// int x;
	// int	y = 0;
	// while (y < game.map.height)
	// {
	// 	x = 0;		
	// 	while (x < game.map.width)
	// 	{
	// 		printf("%c", game.map.grid[y][x]);
	// 		x++;
	// 	}
	// 	printf("\n");
	// 	y++;
	// }
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
	if (fd == -1)
		error_map("Map not found", NULL);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

void	verify_letters(char	*line)
{
	int	i;

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

	if (!map || !map->grid)
		error_map("Invalid map data", NULL);
	while (y < map->height)
	{
		x = 0;		
		while (x < map->width)
		{
			printf("%c", map->grid[y][x]);
			if (map->grid[y][x] == 'E')
				count_e++;
			if (map->grid[y][x] == 'P')
				count_p++;
			if (map->grid[y][x] == 'C')
				count_c++;
			x++;
		}
		printf("\n");
		y++;
	}
	printf("player %d, exit %d, collectible %d\n", count_p, count_e, count_c);
	if (count_e > 1 || count_p > 1)
		error_map("More than one player or exit", map);
	if (count_c == 0 || count_e == 0 || count_p == 0)
		error_map("Missing player, exit or collectibles", map);
}

void	rectangle_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->width)
	{
		if (map->grid[0][x] != '1'|| map->grid[map->height - 1][x] != '1')
			error_map("False border", map);
		x++;	
	}
	y = 0;
	while (y < map->height)
	{
		if (map->grid[y][0] != '1' || map->grid[y][map->width - 1] != '1')
			error_map("False border", map);
		y++;
	}
	if (map->width == map->height)
		error_map("Map is not a rectangle", map);
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

void	verify_paths(t_game *game)
{
	flood_fill(game, 'F', game->map.player_y, game->map.player_x);
	verify_exit(game);
	verify_collectibles(game);
	free_grid_cpy(game->map.grid_cpy, game->map.height);
}
// sert a rien ??????
void	free_grid_cpy(char **grid_cpy, int	height)
{
	int	i;
	if(!grid_cpy)
		return ;
	i = 0;
	while(i < height)
	{
		free(grid_cpy[i]);
		i++;
	}
	free(grid_cpy);
}

void	verify_exit(t_game *game)
{
	int 	i;
	int 	j;
	char	**grid;
	
	grid = game->map.grid_cpy;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (grid[i][j] == 'E')
				error_map("Exit not accessible", NULL);
			j++;
		}
		i++;
	}
}

void	verify_collectibles(t_game *game)
{
	int 	i;
	int 	j;
	char	**grid;

	grid = game->map.grid_cpy;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (grid[i][j] == 'C')
				error_map("Not all collectibles are accessible", NULL);
			j++;
		}
		i++;
	}
}
