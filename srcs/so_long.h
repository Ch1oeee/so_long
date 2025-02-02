/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:33 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/02 17:19:37 by cmontaig         ###   ########.fr       */
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

typedef struct	s_game {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_game;

typedef struct	s_map {
	int		map_y;
	int		map_x;
	char 	**grid;
	char	*path;
}				t_map;


void	my_mlx_pixel_put(t_game *data, int x, int y, int color);
void	error_map(char *str, t_map *map);
int		read_map(t_map *map, char **argv);
int		grid_length(char *str);
void		verify_letters(char	*line);
void	rectangle_map(t_map *map);
void	free_map(t_map *map);
int		grid_height(char *file);
void	missing_letters(t_map *map);
t_map	malloc_map(t_map *map, char **argv);

#endif