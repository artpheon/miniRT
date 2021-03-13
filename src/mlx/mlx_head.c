//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

int key_hook(int keycode, t_info *info)
{
	static int i;

	if (keycode == ESC)
	{
		mlx_destroy_window(info->mlx, info->win);
		exit(0);
	}
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

void start_show(t_info *info)
{
	t_scene *scene;
	t_list	*cam_start;
	int		i;

	scene = info->scene;
	cam_start = info->scene->camera;
	info->mlx = mlx_init();
	xy_size_check(scene, info->mlx);
	info->cams = ft_lstsize(scene->camera);
	i = 0;
	info->img = malloc(sizeof(t_data) * info->cams); //i.e. 5
	info->win = mlx_new_window(info->mlx, scene->width, scene->height, "miniRT"); // создаем окно

	while (i < info->cams)
	{
		info->img[i].img = mlx_new_image(info->mlx, scene->width, scene->height); // создаем имидж
		info->img[i].addr = mlx_get_data_addr(info->img[i].img, &info->img[i].bits_per_pixel, &info->img[i].line_length, &info->img[i].endian); // достаем имиджа адрес
		put_rays(info->scene, &info->img[i], i); //рисуем имидж
		i++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img[0].img, 0, 0); //кидаем имидж в окно
	mlx_hook(info->win, 2, 0, key_hook, info);
	mlx_loop(info->mlx);
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
	new.z = -1;
	return (new);
}

void intersect_sp(t_ray *ray, t_object *obj, float *res, float t)
{
	t_vector	sp_to_ray;
	float		b;
	float		c;
	float		discriminant;
	float		root;

	sp_to_ray = vector_sub(ray->orig, obj->origin_coord);
	b = 2 * dot_prod(ray->dir, sp_to_ray);
	c = dot_prod(sp_to_ray, sp_to_ray) - (obj->sp_radius * obj->sp_radius);
	discriminant = (b * b) - (4 * c);
	*res = INFINITY;
	if (discriminant >= 0)
	{
		discriminant = sqrtf(discriminant);
		root = (-b + discriminant) / 2;
		if (root >= 0 && root < t)
			*res = root;
		root = (-b - discriminant) / 2;
		if (root >= 0 && root < t)
			*res = root;
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
	t_vector	w;
	float		a;
	float		det;

	w = vector_sub(ray->orig, o->origin_coord); // t = dot(w,N)/dot(v,N)
	a = -dot_prod(w, o->vector_norm);
	det = dot_prod(ray->dir, o->vector_norm);
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

void tr_solve(t_ray *r, t_object *o, t_tr_vars *p, float *res)
{
	t_vector	pvec;
	t_vector	tvec;
	float		det;
	float		c;
	float		a;
	float		b;

	pvec = vector_prod(r->dir, p->v);
	det = dot_prod(p->u, pvec);
	c = 1 / det;
	tvec = vector_sub(r->orig, o->origin_coord);
	a = dot_prod(tvec, pvec) * c;
	if (a < 0 || a > 1)
	{
		*res = INFINITY;
		return ;
	}
	tvec = vector_prod(tvec, p->u);
	b  = dot_prod(r->dir, tvec) * c;
	if (b < 0 || (a + b) > 1)
	{
		*res = INFINITY;
		return ;
	}
	*res = dot_prod(p->v, tvec) * c;
}

void intersect_tr(t_ray *ray, t_object *obj, float *res)
{
	t_tr_vars	new;
	float		t;

	tr_solve_vars(&new, obj);		  //считаем доп.параметры
	if (inter_as_pl(ray, obj, &t))	  //если пересекло плоскость в кот.лежит 3-уг
		tr_solve(ray, obj, &new, &t); //находим точку пересечения
	*res = t;
}

void intersect_pl(t_ray *ray, t_object *obj, float *res)
{
	float	r;

	inter_as_pl(ray, obj, &r);
	*res = r;
}


float		sq_as_pl(t_ray *r, t_object *sq)
{
	float		a;
	float		b;
	float		t;
	t_vector	tmp;

	tmp = vector_sub(r->orig, sq->origin_coord);
	a = dot_prod(tmp, sq->vector_norm);
	b = dot_prod(r->dir, sq->vector_norm);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t = -a / b;
	if (t < 0)
		return (0);
	return (t);
}

float	magnitude(t_vector a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2)));
}

t_vector	calculate_rot(t_vector *c2, t_vector *c3, t_vector rot, t_vector to)
{
	t_vector	c1;
	t_vector	v;
	float	c;
	float	s;
	float	r;

	v = vector_prod(to, rot);
	c = dot_prod(rot, to);
	s = pow(magnitude(v), 2);
	r = ((1 - c) / s);
	c1 = set_vector(-r * (pow(v.y, 2) + pow(v.z, 2)) + 1, r * v.x * \
				v.y - v.z, r * v.x * v.z + v.y);
	(*c2) = set_vector(r * v.x * v.y + v.z, -r * (pow(v.x, 2) + \
					pow(v.z, 2)) + 1, r * v.y * v.x - v.x);
	(*c3) = set_vector(r * v.x * v.z - v.y, r * v.y * v.z - v.x, -r * \
					(pow(v.x, 2) + pow(v.y, 2)) + 1);
	return (c1);
}

t_vector	apply_rot(t_vector pos, t_vector dir, t_vector rot)
{
	t_vector	c1;
	t_vector	c2;
	t_vector	c3;
	t_vector	prev;

	if (dir.x == 0 && dir.y < 0 && dir.z == 0)
		pos = set_vector(pos.x, pos.y, -pos.z);
	else if (!(dir.x == 0 && dir.y != 0 && dir.z == 0))
	{
		prev = pos;
		c1 = calculate_rot(&c2, &c3, rot, dir);
		pos = set_vector(dot_prod(c1, prev), dot_prod(c2, prev), dot_prod(c3, prev));
	}
	return (pos);
}

void intersect_sq(t_ray *ray, t_object *obj, float *res)
{
	float		t;
	float		a;
	t_vector	p;
	t_vector	data;

	if (!(t = sq_as_pl(ray, obj)))
		return ;
	data = v_mult_scal(ray->dir, t);
	p = vector_add(ray->orig, data);
	if (obj->vector_norm.x != 0 || obj->vector_norm.y == 0 || obj->vector_norm.z != 0)
		apply_rot(p, obj->vector_norm, set_vector(0, 1, 0));
	a = obj->origin_coord.x - (obj->side_size / 2);
	data.x = obj->origin_coord.x + (obj->side_size / 2);
	data.y = obj->origin_coord.z - (obj->side_size / 2);
	data.z = obj->origin_coord.z + (obj->side_size / 2); //fixme check at qfeuilla
	if (!((p.x >= a && p.x <= data.x) && (p.z <= data.z && p.z >= data.y)))
		return ;
	*res = t;
	/*
	t_vector	side_dir;
	t_vector	up_dir;
	t_vector	side;
	t_vector	u_l;
	t_vector	u_r;
	t_vector	b_r;
	t_vector	b_l;
	float 		p0z;

	if (obj->vector_norm.z == 0)
		return ;
	p0z = ((obj->vector_norm.z * obj->origin_coord.z) +
			obj->vector_norm.x * (obj->origin_coord.x + 1)) / obj->vector_norm.z;
	side_dir = set_vector(-1, obj->origin_coord.y, p0z);
	if (!vec_cmp(side_dir, obj->origin_coord))
		side_dir = vector_sub(side_dir, obj->origin_coord);
	normalize(&side_dir);
	side = vector_add(obj->origin_coord, v_mult_scal(side_dir, (obj->side_size / 2)));
	p0z = obj->vector_norm.y * ((obj->origin_coord.y - 1) + (obj->vector_norm.z * obj->origin_coord.z)) / obj->vector_norm.z;
	up_dir = set_vector(obj->origin_coord.x, 1, p0z);
	if (!vec_cmp(up_dir, obj->origin_coord))
		up_dir = vector_sub(up_dir, obj->origin_coord);
	normalize(&up_dir);
	u_l = vector_add(side, v_mult_scal(up_dir, (obj->side_size / 2)));
	print_vector(u_l);

	side_dir = v_mult_scal(side_dir, -1);
	side = vector_add(obj->origin_coord, v_mult_scal(side_dir, (obj->side_size / 2)));
	u_r = vector_add(side, v_mult_scal(up_dir, (obj->side_size / 2)));
	print_vector(u_r);

	up_dir = v_mult_scal(up_dir, -1);
	b_r = vector_add(side, v_mult_scal(up_dir, (obj->side_size / 2)));
	print_vector(b_r);

	side_dir = v_mult_scal(side_dir, -1);
	side = vector_add(obj->origin_coord, v_mult_scal(side_dir, (obj->side_size / 2)));
	b_l = vector_add(side, v_mult_scal(up_dir, (obj->side_size / 2)));
	print_vector(b_l);
	getchar();*/


	/*
	float	t;
	float denom, hht;
	t_vector p0, hpos;

	t = INFINITY;
	if (inter_as_pl(ray, obj, &t))
	{
		/*a = dot_prod(vector_sub(ray->orig, obj->origin_coord), obj->vector_norm);
		b = dot_prod(ray->dir, obj->vector_norm);
		if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
			return ;
		t1 = -a / b;
		d = vector_sub(vector_add(v_mult_scal(ray->dir, t1), ray->orig), obj->origin_coord);
		t2 = obj->side_size / 2;
		if (fabsf(d.x) > t2 || fabsf(d.y) > t2 || fabsf(d.z) > t2)
			return ;
		if (t1 > 0)
			*res = t1;*/
/*
		denom = dot_prod(obj->vector_norm, ray->dir);
		p0 = vector_sub(obj->origin_coord, ray->orig);
		t = dot_prod(p0, obj->vector_norm) / denom;
		hpos = vector_add(ray->orig, v_mult_scal(ray->dir, t));
		if (t < 0)
			t = INFINITY;
		else
		{
			hht = obj->side_size / 2;
			if (fabsf(hpos.x - obj->origin_coord.x) > hht ||
				fabsf(hpos.y - obj->origin_coord.y) > hht ||
				fabsf(hpos.z - obj->origin_coord.z) > hht)
				t = INFINITY;
		}
	} //fixme wrong formula
	*res = t; */
}

int		solve_quad(float a, float b, float c, float *t)
{
	float discrim;

	discrim = (b * b) - (4 * a * c);
	if (discrim < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
		return (0);
	}
	else
	{
		t[0] = (-b - sqrtf(discrim)) / (2 * a);
		t[1] = (-b + sqrtf(discrim)) / (2 * a);
	}
	return (1);
}

void cy_check_t(float *t, t_object *o, t_ray *r)
{
	t_vector q;
	t_vector point2;

	point2 = vector_add(o->origin_coord, v_mult_scal(o->vector_norm, o->cyl_h));
	q = vector_add(r->orig, v_mult_scal(r->dir, *t));
	if (dot_prod(o->vector_norm, vector_sub(q, o->origin_coord)) <= 0)
		*t = -1;
	if (dot_prod(o->vector_norm, vector_sub(q, point2)) >= 0)
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

	sub_o = vector_sub(r->orig, o->origin_coord);
	a_sqrt = vector_sub(r->dir, v_mult_scal(o->vector_norm, dot_prod(r->dir, o->vector_norm)));
	a = dot_prod(a_sqrt, a_sqrt);
	right = vector_sub(sub_o, v_mult_scal(o->vector_norm, dot_prod(sub_o, o->vector_norm)));
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

	cl->closest_t = INFINITY;
	resol = INFINITY;
	cl->closest_obj = NULL;
	while (start)
	{
		if (typecmp("sp", start->content))
		{
			intersect_sp(ray, start->content, &resol, cl->closest_t);
			if (resol >= range->t_min && resol < cl->closest_t && resol < range->t_max)
			{
				cl->closest_t = resol;
				cl->closest_obj = start->content;
			}
		}
		if (typecmp("tr", start->content))
		{
			intersect_tr(ray, start->content, &resol);
			if (resol >= range->t_min && resol < cl->closest_t && resol < range->t_max)
			{
				cl->closest_t = resol;
				cl->closest_obj = start->content;
			}
		}
		if (typecmp("pl", start->content))
		{
			intersect_pl(ray, start->content, &resol);
			if (resol >= range->t_min && resol < cl->closest_t && resol < range->t_max)
			{
				cl->closest_t = resol;
				cl->closest_obj = start->content;
			}
		}
		if (typecmp("sq", start->content))
		{
			intersect_sq(ray, start->content, &resol);
			if (resol >= range->t_min && resol < cl->closest_t && resol < range->t_max)
			{
				cl->closest_t = resol;
				cl->closest_obj = start->content;
			}
		}
		if (typecmp("cy", start->content))
		{
			intersect_cy(ray, start->content, &resol);
			if (resol >= range->t_min && resol < cl->closest_t && resol < range->t_max)
			{
				cl->closest_t = resol;
				cl->closest_obj = start->content;
			}
		}
		start = start->next;
	}
}

void get_hit_sp(t_hit *hit, t_closest *cl, t_ray *ray)
{
	hit->hit_dist = cl->closest_t;
	hit->hit_pos = vector_add(ray->orig, v_mult_scal(ray->dir, hit->hit_dist));
	hit->hit_normal = vector_sub(hit->hit_pos, cl->closest_obj->origin_coord);
	normalize(&hit->hit_normal);
}

void get_hit_tr(t_hit *hit, t_closest *cl, t_ray *ray)
{
	hit->hit_dist = cl->closest_t * 0.99;
	hit->hit_pos = vector_add(ray->orig, v_mult_scal(ray->dir, hit->hit_dist));
	if (dot_prod(ray->dir, cl->closest_obj->vector_norm) > 0)
		hit->hit_normal = v_mult_scal(cl->closest_obj->vector_norm, -1);
	else
		hit->hit_normal = cl->closest_obj->vector_norm;
}

float l_shading(t_hit *hit, t_light *light)
{
	float		l_coef;
	float		l_intens;
	float		n_dot_l;
	t_vector	v_to_lght;

	l_coef = 0;
	v_to_lght = vector_sub(light->origin_coord,
						   hit->hit_pos);
	l_intens = light->ratio;
	n_dot_l = dot_prod(hit->hit_normal, v_to_lght);
	if (n_dot_l > 0)
		l_coef += l_intens * n_dot_l / (vector_length(hit->hit_normal) * vector_length(v_to_lght));
	return (l_coef);
}

float s_shading(t_hit *hit, t_light *light, t_ray *ray)
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
	t_range	sh_range;

	sh_range.t_min = 0.0015;
	sh_range.t_max = vector_dist(hit->hit_pos, light->origin_coord);
	v_to_light = vector_sub(light->origin_coord, hit->hit_pos);
	r_to_light = set_ray(hit->hit_pos, v_to_light);
	cl_inter(&shadow, &r_to_light, sc->object, &sh_range); //ClosestIntersection(P, L, 0.001, t_max)
	if (shadow.closest_obj)
	{
		return (1);
	}
	return (0);
}

t_vector calc_light(t_closest *cl, t_scene *scene, t_ray *ray, t_hit *hit)
{
	t_vector	rgb;
	t_vector	temp;
	t_list		*light;
	float		coef;

	light = scene->light;
	if (typecmp("sp", cl->closest_obj))
		get_hit_sp(hit, cl, ray);
	if (typecmp("tr", cl->closest_obj))
		get_hit_tr(hit, cl, ray);
	if (typecmp("pl", cl->closest_obj))
		get_hit_tr(hit, cl, ray);
	if (typecmp("sq", cl->closest_obj))
		get_hit_tr(hit, cl, ray);
	if (typecmp("cy", cl->closest_obj))
		get_hit_tr(hit, cl, ray);
	rgb = rgb_mult_n(cl->closest_obj->rgb, scene->ambl.ratio); // fixme нельзя смешивать ргб
	while (light)
	{
		if (in_shad(scene, light->content, hit))
		{
			light = light->next;
			continue;
		}
		coef = l_shading(hit, light->content);
		if (typecmp("sp", cl->closest_obj))
			coef += s_shading(hit, light->content, ray);
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
	t_hit	*hit;

	range.t_min = 0;
	range.t_max = INFINITY;
	hit = malloc(sizeof(t_hit));
	rgb = set_vector(0 ,0 , 0);
	if (hit)
	{
		cl_inter(&cl, ray, scene->object, &range);
		if (cl.closest_obj == NULL)
			return (BG_COLOUR);
		else
			rgb = calc_light(&cl, scene, ray, hit);
	}
	free(hit);
	return (ctohex(rgb));
}

void put_rays(t_scene *scene, t_data *img, int i)
{
	int			canvas_x;
	int			canvas_y;
	float		vp_x;
	float		vp_y;
	int			colour;
	t_vector	plane;
	t_ray		ray;

	if (i)
		scene->camera = scene->camera->next;
	plane = calc_vplane(scene->width, scene->height, scene->camera->content);
	canvas_y = 0;
	vp_y = scene->height / 2;
	while (vp_y > scene->height / 2 * (-1))
	{
		vp_x = scene->width / 2 * (-1);
		canvas_x = 0;
		while (vp_x < scene->width / 2)
		{
			ray = set_ray(((t_camera *)(scene->camera->content))->origin_coord,
						  set_vector(plane.x * vp_x, plane.y * vp_y, plane.z));
			//colour = calc_colour(scene, &plane, vp_x, vp_y);
			colour = ray_trace(&ray, scene);
			my_mlx_pixel_put(img, canvas_x, canvas_y, colour);
			//mlx_pixel_put(mlx, win, canvas_x, canvas_y, colour);
			vp_x++;
			canvas_x++;
		}
		vp_y--;
		canvas_y++;
	}
}