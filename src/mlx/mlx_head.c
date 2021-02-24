//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

int   key_hook(int keycode, t_info *info)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(info->mlx, info->win);
		exit(0);
	}
	printf("key: %d\n", keycode);
	return (0);
}

void start_show(t_info *info)
{
	t_scene *scene;

	scene = info->scene;
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, scene->width, scene->height, "miniRT");
	mlx_key_hook(info->win, key_hook, info);
	trace_ray(info);
	mlx_loop(info->mlx);
}

void intersect_sp(t_ray *ray, t_object *obj, t_roots *roots)
{
	t_vector sp_to_ray;
	float b;
	float c;
	float discriminant;
	float a;

	sp_to_ray = vector_sub(ray->orig, obj->origin_coord);
	a = dot_prod(ray->dir, ray->dir);
	b = 2 * dot_prod(ray->dir, sp_to_ray);
	c = dot_prod(sp_to_ray, sp_to_ray) - (obj->sp_radius * obj->sp_radius);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant >= 0)
	{
		roots->t1 = (-b + sqrtf(discriminant)) / 2;
		roots->t2 = (-b - sqrtf(discriminant)) / 2;
	}
	else
	{
		roots->t1 = INFINITY;
		roots->t2 = INFINITY;
	}
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

t_vector normal(t_vector hit_pos, t_object *sphere)
{
	t_vector new;

	new = vector_sub(hit_pos, sphere->origin_coord);
	new = norm_vector(new);
	return (new);
}

//int	colour_at(t_object *sphere, t_vector pos_hit, t_vector normal, t_scene *scene)
//{
//	t_vector to_cam;
//	t_vector colour = {0, 0, 0};
//	t_ray to_light;
//
//	//t_vector half_vector;
//	to_cam = vector_sub(((t_camera *)(scene->camera->content))->origin_coord, pos_hit);
//	colour = rgb_mult_n(sphere->rgb, scene->ambl.ratio); // еще цвет амбиент
//	to_light = set_ray(pos_hit, vector_sub(((t_light *)(scene->light->content))->origin_coord, pos_hit));
//	float i = K_D * ((t_light *)(scene->light->content))->ratio * maxx(dot_prod(normal, to_light.dir), 0);
//	colour = rgb_add(colour, rgb_mult_n(((t_light *)(scene->light->content))->rgb, i));
//	//colour += ctohex(sphere->rgb) * new.diff * maxx(dot_prod(normal, to_light.dir), 0);
//	//t_vector temp0 = v_mult_scal(sphere->rgb, maxx(dot_prod(normal, to_light.dir), 0));
//	//colour = rgb_add(colour, temp0);
//	//half_vector = norm_vector(vector_add(to_light.dir, to_cam));
//	//colour += ctohex(((t_light *)(scene->light->content))->rgb) * new.spec * maxx(dot_prod(normal, half_vector), 0) * 50;
//	//t_vector temp = v_mult_scal(((t_light *)(scene->light->content))->rgb, maxx(dot_prod(normal, half_vector), 0));
//	//colour = rgb_add(colour, temp);
//	return (ctohex(colour));
//}

float calc_lighting(t_scene *scene, t_hit *hit)
{
	float		i;
	t_list		*start;
	t_vector	light;
	float		nl_light;

	i = 0;
	start = scene->light;
	while (start)
	{
		light = vector_sub(((t_light *)(start->content))->origin_coord, hit->hit_pos);
		nl_light = dot_prod(hit->hit_normal, light);
		if (nl_light > 0)
		{
			i += ((t_light *)(start->content))->ratio * nl_light /
				 (vector_length(light) * vector_length(hit->hit_normal));
		}
		start = start->next;
	}
	return (i);
}

void get_hit_sp(t_hit *hit, t_object *sphere, float closest, t_ray *ray)
{
	hit->hit_dist = closest;
	hit->hit_pos = vector_add(ray->orig, v_mult_scal(ray->dir, hit->hit_dist));
	hit->hit_normal = normal(hit->hit_pos, sphere);
}

//void	closest_inter(t_closest *new, t_roots *roots, t_list *obj, t_range range)
//{
//
//}

int calc_colour(t_scene *scene, t_vector *plane, float vp_x, float vp_y)
{
	int			colour;
	float		light;
	t_ray		ray;
	t_list		*start;
	t_object	*closest_obj;
	float		closest_t;
	t_roots		roots;
	t_hit		new_hit;


	start = scene->object;
	closest_obj = NULL;
	closest_t = INFINITY;
	ray = set_ray(((t_camera *)(scene->camera->content))->origin_coord,
			   set_vector(plane->x * vp_x, plane->y * vp_y, -1));
	while (start)
	{
		if (0 == ft_strncmp(((t_object *)(start->content))->type, "sp", 2))
		{
			intersect_sp(&ray, start->content, &roots);
			if (roots.t1 >= 1 && roots.t1 < INFINITY && roots.t1 < closest_t)
			{
				closest_t = roots.t1;
				closest_obj = start->content;
			}
			if (roots.t2 >= 1 && roots.t2 < INFINITY && roots.t2 < closest_t)
			{
				closest_t = roots.t2;
				closest_obj = start->content;
			}
		}
		start = start->next;
	}
	if (closest_obj == NULL)
		colour = 0xDC143C;
	else
	{
		get_hit_sp(&new_hit, closest_obj, closest_t, &ray);
		light = calc_lighting(scene, &new_hit);
		colour = ctohex(rgb_mult_n(closest_obj->rgb, light));
	}
	return (colour);
}

void trace_ray(t_info *info)
{
	int canvas_x;
	int canvas_y;
	float vp_x;
	float vp_y;
	int colour;
	t_scene *scene;
	t_vector plane;

	scene = info->scene;
	plane = get_sp_plane(scene->width, scene->height, scene->camera->content);
	canvas_y = 0;
	vp_y = scene->height / 2;
	while (vp_y >= scene->height / 2 * (-1))
	{
		vp_x = scene->width / 2 * (-1);
		canvas_x = 0;
		while (vp_x <= scene->width / 2)
		{
			colour = calc_colour(scene, &plane, vp_x, vp_y);
			mlx_pixel_put(info->mlx, info->win, canvas_x, canvas_y, colour);
			vp_x++;
			canvas_x++;
		}
		vp_y--;
		canvas_y++;
	}
}