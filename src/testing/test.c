//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"
void print_scene(t_scene *conf)
{
	for (int i = 0; i < 60; i++)
	{
		printf("_");
		if (i == 59)
			printf("\n");
	}
	printf("Resolution: %d x %d\n",
		   conf->height,
		   conf->width);
	printf("Ambient ratio: %f, rgb: %.0f %.0f %.0f\n",
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
	for (int i = 1; conf->camera != NULL; i++)
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
	if (conf->light)
	{
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
	}

	for (int i = 1;; i++)
	{
		if (0 == ft_strncmp(((t_object *) (conf->object->content))->type,
							"sp", 2))
		{
			printf("SPHERE:\nOriginal XYZ coordinates: %.2f, %.2f, %.2f\n"
				   "Sphere radius: %.3f\n"
				   "Sphere RGB colour: %.0f, %.0f, %.0f\n\n",
				   ((t_object *) (conf->object->content))->origin_coord.x,
				   ((t_object *) (conf->object->content))->origin_coord.y,
				   ((t_object *) (conf->object->content))->origin_coord.z,
				   ((t_object *) (conf->object->content))->sp_radius,
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
				   ((t_object *) (conf->object->content))->angle2.x,
				   ((t_object *) (conf->object->content))->angle2.y,
				   ((t_object *) (conf->object->content))->angle2.z,
				   ((t_object *) (conf->object->content))->angle3.x,
				   ((t_object *) (conf->object->content))->angle3.y,
				   ((t_object *) (conf->object->content))->angle3.z,
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

