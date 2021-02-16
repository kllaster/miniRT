#include "mini_rt.h"

double	vector_len(t_coordinates *s_vector)
{
	return (sqrt(s_vector->x * s_vector->x + s_vector->y * s_vector->y + s_vector->z * s_vector->z));
}

t_coordinates	vector_norm(t_coordinates *s_vector)
{
	t_coordinates	s_vector_norm;
	double			len;

	len = vector_len(s_vector);
	s_vector_norm.x = s_vector->x / len;
	s_vector_norm.y = s_vector->y / len;
	s_vector_norm.z = s_vector->z / len;
	return (s_vector_norm);
}

t_coordinates	vector_sub(t_coordinates *s_vector_1, t_coordinates *s_vector_2)
{
	t_coordinates	s_vector_sub;

	s_vector_sub.x = s_vector_1->x - s_vector_2->x;
	s_vector_sub.y = s_vector_1->y - s_vector_2->y;
	s_vector_sub.z = s_vector_1->z - s_vector_2->z;
	return (s_vector_sub);
}

t_coordinates	vector_mul(t_coordinates *s_vector, float num)
{
	t_coordinates	s_vector_mul;

	s_vector_mul.x = s_vector->x * num;
	s_vector_mul.y = s_vector->y * num;
	s_vector_mul.z = s_vector->z * num;
	return (s_vector_mul);
}

double	vector_scalar_mul(t_coordinates *s_vector_1, t_coordinates *s_vector_2)
{
	return (s_vector_1->x * s_vector_2->x + s_vector_1->y * s_vector_2->y +
											s_vector_1->z * s_vector_2->z);
}