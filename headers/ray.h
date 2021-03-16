/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:43:17 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:43:21 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

int			ray_trace(t_ray *ray, t_scene *scene);
t_vector	multiply_by_matrix(t_vector p, t_matrix m);
t_matrix	look_at(t_vector origin, t_vector cam_vector);
t_vector	get_dir(t_camera *cam, t_scene *scene, int x, int y);
t_ray		gen_ray(int x, int y, t_scene *scene);
#endif
