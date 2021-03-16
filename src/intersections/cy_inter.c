/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:58:09 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/15 23:59:34 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		cy_check_t(float *t, t_object *o, t_ray *r)
{
	t_vector	q;
	t_vector	point2;

	point2 = v3_add(o->orig, v3_mult(o->normal, o->cyl_h));
	q = v3_add(r->orig, v3_mult(r->dir, *t));
	if (dot_prod(o->normal, v3_sub(q, o->orig)) <= 0)
		*t = -1;
	if (dot_prod(o->normal, v3_sub(q, point2)) >= 0)
		*t = -1;
}

static int		cy_solvable(t_ray *r, t_object *o, float *t)
{
	t_vector	a_sqrt;
	t_vector	right;
	t_vector	sub_o;
	float		b;
	float		c;

	sub_o = v3_sub(r->orig, o->orig);
	a_sqrt = v3_sub(r->dir, v3_mult(o->normal, dot_prod(r->dir, o->normal)));
	right = v3_sub(sub_o, v3_mult(o->normal, dot_prod(sub_o, o->normal)));
	b = 2 * dot_prod(a_sqrt, right);
	c = dot_prod(right, right) - ((o->cyl_d / 2) * (o->cyl_d / 2));
	if (solve_quad(dot_prod(a_sqrt, a_sqrt), b, c, t))
		return (1);
	else
		return (0);
}

void			intersect_cy(t_ray *ray, t_object *obj, float *res)
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
