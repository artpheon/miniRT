//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

int intersect_sp(t_ray ray, t_object *obj)
{
	t_vector sp_to_ray;
	float b;
	float c;
	float discriminant;
	float dist;

	sp_to_ray = vector_sub(ray.origin, obj->origin_coord);
	b = 2 * scalar_prod(ray.direction, sp_to_ray);
	c = scalar_prod(sp_to_ray, sp_to_ray) - ((obj->sphere_diam / 2) * (obj->sphere_diam / 2));
	discriminant = (b * b) - (4 * c);
	if (discriminant >= 0)
	{
		dist = ((b * -1) - sqrtf(discriminant)) / 2;
		if (dist > 0)
			return (1);
	}
	return (0);
}

t_vector get_sp_plane(float width, float height, t_camera *cam)
{
	t_vector new;
	float vp_width;
	float vp_height;
	float aspect_ratio;

	aspect_ratio = width / height;
	vp_width = tan(M_PI * 0.5 * cam->fov / 180.) * 2;
	vp_height = vp_width / aspect_ratio;
	new.x = vp_width / width;
	new.y = vp_height / height;
	new.z = -1;
	return (new);
}

void trace_ray(void *mlx, void *window, t_config *config)
{
	int canvas_x;
	int canvas_y;
	float vp_x;
	float vp_y;
	int colour;
	t_ray ray;
	t_vector plane;

	plane = get_sp_plane(config->res.width, config->res.height, config->camera->content);
	canvas_y = 0;
	vp_y = (config->res.height) / 2;
	while (vp_y >= (config->res.height) / 2 * (-1))
	{
		vp_x = (config->res.width) / 2 * (-1);
		canvas_x = 0;
		while (vp_x <= config->res.width / 2)
		{
			ray = set_ray(((t_camera *)(config->camera->content))->origin_coord,
			set_nvector(plane.x * vp_x, plane.y * vp_y, -1));
			if (intersect_sp(ray, config->object->next->content))
				colour = ctohex(((t_object *)(config->object->next->content))->rgb);
			else
				colour = 0x202020;
			mlx_pixel_put(mlx, window, canvas_x, canvas_y, colour);
			vp_x++;
			canvas_x++;
		}
		vp_y--;
		canvas_y++;
	}
}