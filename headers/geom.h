//
// Created by Howe Robbin on 1/28/21.
//

#ifndef GEOM_H
# define GEOM_H

float dot_prod(t_vector vector1, t_vector vector2);
float vector_length(t_vector v);
float v3_dist(t_vector v1, t_vector v2);
void normalize(t_vector *v);
t_vector v3_add(t_vector v1, t_vector v2);
t_vector v3_sub(t_vector v1, t_vector v2);
t_vector v3_cross(t_vector v1, t_vector v2);
t_vector v3_mult(t_vector v1, float num);
t_vector v_div_scal(t_vector v1, float num);
t_vector rgb_add(t_vector rgb, t_vector add);
t_vector rgb_add_n(t_vector rgb, float num);
t_vector rgb_mult_n(t_vector rgb, float num);
int		vec_cmp(t_vector v1, t_vector v2);
#endif //MINIRT_MATH_H
