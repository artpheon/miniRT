//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

t_vplane	*get_new_plane(float width, float height, float fov)
{
	t_vplane *plane;
	float	asp_ratio;

	if (NULL == (plane = malloc(sizeof(t_vplane))))
		close_app("Could not allocate mem for view plane", -1);
	asp_ratio = width / height; 
	plane->width = tan(M_PI * 0.5 * fov / 180.);
	plane->width *= 2;
	plane->height = plane->width / asp_ratio;
	plane->x_pixel = plane->width / width;
	plane->y_pixel = plane->height / height;
	return (plane);
}

int sphere_inter(t_camera *cam, t_vector ray, t_object *obj)
{
	float b;
	float c;
	float discriminant;
	float dist_1;
	float dist_2;
	t_vector sp_cam;

	sp_cam = vector_sub(cam->origin_coord, obj->origin_coord);
	b = 2 * (scalar_prod(sp_cam, ray));	
	c = scalar_prod(sp_cam, sp_cam) - ((obj->sphere_diam / 2.) * (obj->sphere_diam / 2.));
	discriminant = (b * b) - (4 * c);
	if (discriminant < 0)
		return (0);
	dist_1 = ((b * (-1)) - sqrtf(discriminant)) / 2;
	dist_2 = ((b * (-1)) + sqrtf(discriminant)) / 2;
	if (dist_1 > 0)
		return (1);
	return (0);
}

void trace_ray(void *mlx, void *window, t_config *config)
{
    int mlx_x, mlx_y;
    float angle_x, angle_y;
	float x_ray, y_ray;
    int color;
	t_vector ray;
	t_vplane *new_plane;
	
	mlx_y = 0;
	new_plane = get_new_plane(config->res.width,
							  config->res.height,
							  ((t_camera *)(config->camera->content))->fov);
	angle_y = (config->res.height) / 2;
	while (angle_y >= (config->res.height / 2) * (-1))
	{
		y_ray = angle_y * new_plane->y_pixel;
		angle_x = (config->res.width / 2) * (-1);
		mlx_x = 0;
		while (angle_x <= (config->res.width / 2))
		{
			x_ray = angle_x * new_plane->x_pixel;
			ray = set_vector(x_ray, y_ray, -1);
			ray = norm_vector(ray);
			if (sphere_inter(config->camera->content, ray, config->object->next->content))
				color = 0xFFAAFF;
			else
				color = 0x000000;
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, color);
			angle_x++;
			mlx_x++;
		}
		angle_y--;
		mlx_y++;
	}
	free(new_plane);    
}