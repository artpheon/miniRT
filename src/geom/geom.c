//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

float scalar_prod(t_vector vector1, t_vector vector2)
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

	x = powf(v.x, 2);
	y = powf(v.y, 2);
	z = powf(v.z, 2);
	return (sqrtf(x + y + z));
}

t_vector norm_vector(t_vector v)
{
	float length;
	t_vector normalized;

	length = vector_length(v);
	normalized.x = v.x / length;
	normalized.y = v.y / length;
	normalized.z = v.z / length;
	return (normalized);
}

t_vector vector_add(t_vector v1, t_vector v2)
{
	t_vector sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;
	return (sum);
}

t_vector vector_sub(t_vector v1, t_vector v2)
{
	t_vector diff;

	diff.x = v1.x - v2.x;
	diff.y = v1.y - v2.y;
	diff.z = v1.z - v2.z;
	return (diff);
}

t_vector vector_prod(t_vector v1, t_vector v2)
{
	t_vector prod;

	prod.x = (v1.y * v2.z) - (v1.z * v2.y);
	prod.y = (v1.z * v2.x) - (v1.x * v2.z);
	prod.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (prod);
}

t_vector v_mult_scal(t_vector v1, float num)
{
	t_vector new;

	new.x = v1.x * num;
	new.y = v1.y * num;
	new.z = v1.z * num;
	return (new);
}

t_vector v_div_scal(t_vector v1, float num)
{
	t_vector new;

	new.x = v1.x / num;
	new.y = v1.y / num;
	new.z = v1.z / num;
	return (new);
}
