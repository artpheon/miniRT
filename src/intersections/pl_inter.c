/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:59:00 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/15 23:59:01 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		inter_as_pl(t_ray *ray, t_object *obj, float *res)
{
	t_vector	w;
	float		a;
	float		det;

	w = v3_sub(ray->orig, obj->orig);
	a = -dot_prod(w, obj->normal);
	det = dot_prod(ray->dir, obj->normal);
	if (fabsf(det) < M_EPS)
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

void	intersect_pl(t_ray *ray, t_object *obj, float *res)
{
	float		r;

	inter_as_pl(ray, obj, &r);
	*res = r;
}
