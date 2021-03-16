/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:59:11 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/15 23:59:12 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	intersect_sq(t_ray *ray, t_object *obj, float *res)
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
