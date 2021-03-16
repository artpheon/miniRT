/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:57:44 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:25:28 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float		dot_prod(t_vector vector1, t_vector vector2)
{
	return (vector1.x * vector2.x +
			vector1.y * vector2.y +
			vector1.z * vector2.z);
}

float		vector_length(t_vector v)
{
	float x;
	float y;
	float z;
	float length;

	x = powf(v.x, 2);
	y = powf(v.y, 2);
	z = powf(v.z, 2);
	length = sqrtf(x + y + z);
	return (length);
}

float		v3_dist(t_vector v1, t_vector v2)
{
	float res;

	res = powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2) + powf(v1.z - v2.z, 2);
	res = sqrtf(res);
	return (res);
}

void		normalize(t_vector *v)
{
	float length;

	length = vector_length(*v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

t_vector	v3_add(t_vector v1, t_vector v2)
{
	t_vector sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}
