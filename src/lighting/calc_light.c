/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:59:55 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:38:07 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		get_hit(t_hit *hit, t_closest *cl, t_ray *ray)
{
	hit->hit_dist = cl->cl_t * 0.99;
	hit->hit_pos = v3_add(ray->orig, v3_mult(ray->dir, hit->hit_dist));
	if (typecmp("sp", cl->cl_obj) || typecmp("cy", cl->cl_obj))
	{
		hit->hit_normal = v3_sub(hit->hit_pos, cl->cl_obj->orig);
		normalize(&hit->hit_normal);
	}
	else
	{
		if (dot_prod(ray->dir, cl->cl_obj->normal) > 0)
			hit->hit_normal = v3_mult(cl->cl_obj->normal, -1);
		else
			hit->hit_normal = cl->cl_obj->normal;
	}
}

float		l_shading(t_hit *hit, t_light *light)
{
	float		l_coef;
	float		l_intens;
	float		n_dot_l;
	t_vector	v_to_lght;

	l_coef = 0;
	v_to_lght = v3_sub(light->orig, hit->hit_pos);
	l_intens = light->ratio * 0.5;
	n_dot_l = dot_prod(hit->hit_normal, v_to_lght);
	if (n_dot_l > 0)
		l_coef += l_intens * n_dot_l /
				(vector_length(hit->hit_normal) * vector_length(v_to_lght));
	return (l_coef);
}

float		s_shading(t_hit *hit, t_light *light, t_ray *ray)
{
	float		coef;
	float		r_dot_v;
	t_vector	v_to_lght;
	t_vector	refl;
	t_vector	v;

	coef = 0;
	v_to_lght = v3_sub(light->orig, hit->hit_pos);
	refl = v3_mult(v3_mult(hit->hit_normal, 2),
					dot_prod(hit->hit_normal, v_to_lght));
	refl = v3_sub(refl, v_to_lght);
	v = v3_mult(ray->dir, -1);
	r_dot_v = dot_prod(refl, v);
	if (r_dot_v > 0)
		coef += light->ratio *
				powf(r_dot_v / (vector_length(refl) * vector_length(v)), 10);
	return (coef);
}

int			in_shad(t_scene *sc, t_light *light, t_hit *hit)
{
	t_closest	shadow;
	t_vector	v_to_light;
	t_ray		r_to_light;
	t_range		sh_range;

	sh_range.t_min = 0.0015;
	sh_range.t_max = v3_dist(hit->hit_pos, light->orig);
	v_to_light = v3_sub(light->orig, hit->hit_pos);
	r_to_light = set_ray(hit->hit_pos, v_to_light);
	cl_inter(&shadow, &r_to_light, sc->object, &sh_range);
	if (shadow.cl_obj)
		return (1);
	return (0);
}

t_vector	calc_light(t_closest *cl, t_scene *scene, t_ray *ray, t_hit *hit)
{
	t_vector	rgb;
	t_vector	temp;
	t_list		*light;
	float		coef;

	light = scene->light;
	get_hit(hit, cl, ray);
	rgb = rgb_mult_n(cl->cl_obj->rgb, scene->ambl.ratio);
	while (light)
	{
		if (in_shad(scene, light->content, hit))
		{
			light = light->next;
			continue;
		}
		coef = l_shading(hit, light->content);
		coef += s_shading(hit, light->content, ray);
		temp = rgb_mult_n(((t_light *)(light->content))->rgb, coef);
		rgb = rgb_add(rgb, temp);
		light = light->next;
	}
	return (rgb);
}
