//
// Created by Howe Robbin on 1/20/21.
//

#ifndef HEADER_H
# define HEADER_H

# ifdef __linux__
	#  define OS "Linux"
	#  define ESC 65307
# elif __APPLE__
	#  define OS "Mac"
	#  define ESC 53
# endif

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "parser.h"
# include "geom.h"
# include "mlx_head.h"
# include "test.h"
# include "utils.h"
# include "save.h"

typedef struct	s_vector
{
	float x;
	float y;
	float z;
}				t_vector;

typedef struct 	s_object
{
	char 		type[3];
	t_vector	origin_coord;
	t_vector	vector_norm;
	t_vector	rgb;
	float 		sphere_diam;
	float		side_size;
	float		cyl_d;
	float 		cyl_h;
	t_vector	trian2;
	t_vector	trian3;
}				t_object;

typedef struct 	s_camera
{
	t_vector	origin_coord;
	t_vector	vector_norm;
	char 		fov;
}				t_camera;

typedef struct	s_light
{
	t_vector	origin_coord;
	float 		ratio;
	t_vector	rgb;
}				t_light;

typedef struct	s_resolution
{
	int width;
	int height;
}				t_resolution;

typedef struct	s_ambient
{
	float		ratio;
	t_vector	colour;
}				t_ambient;

typedef struct	s_config
{
	t_resolution	res;
	t_ambient		ambl;
	t_list			*camera;
	t_list			*light;
	t_list			*object;
}				t_config;

#endif //MINIRT_HEADER_H