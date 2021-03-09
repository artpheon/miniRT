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

typedef struct  s_info {
    t_data	*img;
    void    *mlx;
	void	*win;
	t_scene	*scene;
}               t_info;

typedef struct	s_hit
{
	t_vector	hit_pos;
	t_vector	hit_normal;
	float		hit_dist;
}				t_hit;

typedef struct s_closest
{
	float		closest_t;
	t_object	*closest_obj;
}				t_closest;

typedef struct s_range
{
	float t_min;
	float t_max;
}				t_range;

typedef struct	s_tr_vars
{
	t_vector	u;
	t_vector	v;
	t_vector	normal;
	float		dot_uu;
	float		dot_uv;
	float		dot_vv;
	float		calc_a;
	float		calc_d;
}				t_tr_vars;

typedef struct	s_cy_vars
{
	t_vector	cross;
	t_vector	sub;
	float		a;
	float		b;
	float		c;
	float		det;
	float 		t1;
	float 		t2;
}				t_cy_vars;

void		intersect_sp(t_ray *ray, t_object *obj, float *res, float t);
void		put_rays(t_scene *scene, void *mlx, void *win);
void		start_show(t_info *info);
int			calc_colour(t_scene *scene, t_vector *plane, float vp_x, float vp_y);
int			key_hook(int keycode, t_info *info);


#endif //MINIRT_MLX_H
