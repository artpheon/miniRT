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

t_vplane	get_new_plane(float width, float height, float fov);
void		intersect_sp(t_ray *ray, t_object *obj, t_roots *roots);
void		trace_ray(t_info *info);
void		start_show(t_info *info);
int			calc_colour(t_scene *scene, t_vector *plane, float vp_x, float vp_y);
int			key_hook(int keycode, t_info *info);


#endif //MINIRT_MLX_H
