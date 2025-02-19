/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:44 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/19 11:51:50 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"

void	free_map(t_game *game)
{
	int	i;

	if (!game || !game->map.grid)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

void	error_map(char *str, t_game *game)
{
	ft_printf("Error, %s\n", str);
	if (game)
	{
		if (game->map.grid)
			free_grid_cpy(game->map.grid, game->map.height);
		if (game->map.grid_cpy)
			free_grid_cpy(game->map.grid_cpy, game->map.height);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
	get_next_line(0, 1);
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
	if (fd == -1)
		error_map("Map not found", NULL);
	count = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd, 0);
	}
	free(line);
	close(fd);
	return (count);
}

void	free_grid_cpy(char **grid_cpy, int height)
{
	int	i;

	if (!grid_cpy)
		return ;
	i = 0;
	while (i < height)
	{
		free(grid_cpy[i]);
		i++;
	}
	free(grid_cpy);
}
