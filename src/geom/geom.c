//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

float dot_prod(t_vector vector1, t_vector vector2) /* scalar product, dot product */
{
	return (vector1.x * vector2.x +
			vector1.y * vector2.y +
			vector1.z * vector2.z);
}

float vector_length(t_vector v)
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

float v3_dist(t_vector v1, t_vector v2)
{
	float res;

	res = powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2) + powf(v1.z - v2.z, 2);
	res = sqrtf(res);
	return (res);
}

void normalize(t_vector *v)
{
	float length;

	length = vector_length(*v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

t_vector v3_add(t_vector v1, t_vector v2)
{
	t_vector sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

t_vector v3_sub(t_vector v1, t_vector v2)
{
	t_vector diff;

	diff.x = v1.x - v2.x;
	diff.y = v1.y - v2.y;
	diff.z = v1.z - v2.z;
	return (diff);
}

t_vector v3_cross(t_vector v1, t_vector v2)
{
	t_vector prod;

	prod.x = (v1.y * v2.z) - (v1.z * v2.y);
	prod.y = (v1.z * v2.x) - (v1.x * v2.z);
	prod.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (prod);
}

t_vector v3_mult(t_vector v1, float num)
{
	t_vector new;

	new.x = v1.x * num;
	new.y = v1.y * num;
	new.z = v1.z * num;
	return (new);
}

t_vector v3_div(t_vector v1, float num)
{
	t_vector new;

	new.x = v1.x / num;
	new.y = v1.y / num;
	new.z = v1.z / num;
	return (new);
}

t_vector rgb_add_n(t_vector rgb, float num)
{
	rgb.x += num;
	rgb.y += num;
	rgb.z += num;
	if (rgb.x > 255)
		rgb.x = 255;
	if (rgb.y > 255)
		rgb.y = 255;
	if (rgb.z > 255)
		rgb.z = 255;
	return (rgb);
}

t_vector rgb_mult_n(t_vector rgb, float num)
{
	rgb.x *= num;
	rgb.y *= num;
	rgb.z *= num;
	if (rgb.x > 255)
		rgb.x = 255;
	if (rgb.y > 255)
		rgb.y = 255;
	if (rgb.z > 255)
		rgb.z = 255;
	return (rgb);
}

t_vector rgb_add(t_vector rgb, t_vector add)
{
	rgb.x += add.x;
	if (rgb.x > 255)
		rgb.x = 255;
	rgb.y += add.y;
	if (rgb.y > 255)
		rgb.y = 255;
	rgb.z += add.z;
	if (rgb.z > 255)
		rgb.z = 255;
	return (rgb);
}

int		vec_cmp(t_vector v1, t_vector v2)
{
	if (v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z)
		return (1);
	return (0);
}