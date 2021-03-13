//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

int key_hook(int keycode, t_info *info)
{
	static int i;

	if (keycode == ESC)
		exit_free(info);
	if (keycode == TAB)
	{
		i++;
		if (i >= info->cams)
			i = 0;
		mlx_put_image_to_window(info->mlx, info->win, info->img[i].img, 0, 0);
	}
	printf("key: %d\n", keycode);
	return (0);
}

int             w_close(t_info *info)
{
	exit_free(info);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void 	xy_size_check(t_scene *scene, void *mlx)
{
	int w;
	int h;
	mlx_get_screen_size(mlx, &w, &h);
	if (scene->width > w)
		scene->width = w;
	if (scene->height > h)
		scene->height = h;
}

void start_render(t_info *info)
{
	t_scene	*scene;
	t_list	*start;
	int		i;

	scene = info->scene;
	start = info->scene->camera;
	info->mlx = mlx_init();
	xy_size_check(scene, info->mlx);
	info->cams = ft_lstsize(scene->camera);
	i = 0;
	if (info->sshot)
		shoot_screen(info);
	info->img = malloc(sizeof(t_data) * info->cams); //i.e. 5
	info->win = mlx_new_window(info->mlx, scene->width, scene->height, "miniRT"); // создаем окно
	while (i < info->cams)
	{
		info->img[i].img = mlx_new_image(info->mlx, scene->width, scene->height); // создаем имидж
		info->img[i].addr = mlx_get_data_addr(info->img[i].img,
					 					&info->img[i].bits_per_pixel,
										&info->img[i].line_length,
										&info->img[i].endian); // достаем имиджа адрес
		put_rays(info->scene, &info->img[i], i); //рисуем имидж
		scene->camera = scene->camera->next;
		i++;
	}
	scene->camera = start;
	mlx_put_image_to_window(info->mlx, info->win, info->img[0].img, 0, 0); //кидаем имидж в окно
	mlx_hook(info->win, 17, 0, w_close, info);
	mlx_hook(info->win, 2, 0, key_hook, info);
	mlx_loop(info->mlx);
}



int		solve_quad(float a, float b, float c, float *t)
{
	float discr;

	discr = (b * b) - (4 * a * c);
	if (discr < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
		return (0);
	}
	else
	{
		t[0] = (-b - sqrtf(discr)) / (2 * a);
		t[1] = (-b + sqrtf(discr)) / (2 * a);
	}
	return (1);
}

void intersect_sp(t_ray *ray, t_object *obj, float *res)
{
	t_vector	sp_to_ray;
	float		b;
	float		c;
	float		roots[2];

	sp_to_ray = v3_sub(ray->orig, obj->orig);
	b = 2 * dot_prod(ray->dir, sp_to_ray);
	c = dot_prod(sp_to_ray, sp_to_ray) - (obj->sp_radius * obj->sp_radius);
	if (solve_quad(1, b, c, roots))
	{
		if (roots[0] < roots[1] && roots[0] >= 0)
			*res = roots[0];
		if (roots[1] >= 0 && roots[1] < roots[0])
			*res = roots[1];
	}
}

int inter_as_pl(t_ray *ray, t_object *o, float *res)
{
	t_vector	w;
	float		a;
	float		det;

	w = v3_sub(ray->orig, o->orig); // t = dot(w,N)/dot(v,N)
	a = -dot_prod(w, o->normal);
	det = dot_prod(ray->dir, o->normal);
	if (fabsf(det) < macheps())
	{
		*res = INFINITY;
		return (0);
	}
	if ((a / det) < 0)
	{
		*res = INFINITY;
		return (0);
	}
	*res = a / det;
	return (1);
}

void tr_solve(t_ray *r, t_object *o, t_vector *p, float *res)
{
	t_vector	pvec;
	t_vector	tvec;
	float		det;
	float		c;
	float		a;
	float		b;

	pvec = v3_cross(r->dir, p[1]);
	det = dot_prod(p[0], pvec);
	c = 1 / det;
	tvec = v3_sub(r->orig, o->orig);
	a = dot_prod(tvec, pvec) * c;
	if (a < 0 || a > 1)
	{
		*res = INFINITY;
		return ;
	}
	tvec = v3_cross(tvec, p[0]);
	b  = dot_prod(r->dir, tvec) * c;
	if (b < 0 || (a + b) > 1)
	{
		*res = INFINITY;
		return ;
	}
	*res = dot_prod(p[1], tvec) * c;
}

void intersect_tr(t_ray *ray, t_object *obj, float *res)
{
	t_vector	tr_vars[2];
	float		t;

	tr_vars[0] = v3_sub(obj->angle2, obj->orig);
	tr_vars[1] = v3_sub(obj->angle3, obj->orig); //считаем доп.параметры
	if (inter_as_pl(ray, obj, &t))	  //если пересекло плоскость в кот.лежит 3-уг
		tr_solve(ray, obj, tr_vars, &t); //находим точку пересечения
	*res = t;
}

void intersect_pl(t_ray *ray, t_object *obj, float *res)
{
	float	r;

	inter_as_pl(ray, obj, &r);
	*res = r;
}

void intersect_sq(t_ray *ray, t_object *obj, float *res)
{
	float		t;
	float		denom;
	float		hht;
	t_vector	p0;
	t_vector	hpos;

	t = INFINITY;
	if (inter_as_pl(ray, obj, &t))
	{
		denom = dot_prod(obj->normal, ray->dir);
		p0 = v3_sub(obj->orig, ray->orig);
		t = dot_prod(p0, obj->normal) / denom;
		hpos = v3_add(ray->orig, v3_mult(ray->dir, t));
		if (t < 0)
			t = INFINITY;
		else
		{
			hht = obj->side_size / 2;
			hpos = v3_sub(hpos, obj->orig);
			if (fabsf(hpos.x) > hht || fabsf(hpos.y) > hht ||
				fabsf(hpos.z) > hht)
				t = INFINITY;
		}
	}
	*res = t;
}

void cy_check_t(float *t, t_object *o, t_ray *r)
{
	t_vector q;
	t_vector point2;

	point2 = v3_add(o->orig, v3_mult(o->normal, o->cyl_h));
	q = v3_add(r->orig, v3_mult(r->dir, *t));
	if (dot_prod(o->normal, v3_sub(q, o->orig)) <= 0)
		*t = -1;
	if (dot_prod(o->normal, v3_sub(q, point2)) >= 0)
		*t = -1;
}

int		cy_solvable(t_ray *r, t_object *o, float *t)
{
	t_vector a_sqrt;
	t_vector right;
	t_vector sub_o;
	float a;
	float b;
	float c;

	sub_o = v3_sub(r->orig, o->orig);
	a_sqrt = v3_sub(r->dir, v3_mult(o->normal, dot_prod(r->dir, o->normal)));
	a = dot_prod(a_sqrt, a_sqrt);
	right = v3_sub(sub_o, v3_mult(o->normal, dot_prod(sub_o, o->normal)));
	b = 2 * dot_prod(a_sqrt, right);
	c = dot_prod(right, right) - ((o->cyl_d / 2) * (o->cyl_d / 2));
	if (solve_quad(a, b, c, t))
		return (1);
	else
		return (0);
}

void	intersect_cy(t_ray *ray, t_object *obj, float *res)
{
	float t[2];
	if (cy_solvable(ray, obj, t))
	{
		if (t[0] > 0)
			cy_check_t(&t[0], obj, ray);
		if (t[1] > 0)
			cy_check_t(&t[1], obj, ray);
		if (t[0] < 0 && t[1] < 0)
			*res = -1;
		if (t[1] < t[0])
		{
			if (t[1] > 0)
				*res = t[1];
			else
				*res = t[0];
		}
		else
		{
			if (t[0] > 0)
				*res = t[0];
			else
				*res = t[1];
		}
	}
}

void cl_inter(t_closest *cl, t_ray *ray, t_list *start, t_range *range)
{
	float	resol;

	resol = INFINITY;
	cl->cl_t = INFINITY;
	cl->cl_obj = NULL;
	while (start)
	{
		if (typecmp("sp", start->content))
			intersect_sp(ray, start->content, &resol);
		if (typecmp("tr", start->content))
			intersect_tr(ray, start->content, &resol);
		if (typecmp("pl", start->content))
			intersect_pl(ray, start->content, &resol);
		if (typecmp("sq", start->content))
			intersect_sq(ray, start->content, &resol);
		if (typecmp("cy", start->content))
			intersect_cy(ray, start->content, &resol);
		if (resol >= range->t_min && resol < cl->cl_t && resol < range->t_max)
			{
				cl->cl_t = resol;
				cl->cl_obj = start->content;
			}
		start = start->next;
	}
}

int		ray_trace(t_ray *ray, t_scene *scene)
{
	t_vector rgb;
	t_closest cl;
	t_range range;
	t_hit	hit;

	range.t_min = 0;
	range.t_max = INFINITY;
	cl_inter(&cl, ray, scene->object, &range);
	if (cl.cl_obj == NULL)
		return (BG_COLOUR);
	else
		rgb = calc_light(&cl, scene, ray, &hit);
	return (ctohex(rgb));
}

/* abeaugustijn
t_vec3f	look_at(t_camera *cam, t_vec3f ray_origin)
{
	t_vec3f	res;

	res.x = ray_origin.x * cam->dir_vecs.right.x + ray_origin.y *
												   cam->dir_vecs.up.x + ray_origin.z * cam->dir_vecs.forward.x;
	res.y = ray_origin.x * cam->dir_vecs.right.y + ray_origin.y *
												   cam->dir_vecs.up.y + ray_origin.z * cam->dir_vecs.forward.y;
	res.z = ray_origin.x * cam->dir_vecs.right.z + ray_origin.y *
												   cam->dir_vecs.up.z + ray_origin.z * cam->dir_vecs.forward.z;
	return (res);
} */

t_vector	get_ax(t_vector dir)
{
	if (fabsf(dir.x) >= fabsf(dir.y) &&
		fabsf(dir.x) >= fabsf(dir.z))
		return (set_vector(1, 0, 0));
	if (fabsf(dir.y) > fabsf(dir.z))
		return (set_vector(0, 1, 0));
	else
		return (set_vector(0, 0, 1));
}
void v3_mat_x(t_vector *v1, float x, float y, float z)
{
	v1->x = v1->x * 1 + v1->y * 0 + v1->z * 0;
	v1->y = v1->x * 0 + v1->y * cosf(x) + v1->z * -sinf(x);
	v1->z = v1->x * 0 + v1->y * sinf(x) + v1->z * cosf(x);

	v1->x = v1->x * cos(y) + v1->y * 0 + v1->z * sin(y);
	v1->y = v1->x * 0 + v1->y * 1 + v1->z * 0;
	v1->z = v1->x * -sin(y) + v1->y * 0 + v1->z * cosf(y);

	v1->x = v1->x * cos(z) + v1->y * -sin(z) + v1->z * 0;
	v1->y = v1->x * sin(z) + v1->y * cosf(z) + v1->z * 0;
	v1->z = v1->x * 0 + v1->y * 0 + v1->z * 1;
}
t_vector calc_vplane(float width, float height, t_camera *cam)
{
	t_vector	new;
	float		vp_width;
	float		vp_height;
	float		aspect_ratio;

	aspect_ratio = width / height;
	vp_width = tanf(M_PI * 0.5 * cam->fov / 180.) * 2;
	vp_height = vp_width / aspect_ratio;
	new.x = vp_width / width;
	new.y = vp_height / height;
	new.z = cam->normal.z;
	//print_vector(new);
	return (new);
}



t_ray	gen_ray(t_camera *cam, t_vector plane, float x, float y)
{
	t_vector dir;
	t_ray ray;

	dir.x = x * plane.x;
	dir.y = y * plane.y;
	dir.z = plane.z;

	v3_mat_x(&dir, 0, 0.4, 0);
	ray = set_ray(cam->orig, dir);
	return (ray);
}

void put_rays(t_scene *scene, t_data *img, int i)
{
	int			canvas[2];
	float		vp[2];
	int			colour;
	t_vector	plane;
	t_ray		ray;

	plane = calc_vplane(scene->width, scene->height, scene->camera->content);
	canvas[1] = 0;
	vp[1] = scene->height / 2;
	while (vp[1] > scene->height / 2 * (-1))
	{
		vp[0] = scene->width / 2 * (-1);
		canvas[0] = 0;
		while (vp[0] < scene->width / 2)
		{
			ray = gen_ray(scene->camera->content, plane, vp[0], vp[1]);
			colour = ray_trace(&ray, scene);
			my_mlx_pixel_put(img, canvas[0], canvas[1], colour);
			vp[0]++;
			canvas[0]++;
		}
		vp[1]--;
		canvas[1]++;
	}
}