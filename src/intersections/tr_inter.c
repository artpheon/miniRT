/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:59:15 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/15 23:59:16 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	tr_solve(t_ray *r, t_object *o, t_vector *p, float *res)
{
	t_vector	pvec;
	t_vector	tvec;
	float		det;
	float		a;
	float		b;

	pvec = v3_cross(r->dir, p[1]);
	det = dot_prod(p[0], pvec);
	det = 1 / det;
	tvec = v3_sub(r->orig, o->orig);
	a = dot_prod(tvec, pvec) * det;
	if (a < 0 || a > 1)
	{
		*res = INFINITY;
		return ;
	}
	tvec = v3_cross(tvec, p[0]);
	b = dot_prod(r->dir, tvec) * det;
	if (b < 0 || (a + b) > 1)
	{
		*res = INFINITY;
		return ;
	}
	*res = dot_prod(p[1], tvec) * det;
}

void		intersect_tr(t_ray *ray, t_object *obj, float *res)
{
	t_vector	tr_vars[2];
	float		t;

	tr_vars[0] = v3_sub(obj->angle2, obj->orig);
	tr_vars[1] = v3_sub(obj->angle3, obj->orig);
	if (inter_as_pl(ray, obj, &t))
		tr_solve(ray, obj, tr_vars, &t);
	*res = t;
}
