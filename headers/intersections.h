/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:42:45 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:42:55 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

int		solve_quad(float a, float b, float c, float *t);
void	intersect_sp(t_ray *ray, t_object *obj, float *res);
int		inter_as_pl(t_ray *ray, t_object *obj, float *res);
void	intersect_pl(t_ray *ray, t_object *obj, float *res);
void	intersect_tr(t_ray *ray, t_object *obj, float *res);
void	intersect_sq(t_ray *ray, t_object *obj, float *res);
void	intersect_cy(t_ray *ray, t_object *obj, float *res);
void	cl_inter(t_closest *cl, t_ray *ray, t_list *start, t_range *range);
#endif
