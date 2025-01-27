#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../Libraries/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	pixel_square(t_data *img);



#endif