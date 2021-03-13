//
// Created by Howe Robbin on 1/20/21.
//

#ifndef HEADER_H
# define HEADER_H

# ifdef __linux__
	#  define OS "Linux"
	#  define ESC 65307
	#  define TAB 65289
	#  define M_PI 3.14159265358979323846
# elif __APPLE__
	#  define OS "Mac"
	#  define ESC 53
	#  define TAB 48
# endif
# define K_D 35
# define K_S 30
# define P 60
# define BG_COLOUR 0x48494B
# include "libft.h"

typedef struct	s_vector
{
	float x;
	float y;
	float z;
}				t_vector;

typedef struct 	s_object
{
	char 		type[3];
	t_vector	orig;
	t_vector	normal;
	t_vector	rgb;
	float 		sp_radius;
	float		side_size;
	float		cyl_d;
	float 		cyl_h;
	t_vector	angle2;
	t_vector	angle3;
}				t_object;

typedef struct 	s_camera
{
	t_vector	orig;
	t_vector	normal;
	int 		fov;
}				t_camera;

typedef struct	s_light
{
	t_vector	orig;
	float 		ratio;
	t_vector	rgb;
}				t_light;

typedef struct	s_ambient
{
	float		ratio;
	t_vector	colour;
}				t_ambient;

typedef struct	s_scene
{
	int				width;
	int				height;
	t_ambient		ambl;
	t_list			*camera;
	t_list			*light;
	t_list			*object;
}				t_scene;

typedef struct  s_ray
{
    t_vector    orig;
    t_vector    dir;
}               t_ray;

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "parser.h"
# include "mlx.h"
# include "geom.h"
# include "mlx_head.h"
# include "screenshot.h"
# include "calc_light.h"
# include "test.h"
# include "utils.h"


#endif //MINIRT_HEADER_H