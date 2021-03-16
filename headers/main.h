/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:44:05 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:45:23 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef struct		s_object
{
	char			type[3];
	t_vector		orig;
	t_vector		normal;
	t_vector		rgb;
	float			sp_radius;
	float			side_size;
	float			cyl_d;
	float			cyl_h;
	t_vector		angle2;
	t_vector		angle3;
}					t_object;

typedef struct		s_camera
{
	t_vector		orig;
	t_vector		normal;
	int				fov;
}					t_camera;

typedef struct		s_light
{
	t_vector		orig;
	float			ratio;
	t_vector		rgb;
}					t_light;

typedef struct		s_ambient
{
	float			ratio;
	t_vector		colour;
}					t_ambient;

typedef struct		s_scene
{
	int				width;
	int				height;
	t_ambient		ambl;
	t_list			*camera;
	t_list			*light;
	t_list			*object;
}					t_scene;

typedef struct		s_ray
{
	t_vector		orig;
	t_vector		dir;
}					t_ray;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_info {
	t_data			*img;
	void			*mlx;
	void			*win;
	t_scene			*scene;
	int				cams;
	int				sshot;
}					t_info;

typedef struct		s_hit
{
	t_vector		hit_pos;
	t_vector		hit_normal;
	float			hit_dist;
}					t_hit;

typedef struct		s_closest
{
	float			cl_t;
	t_object		*cl_obj;
}					t_closest;

typedef struct		s_matrix
{
	double			d[4][4];
}					t_matrix;

typedef struct		s_range
{
	float			t_min;
	float			t_max;
}					t_range;
#endif
