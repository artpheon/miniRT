/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:41:43 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:41:49 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOM_H
# define GEOM_H

float		dot_prod(t_vector vector1, t_vector vector2);
float		vector_length(t_vector v);
float		v3_dist(t_vector v1, t_vector v2);
void		normalize(t_vector *v);
t_vector	v3_add(t_vector v1, t_vector v2);
t_vector	v3_sub(t_vector v1, t_vector v2);
t_vector	v3_cross(t_vector v1, t_vector v2);
t_vector	v3_mult(t_vector v1, float num);
int			v3cmp(t_vector v1, t_vector v2);
#endif
