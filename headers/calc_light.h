/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:42:18 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:43:08 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_LIGHT_H
# define CALC_LIGHT_H

void		get_hit(t_hit *hit, t_closest *cl, t_ray *ray);
float		l_shading(t_hit *hit, t_light *light);
float		s_shading(t_hit *hit, t_light *light, t_ray *ray);
int			in_shad(t_scene *sc, t_light *light, t_hit *hit);
t_vector	calc_light(t_closest *cl, t_scene *scene, t_ray *ray, t_hit *hit);
#endif
