//
// Created by Howe Robbin on 3/13/21.
//

#ifndef LIGHTS_H
# define LIGHTS_H

void		get_hit(t_hit *hit, t_closest *cl, t_ray *ray);
float		l_shading(t_hit *hit, t_light *light);
float		s_shading(t_hit *hit, t_light *light, t_ray *ray);
int			in_shad(t_scene *sc, t_light *light, t_hit *hit);
t_vector	calc_light(t_closest *cl, t_scene *scene, t_ray *ray, t_hit *hit);

#endif //MINIRT_LIGHTS_H
