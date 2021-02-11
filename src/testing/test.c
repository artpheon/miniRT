//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"
void print_config(t_config *conf)
{
	for (int i = 0; i < 60; i++)
	{
		printf("_");
		if (i == 59)
			printf("\n");
	}
	printf("Resolution: %d x %d\n",
		   conf->res.height,
		   conf->res.width);
	printf("Ambient: ratio - %f, rgb: %.0f %.0f %.0f\n",
		   conf->ambl.ratio,
		   conf->ambl.colour.x,
		   conf->ambl.colour.y,
		   conf->ambl.colour.z);
	for (int i = 0; i < 60; i++)
	{
		printf("_");
		if (i == 59)
			printf("\n");
	}
	printf("CAMERAS:\n");
	for (int i = 1; conf->camera->next != NULL; i++)
	{
		printf("Original XYZ coordinates of the camera #%d: %.2f, %.2f, %.2f\n",
			   i,
			   ((t_camera *) (conf->camera->content))->origin_coord.x,
			   ((t_camera *) (conf->camera->content))->origin_coord.y,
			   ((t_camera *) (conf->camera->content))->origin_coord.z);
		printf("Normalized XYZ vectors of the camera #%d: %.2f, %.2f, %.2f\n",
			   i,
			   ((t_camera *) (conf->camera->content))->vector_norm.x,
			   ((t_camera *) (conf->camera->content))->vector_norm.y,
			   ((t_camera *) (conf->camera->content))->vector_norm.z);
		printf("FOV of the camera #%d: %d\n\n",
			   i,
			   ((t_camera *) (conf->camera->content))->fov);
		conf->camera = conf->camera->next;
	}
	for (int i = 0; i < 60; i++)
	{
		printf("_");
		if (i == 59)
			printf("\n");
	}
	printf("LIGHTINGS:\n");
	for (int i = 1;; i++)
	{
		printf("Original XYZ of the lighting #%d: %.2f, %.2f, %.2f\n",
			   i,
			   ((t_light *) (conf->light->content))->origin_coord.x,
			   ((t_light *) (conf->light->content))->origin_coord.y,
			   ((t_light *) (conf->light->content))->origin_coord.z);
		printf("Ratio of the camera #%d: %f\n",
			   i,
			   ((t_light *) (conf->light->content))->ratio);
		printf("RGB of the lighting #%d: %.0f, %.0f, %.0f\n\n",
			   i,
			   ((t_light *) (conf->light->content))->rgb.x,
			   ((t_light *) (conf->light->content))->rgb.y,
			   ((t_light *) (conf->light->content))->rgb.z);
		if (conf->light->next == NULL)
			break;
		conf->light = conf->light->next;
	}
	for (int i = 0; i < 60; i++)
	{
		printf("_");
		if (i == 59)
			printf("\n");
	}

	for (int i = 1;; i++)
	{
		if (0 == ft_strncmp(((t_object *) (conf->object->content))->type,
							"sp", 2))
		{
			printf("SPHERE:\nOriginal XYZ coordinates: %.2f, %.2f, %.2f\n"
				   "Sphere diameter: %.3f\n"
				   "Sphere RGB colour: %.0f, %.0f, %.0f\n\n",
				   ((t_object *) (conf->object->content))->origin_coord.x,
				   ((t_object *) (conf->object->content))->origin_coord.y,
				   ((t_object *) (conf->object->content))->origin_coord.z,
				   ((t_object *) (conf->object->content))->sphere_diam,
				   ((t_object *) (conf->object->content))->rgb.x,
				   ((t_object *) (conf->object->content))->rgb.y,
				   ((t_object *) (conf->object->content))->rgb.z);
		}
		if (0 == ft_strncmp(((t_object *) (conf->object->content))->type,
							"pl", 2))
		{
			printf("PLANE:\nOriginal XYZ coordinates: %.2f, %.2f, %.2f\n"
				   "Normalized vector: %.2f %.2f %.2f\n"
				   "Plane RGB colour: %.0f, %.0f, %.0f\n\n",
				   ((t_object *) (conf->object->content))->origin_coord.x,
				   ((t_object *) (conf->object->content))->origin_coord.y,
				   ((t_object *) (conf->object->content))->origin_coord.z,
				   ((t_object *) (conf->object->content))->vector_norm.x,
				   ((t_object *) (conf->object->content))->vector_norm.y,
				   ((t_object *) (conf->object->content))->vector_norm.z,
				   ((t_object *) (conf->object->content))->rgb.x,
				   ((t_object *) (conf->object->content))->rgb.y,
				   ((t_object *) (conf->object->content))->rgb.z);
		}
		if (0 == ft_strncmp(((t_object *) (conf->object->content))->type,
							"sq", 2))
		{
			printf("SQUARE:\nSquare centre XYZ coordinates: %.2f, %.2f, %.2f\n"
				   "Normalized vector: %.2f %.2f %.2f\n"
				   "Side size: %.3f\n"
				   "Plane RGB colour: %.0f, %.0f, %.0f\n\n",
				   ((t_object *) (conf->object->content))->origin_coord.x,
				   ((t_object *) (conf->object->content))->origin_coord.y,
				   ((t_object *) (conf->object->content))->origin_coord.z,
				   ((t_object *) (conf->object->content))->vector_norm.x,
				   ((t_object *) (conf->object->content))->vector_norm.y,
				   ((t_object *) (conf->object->content))->vector_norm.z,
				   ((t_object *) (conf->object->content))->side_size,
				   ((t_object *) (conf->object->content))->rgb.x,
				   ((t_object *) (conf->object->content))->rgb.y,
				   ((t_object *) (conf->object->content))->rgb.z);
		}
		if (0 == ft_strncmp(((t_object *) (conf->object->content))->type,
							"cy", 2))
		{
			printf("CYLINDER:\nOriginal XYZ coordinates: %.2f, %.2f, %.2f\n"
				   "Normalized vector: %.2f %.2f %.2f\n"
				   "Cylinder diameter: %.3f\n"
				   "Cylinder height: %.3f\n"
				   "RGB colour: %.0f, %.0f, %.0f\n\n",
				   ((t_object *) (conf->object->content))->origin_coord.x,
				   ((t_object *) (conf->object->content))->origin_coord.y,
				   ((t_object *) (conf->object->content))->origin_coord.z,
				   ((t_object *) (conf->object->content))->vector_norm.x,
				   ((t_object *) (conf->object->content))->vector_norm.y,
				   ((t_object *) (conf->object->content))->vector_norm.z,
				   ((t_object *) (conf->object->content))->cyl_d,
				   ((t_object *) (conf->object->content))->cyl_h,
				   ((t_object *) (conf->object->content))->rgb.x,
				   ((t_object *) (conf->object->content))->rgb.y,
				   ((t_object *) (conf->object->content))->rgb.z);
		}
		if (0 == ft_strncmp(((t_object *) (conf->object->content))->type,
							"tr", 2))
		{
			printf("TRIANGLE:\n"
				   "original XYZ coordinates: %.2f, %.2f, %.2f\n"
				   "XYZ coordinates of 2nd point: %.2f %.2f %.2f\n"
				   "XYZ coordinates of 3rd point: %.2f %.2f %.2f\n"
				   "RGB colour: %.0f, %.0f, %.0f\n\n",
				   ((t_object *) (conf->object->content))->origin_coord.x,
				   ((t_object *) (conf->object->content))->origin_coord.y,
				   ((t_object *) (conf->object->content))->origin_coord.z,
				   ((t_object *) (conf->object->content))->trian2.x,
				   ((t_object *) (conf->object->content))->trian2.y,
				   ((t_object *) (conf->object->content))->trian2.z,
				   ((t_object *) (conf->object->content))->trian3.x,
				   ((t_object *) (conf->object->content))->trian3.y,
				   ((t_object *) (conf->object->content))->trian3.z,
				   ((t_object *) (conf->object->content))->rgb.x,
				   ((t_object *) (conf->object->content))->rgb.y,
				   ((t_object *) (conf->object->content))->rgb.z);
		}
		if (conf->object->next == NULL)
			break;
		conf->object = conf->object->next;
	}
}
void print_vector(t_vector v)
{
	for (int i = 0; i < 15; i++)
	{
		printf("_");
		if (i == 14)
			printf("\n");
	}
	printf("COORDINATES:\nX: %f Y: %f Z: %f\n", v.x, v.y, v.z);
	for (int i = 0; i < 15; i++)
	{
		printf("_");
		if (i == 14)
			printf("\n");
	}
}

int   key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
	}
	printf("key: %d\n", keycode);
	return (0);
}

void start_show(t_config *config)
{
	t_vars vars;

	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx, (int)(config->res.width), (int)(config->res.height), "TRY");
	mlx_key_hook(vars.win, key_hook, &vars);
	trace_ray(vars.mlx, vars.win, config);
	mlx_loop(vars.mlx);
}