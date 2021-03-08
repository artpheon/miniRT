//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

int key_hook(int keycode, t_info *info)
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
	put_rays(info->scene, info->mlx, info->win);
	mlx_loop(info->mlx);
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

t_vector sp_normal(t_vector hit_pos, t_object *sphere)
{
	t_vector new;

	new = vector_sub(hit_pos, sphere->origin_coord);
	normalize(&new);
	return (new);
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

void tr_solve_vars(t_tr_vars *new, t_object *o)
{
	new->u = vector_sub(o->angle2, o->origin_coord);
	new->v = vector_sub(o->angle3, o->origin_coord);
	new->dot_uu = dot_prod(new->u, new->u);
	new->dot_uv = dot_prod(new->u, new->v);
	new->dot_vv = dot_prod(new->v, new->v);
	new->calc_d = new->dot_uv *new->dot_uv - new->dot_uu *new->dot_vv;
}

int inter_as_pl(t_ray *ray, t_object *o, float *res)
{
	t_vector w;
	float a;
	float b;

	w = vector_sub(ray->orig, o->origin_coord); // t = dot(w,N)/dot(v,N)
	a = -dot_prod(w, o->vector_norm);
	b = dot_prod(ray->dir, o->vector_norm);
	if (fabs(b) < macheps())
	{
		*res = INFINITY;
		return (0);
	}
	if ((a / b) < 0)
	{
		*res = INFINITY;
		return (0);
	}
	*res = a / b;
	return (1);
}

void tr_solve(t_ray *r, t_object *o, t_tr_vars *p, float *res)
{
	t_vector point;
	t_vector w;
	float wu;
	float wv;
	float s;
	float t;

	point = vector_add(r->orig, v_mult_scal(r->dir, *res));
	w = vector_sub(point, o->origin_coord);
	wu = dot_prod(w, p->u);
	wv = dot_prod(w, p->v);
	s = (p->dot_uv * wv - p->dot_vv * wu) / p->calc_d;
	if (s < 0.0 || s > 1.0) // I is outside T
	{
		*res = INFINITY;
		return;
	}
	t = (p->dot_uv * wu - p->dot_uu * wv) / p->calc_d;
	if (t < 0.0 || (s + t) > 1.0) // I is outside T
		*res = INFINITY;
}

void intersect_tr(t_ray *ray, t_object *obj, float *res)
{
	t_tr_vars new;
	float t;

	tr_solve_vars(&new, obj);		  //считаем доп.параметры
	if (inter_as_pl(ray, obj, &t))	  //если пересекло плоскость в кот.лежит 3-уг
		tr_solve(ray, obj, &new, &t); //находим точку пересечения
	*res = t;
}

void intersect_pl(t_ray *ray, t_object *obj, float *res)
{
	float r;

	inter_as_pl(ray, obj, &r);
	*res = r;
}

void cl_inter(t_closest *cl, t_ray *ray, t_list *start, int shadow)
{
	t_roots roots;
	float resol;
	t_list *temp;
	t_range range;

	cl->closest_t = INFINITY;
	cl->closest_obj = NULL;
	if (shadow)
		range.t_min = 0.0015;
	else
		range.t_min = 0;
	range.t_max = INFINITY;
	temp = start;
	while (temp)
	{
		if (typecmp("sp", temp->content))
		{
			intersect_sp(ray, temp->content, &roots);
			if (shadow)
				range.t_max = 1;
			if (roots.t1 >= range.t_min && roots.t1 < range.t_max &&
				roots.t1 < cl->closest_t)
			{
				cl->closest_t = roots.t1;
				cl->closest_obj = temp->content;
			}
			if (roots.t2 >= range.t_min && roots.t2 < range.t_max &&
				roots.t2 < cl->closest_t)
			{
				cl->closest_t = roots.t2;
				cl->closest_obj = temp->content;
			}
		}
		if (typecmp("tr", temp->content))
		{
			intersect_tr(ray, temp->content, &resol);
			if (resol >= range.t_min && resol < cl->closest_t && resol < range.t_max)
			{
				cl->closest_t = resol;
				cl->closest_obj = temp->content;
			}
		}
		if (typecmp("pl", temp->content))
		{
			if (shadow)
				range.t_max = 1;
			intersect_pl(ray, temp->content, &resol);
			if (resol >= range.t_min && resol < cl->closest_t && resol < range.t_max)
			{
				cl->closest_t = resol;
				cl->closest_obj = temp->content;
			}
		}
		if (typecmp("sq", temp->content))
		{
			intersect_sq(ray, temp->content, &resol);
			if (resol >= range.t_min && resol < cl->closest_t && resol < range.t_max)
			{
				cl->closest_t = resol;
				cl->closest_obj = temp->content;
			}
		}
		temp = temp->next;
	}
}

void get_hit_sp(t_hit *hit, t_closest *cl, t_ray *ray)
{
	hit->hit_dist = cl->closest_t;
	hit->hit_pos = vector_add(ray->orig, v_mult_scal(ray->dir, hit->hit_dist));
	hit->hit_normal = sp_normal(hit->hit_pos, cl->closest_obj);
}

void get_hit_tr(t_hit *hit, t_closest *cl, t_ray *ray)
{
	hit->hit_dist = cl->closest_t;
	hit->hit_pos = vector_add(ray->orig, v_mult_scal(ray->dir, hit->hit_dist));
	hit->hit_normal = cl->closest_obj->vector_norm; // здесь всё ок
}
/*
int calc_colour(t_scene *scene, t_vector *plane, float vp_x, float vp_y)
{
	int			colour;
	float		light;
	t_ray		ray;
	t_list		*start;
	t_hit		hit;
	t_closest 	cl;
	t_range 	range;

	cl.closest_t = INFINITY;
	cl.closest_obj = NULL;
	start = scene->object;

	range.t_max = INFINITY;
	range.t_min = 1;
	cl_inter(&cl, &ray, start, &range);
	//if (0 == ft_strncmp(((t_object *)(start->content))->type, "sp", 2))
	//	;
	if (cl.closest_obj == NULL)
		colour = BG_COLOUR;
	else
	{
		get_hit_sp(&hit, &cl, &ray);
		//light = calc_lighting(scene, &new_hit, &ray);
		light = scene->ambl.ratio;
		colour = ctohex(rgb_mult_n(cl.closest_obj->rgb, light));
	}
	return (colour);
}*/

float l_shading(t_hit *hit, t_light *light, t_closest *cl)
{
	float l_coef;
	float l_intens;
	float n_dot_l;
	t_vector v_to_lght;

	l_coef = 0;
	v_to_lght = vector_sub(light->origin_coord,
						   hit->hit_pos);
	l_intens = light->ratio;
	n_dot_l = dot_prod(hit->hit_normal, v_to_lght);
	if (n_dot_l > 0)
		l_coef += l_intens * n_dot_l / (vector_length(hit->hit_normal) * vector_length(v_to_lght));
	return (l_coef);
}

float s_shading(t_hit *hit, t_light *light, t_ray *ray, t_closest *cl)
{
	float coef;
	float n_dot_l;
	float r_dot_v;
	t_vector v_to_lght;
	t_vector refl;
	t_vector v;

	coef = 0;
	v_to_lght = vector_sub(light->origin_coord, hit->hit_pos);
	n_dot_l = dot_prod(hit->hit_normal, v_to_lght);
	refl = v_mult_scal(v_mult_scal(hit->hit_normal, 2), n_dot_l);
	refl = vector_sub(refl, v_to_lght);
	v = v_mult_scal(ray->dir, -1);
	r_dot_v = dot_prod(refl, v);
	if (r_dot_v > 0)
		coef += light->ratio * powf(r_dot_v / (vector_length(refl) * vector_length(v)), 10);
	return (coef);
}

int in_shad(t_scene *sc, t_light *light, t_hit *hit)
{
	t_closest shadow;
	t_vector v_to_light;
	t_ray r_to_light;

	//sh_range.t_min = 0.0015;
	//sh_range.t_max = 1;
	v_to_light = vector_sub(light->origin_coord, hit->hit_pos);
	r_to_light = set_ray(hit->hit_pos, v_to_light);
	cl_inter(&shadow, &r_to_light, sc->object, 1); //ClosestIntersection(P, L, 0.001, t_max)
	if (shadow.closest_obj)
	{
		return (1);
	}
	return (0);
}

t_vector calc_light(t_closest *cl, t_scene *scene, t_ray *ray)
{
	t_vector rgb;
	t_vector temp;
	t_hit hit;
	t_list *light;
	float coef;

	light = scene->light;
	if (typecmp("sp", cl->closest_obj))
		get_hit_sp(&hit, cl, ray);
	if (typecmp("tr", cl->closest_obj))
		get_hit_tr(&hit, cl, ray);
	if (typecmp("pl", cl->closest_obj))
		get_hit_tr(&hit, cl, ray);
	rgb = rgb_mult_n(cl->closest_obj->rgb, scene->ambl.ratio); // ok
	while (light)
	{
		if (in_shad(scene, light->content, &hit))
		{
			light = light->next;
			continue;
		}
		coef = l_shading(&hit, light->content, cl);
		if (typecmp("sp", cl->closest_obj))
			coef += s_shading(&hit, light->content, ray, cl);
		temp = rgb_mult_n(((t_light *)(light->content))->rgb, coef); //fixme цвет
		rgb = rgb_add(rgb, temp);
		light = light->next;
	}
	return (rgb);
}

int		ray_trace(t_ray *ray, t_scene *scene)
{
	t_vector rgb;
	t_closest cl;
	t_range range;

	range.t_min = 1;
	range.t_max = INFINITY;
	cl_inter(&cl, ray, scene->object, 0);
	if (cl.closest_obj == NULL)
		return (BG_COLOUR);
	else
		rgb = calc_light(&cl, scene, ray);
	return (ctohex(rgb));
}

void put_rays(t_scene *scene, void *mlx, void *win)
{
	int canvas_x;
	int canvas_y;
	float vp_x;
	float vp_y;
	int colour;
	t_vector plane;
	t_ray ray;

	plane = get_sp_plane(scene->width, scene->height, scene->camera->content);
	canvas_y = 0;
	vp_y = scene->height / 2;
	while (vp_y >= scene->height / 2 * (-1))
	{
		vp_x = scene->width / 2 * (-1);
		canvas_x = 0;
		while (vp_x <= scene->width / 2)
		{
			ray = set_ray(((t_camera *)(scene->camera->content))->origin_coord,
						  set_vector(plane.x * vp_x, plane.y * vp_y, plane.z));
			//colour = calc_colour(scene, &plane, vp_x, vp_y); //fixme
			colour = ray_trace(&ray, scene);
			mlx_pixel_put(mlx, win, canvas_x, canvas_y, colour);
			vp_x++;
			canvas_x++;
		}
		vp_y--;
		canvas_y++;
	}
}