/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:33 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/11 14:16:30 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../Libraries/libft/libft.h"
# include "../Libraries/gnl/get_next_line.h"
# include "../Libraries/ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <math.h>

// typedef struct s_data
// {
// 	int	endian;
// 	char	*addr;
// 	void	img;
// };

typedef struct	s_map {
	int		height;
	int		width;
	char 	**grid;
	char	**grid_cpy;
	char	*path;
	int		player_y;
	int		player_x;
	int		exit_y;
	int		exit_x;
	int		collectibles;
}				t_map;

typedef struct s_textures {
	void	*grass;
	void	*wall;
	void	*player;
	void	*exit;
	void	*collectible;
	int		img_width;
	int		img_height;
}			t_textures;

typedef struct	s_game {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		player_moves;
	t_map	map;
	t_textures	textures;
}				t_game;


int		key_handler(int keycode, t_game *game);
int		close_window(t_game *game);
void	draw_textures(t_game *game);
void	draw_map(t_game *game);

//PARSING
void	my_mlx_pixel_put(t_game *data, int x, int y, int color);
void	error_map(char *str, t_map *map);
int		read_map(t_game *game, char **argv);
int		grid_length(char *str);
void	verify_letters(char	*line);
void	rectangle_map(t_map *map);
void	free_map(t_map *map);
int		grid_height(char *file);
void	missing_letters(t_map *map);
void	assign_placement(t_map *map, char *line, int i);
void	verify_exit(t_game *game);
void	verify_paths(t_game *game);
void	flood_fill(t_game *game, char fill, int y, int x);
void	verify_collectibles(t_game *game);

#endif