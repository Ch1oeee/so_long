/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:53:44 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/19 16:34:00 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../so_long.h"

//redo all the general parsing here, so_long_bonus

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	ft_memset(&game, 0, sizeof(t_game));
	if (!read_map(&game, argv))
		error_map("Invalid map", &game);
	if (count_ennemi(&game) > 0)
		read_map_bonus(&game, argv);
	game.mlx = mlx_init();
	if (!game.mlx)
		error_map("Mlx fail", &game);
	if (!game.map.grid)
		error_map("Can't print map", &game);
	game.win = mlx_new_window(game.mlx, game.map.width * 32,
			game.map.height * 32, "Mims Land");
	if (!game.win)
		error_map("Can't creat window", &game);
	draw_textures(&game);
	draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, key_handler, &game);
	mlx_hook(game.win, 17, 1L << 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}

void	ennemi_placement(t_game	*game, char *line, int i)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'B')
		{
			game->bonus.ennemi_x = x;
			game->bonus.ennemi_y = i;
		}
	}
}

int	count_ennemi(t_game *game)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while(y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'B')
				count++;
			x++;
		}
		y++;
	}
	game->bonus.nb_ennemi = count;
	return(count);
}

void	verify_ennemi(t_game *game)
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
			if (grid[i][j] == 'B')
				error_map("Not all ennemis are accessible", game);
			j++;
		}
		i++;
	}
}

void	parsing_bonus(t_game *game)
{
	flood_fill(game, 'F', game->map.player_y, game->map.player_x);
	verify_ennemi(game);
	free_grid_cpy(game->map.grid_cpy, game->map.height);
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
	parsing_bonus(game);
	printf("%d\n", game->bonus.nb_ennemi);
	return (1);
}