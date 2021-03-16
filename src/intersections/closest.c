/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:58:02 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/15 23:59:28 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	cl_inter(t_closest *cl, t_ray *ray, t_list *start, t_range *range)
{
	float	t;

	t = INFINITY;
	cl->cl_t = INFINITY;
	cl->cl_obj = NULL;
	while (start)
	{
		if (typecmp("sp", start->content))
			intersect_sp(ray, start->content, &t);
		if (typecmp("tr", start->content))
			intersect_tr(ray, start->content, &t);
		if (typecmp("pl", start->content))
			intersect_pl(ray, start->content, &t);
		if (typecmp("sq", start->content))
			intersect_sq(ray, start->content, &t);
		if (typecmp("cy", start->content))
			intersect_cy(ray, start->content, &t);
		if (t >= range->t_min && t < cl->cl_t && t < range->t_max)
		{
			cl->cl_t = t;
			cl->cl_obj = start->content;
		}
		start = start->next;
	}
}
