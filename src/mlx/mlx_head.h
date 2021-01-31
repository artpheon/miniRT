//
// Created by Howe Robbin on 1/28/21.
//

#ifndef MLX_HEAD_H
# define MLX_HEAD_H

# include "header.h"

typedef struct s_data
{
	void	*img;
	char 	*addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
}				t_data;

void 	my_mlx_pixel_put(t_data *data, int x, int y, int colour);
void	show_red_win();

#endif //MINIRT_MLX_H
