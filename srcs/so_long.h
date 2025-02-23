/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:33 by cmontaig          #+#    #+#             */
/*   Updated: 2025/02/23 20:31:07 by cmontaig         ###   ########.fr       */
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

typedef struct s_map
{
	int		height;
	int		width;
	char	**grid;
	char	**grid_cpy;
	char	*path;
	int		player_y;
	int		player_x;
	int		exit_y;
	int		exit_x;
	int		collectibles;
}				t_map;

typedef struct s_textures
{
	void	*grass;
	void	*wall;
	void	*player;
	void	*exit;
	void	*collectible;
	int		img_width;
	int		img_height;
}			t_textures;

typedef struct s_bonus
{
	int		ennemi_y;
	int		ennemi_x;
	void	*ennemi_textures;
	int		nb_ennemi;
	void	*death_sprites[5];
	int		death_frame;
}				t_bonus;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			player_moves;
	int			tile_size;
	t_map		map;
	t_textures	textures;
	t_bonus		bonus;
}				t_game;


int		key_handler(int keycode, t_game *game);
int		close_window(t_game *game);
void	draw_textures(t_game *game);
void	draw_map(t_game *game);
void	draw_tile(t_game *game, int x, int y, char tile);

//PARSING
void	process_map_line(t_game *game, char *line, int i);
void	fill_map(t_game *game, char *file);
void	error_map(char *str, t_game *game);
int		read_map(t_game *game, char **argv);
int		grid_length(char *str);
void	verify_letters(char	*line, t_game *game);
void	rectangle_map(t_game *game);
void	free_map(t_game *game);
int		grid_height(char *file);
void	missing_letters(t_game *game);
void	assign_placement(t_game *game, char *line, int i);
void	verify_exit(t_game *game);
void	verify_paths(t_game *game);
void	flood_fill(t_game *game, char fill, int y, int x);
void	verify_collectibles(t_game *game);
void	free_grid_cpy(char **grid_cpy, int height);
void	free_img(t_game *game);
void	allocate_map(t_game *game, int line_count);

//GAME 
void	handle_movement(int keycode, int *new_x, int *new_y);
void	update_position(t_game *game, int new_x, int new_y);
void	character_moves(int keycode, t_game *game);
void	open_exit(t_game *game);

//BONUS
void	verify_ennemi(t_game *game);
int		read_map_bonus(t_game *game, char **argv);
void	verify_letters_b(char	*line, t_game *game);
void	handle_exit_tile(t_game *game, int x, int y);
void	draw_basic_tiles(t_game *game, int x, int y, char tile);
void	character_moves_b(int keycode, t_game *game);
void	open_exit_b(t_game *game);
void	display_moves(t_game *game);
int		animate_death(t_game *game);
void	free_death_sprites(t_game *game);
void	start_death_animation(t_game *game);
void	load_death_sprites(t_game *game);

#endif