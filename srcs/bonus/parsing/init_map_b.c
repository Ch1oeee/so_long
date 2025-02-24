/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:03:59 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/23 21:11:01 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minilibx-linux/mlx.h"
#include "../../so_long.h" 
#include "../../../Libraries/gnl/get_next_line.h"
#include "../../../Libraries/libft/libft.h"

void	allocate_map(t_game *game, int line_count)
{
	game->map.grid = ft_calloc(sizeof(char *), (line_count + 1));
	game->map.grid_cpy = ft_calloc(sizeof(char *), (line_count + 1));
	game->map.collectibles = 0;
	if (!game->map.grid || !game->map.grid_cpy)
		error_map("Malloc failed", game);
}

void	process_map_line(t_game *game, char *line, int i)
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
	verify_letters_b(line, game);
}

void	fill_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_map("Map not found", game);
	line = get_next_line(fd, 0);
	if (!line)
	{
		close(fd);
		error_map("Empty map file", game);
	}
	i = 0;
	while (line)
	{
		process_map_line(game, line, i);
		free(line);
		i++;
		line = get_next_line(fd, 0);
	}
	game->map.grid[i] = NULL;
	game->map.grid_cpy[i] = NULL;
	close(fd);
}

void	assign_placement(t_game *game, char *line, int i)
{
	int	x;

	x = 0;
	while (line[x])
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
		else if (line[x] == 'B')
		{
			game->bonus.ennemi_x = x;
			game->bonus.ennemi_y = i;
			game->bonus.nb_ennemi++;
		}
		x++;
	}
}

int	read_map_bonus(t_game *game, char **argv)
{
	game->map.height = grid_height(argv[1]);
	if (game->map.height == 0)
		error_map("Empty map", game);
	game->map.width = 0;
	game->player_moves = 0;
	allocate_map(game, game->map.height);
	fill_map(game, argv[1]);
	verify_paths(game);
	return (1);
}
