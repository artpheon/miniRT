/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:01:09 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:01:10 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ray_trace(t_ray *ray, t_scene *scene)
{
	t_vector	rgb;
	t_closest	cl;
	t_range		range;
	t_hit		hit;

	range.t_min = 0;
	range.t_max = INFINITY;
	cl_inter(&cl, ray, scene->object, &range);
	if (cl.cl_obj == NULL)
		return (BG_COLOUR);
	else
		rgb = calc_light(&cl, scene, ray, &hit);
	return (ctohex(rgb));
}

t_vector	multiply_by_matrix(t_vector p, t_matrix m)
{
	t_vector res;

	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
	return (res);
}

t_matrix	look_at(t_vector origin, t_vector cam_vector)
{
	t_matrix		new;
	t_vector		upward;
	t_vector		right;
	t_vector		up;

	upward = set_vector(0, 1, 0);
	normalize(&upward);
	right = v3_cross(upward, cam_vector);
	normalize(&right);
	up = v3_cross(cam_vector, right);
	normalize(&up);
	new.d[0][0] = right.x;
	new.d[0][1] = right.y;
	new.d[0][2] = right.z;
	new.d[1][0] = up.x;
	new.d[1][1] = up.y;
	new.d[1][2] = up.z;
	new.d[2][0] = cam_vector.x;
	new.d[2][1] = cam_vector.y;
	new.d[2][2] = cam_vector.z;
	new.d[3][0] = origin.x;
	new.d[3][1] = origin.y;
	new.d[3][2] = origin.z;
	return (new);
}

t_vector	get_dir(t_camera *cam, t_scene *scene, int x, int y)
{
	double			fov_coeff;
	double			aspect_ratio;
	double			p_x;
	double			p_y;

	fov_coeff = tan((double)cam->fov / 2 * M_PI / 180);
	aspect_ratio = (double)scene->width / (double)scene->height;
	p_x = (-2 * (x + 0.5) / (double)scene->width) * aspect_ratio * fov_coeff;
	p_y = (2 * (y + 0.5) / (double)scene->height) * fov_coeff;
	return (set_vector(p_x, p_y, 1));
}

t_ray		gen_ray(int x, int y, t_scene *scene)
{
	t_vector		origin;
	t_vector		direction;
	t_matrix		c2w;
	t_camera		*cam;

	cam = scene->camera->content;
	c2w = look_at(cam->orig, cam->normal);
	origin = multiply_by_matrix(set_vector(0, 0, 0), c2w);
	direction = get_dir(cam, scene, x, y);
	direction = multiply_by_matrix(direction, c2w);
	direction = v3_sub(direction, origin);
	return (set_ray(origin, direction));
}
