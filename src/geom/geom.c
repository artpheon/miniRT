//
// Created by Howe Robbin on 1/28/21.
//

#include "geom.h"

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
