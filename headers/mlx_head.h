//
// Created by Howe Robbin on 1/28/21.
//

#ifndef MLX_HEAD_H
# define MLX_HEAD_H

typedef struct s_data
{
	void	*img;
	char 	*addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
}				t_data;

typedef struct s_vplane
{
	float width;
	float height;
	float x_pixel;
	float y_pixel;
}				t_vplane;

typedef struct  s_vars {
    void    *mlx;
    void    *win;
}               t_vars;

typedef struct s_ray
{
	t_vector origin;
	t_vector direction;
}			   t_ray;

t_vplane	get_new_plane(float width, float height, float fov);
void	trace_ray(void *mlx, void *window, t_config *config);


#endif //MINIRT_MLX_H
