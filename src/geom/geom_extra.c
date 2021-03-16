/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:57:44 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:25:02 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_vector	v3_sub(t_vector v1, t_vector v2)
{
	t_vector diff;

	diff.x = v1.x - v2.x;
	diff.y = v1.y - v2.y;
	diff.z = v1.z - v2.z;
	return (diff);
}

t_vector	v3_cross(t_vector v1, t_vector v2)
{
	t_vector prod;

	prod.x = (v1.y * v2.z) - (v1.z * v2.y);
	prod.y = (v1.z * v2.x) - (v1.x * v2.z);
	prod.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (prod);
}

t_vector	v3_mult(t_vector v1, float num)
{
	t_vector new;

	new.x = v1.x * num;
	new.y = v1.y * num;
	new.z = v1.z * num;
	return (new);
}

t_vector	v3_div(t_vector v1, float num)
{
	t_vector new;

	new.x = v1.x / num;
	new.y = v1.y / num;
	new.z = v1.z / num;
	return (new);
}

int			v3cmp(t_vector v1, t_vector v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	else
		return (0);
}
