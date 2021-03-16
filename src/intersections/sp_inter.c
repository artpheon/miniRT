/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:59:05 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/15 23:59:06 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		solve_quad(float a, float b, float c, float *t)
{
	float		discr;

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

void	intersect_sp(t_ray *ray, t_object *obj, float *res)
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
