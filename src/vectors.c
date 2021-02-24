#include "mini_rt.h"

double			vector_len(t_coordinates *s_vector)
{
	return (sqrt(s_vector->x * s_vector->x + s_vector->y * s_vector->y +
												s_vector->z * s_vector->z));
}

t_coordinates	vector_norm(t_coordinates *s_vector)
{
	t_coordinates	s_vector_norm;
	double			len;

	len = vector_len(s_vector);
	if (len != 1 && len != 0)
	{
		s_vector_norm.x = s_vector->x / len;
		s_vector_norm.y = s_vector->y / len;
		s_vector_norm.z = s_vector->z / len;
		return (s_vector_norm);
	}
	return (*s_vector);
}

t_coordinates	vector_sum(t_coordinates *s_vector_1, t_coordinates *s_vector_2)
{
	t_coordinates	s_vector_sub;

	s_vector_sub.x = s_vector_1->x + s_vector_2->x;
	s_vector_sub.y = s_vector_1->y + s_vector_2->y;
	s_vector_sub.z = s_vector_1->z + s_vector_2->z;
	return (s_vector_sub);
}

t_coordinates	vector_sub(t_coordinates *s_vector_1, t_coordinates *s_vector_2)
{
	t_coordinates	s_vector_sub;

	s_vector_sub.x = s_vector_1->x - s_vector_2->x;
	s_vector_sub.y = s_vector_1->y - s_vector_2->y;
	s_vector_sub.z = s_vector_1->z - s_vector_2->z;
	return (s_vector_sub);
}

t_coordinates	vector_mul(t_coordinates *s_vector, double num)
{
	t_coordinates	s_vector_mul;

	s_vector_mul.x = s_vector->x * num;
	s_vector_mul.y = s_vector->y * num;
	s_vector_mul.z = s_vector->z * num;
	return (s_vector_mul);
}

t_coordinates	vector_cross_product(t_coordinates *s_vector_1, t_coordinates *s_vector_2)
{
	t_coordinates p;

	p.x = s_vector_1->z * s_vector_2->y - s_vector_1->y * s_vector_2->z;
	p.y = s_vector_1->x * s_vector_2->z - s_vector_1->z * s_vector_2->x;
	p.z = s_vector_1->y * s_vector_2->x - s_vector_1->x * s_vector_2->y;
	return (p);
}

double			vector_scalar_mul(t_coordinates *s_vector_1, t_coordinates *s_vector_2)
{
	return (s_vector_1->x * s_vector_2->x + s_vector_1->y * s_vector_2->y +
											s_vector_1->z * s_vector_2->z);
}

void			rotate_vector_x(t_coordinates *s_vector, double sin, double cos)
{
	t_coordinates	s_vector_res;

	s_vector_res.x = s_vector->x;
	s_vector_res.y = s_vector->y * cos - s_vector->z * sin;
	s_vector_res.z = s_vector->y * sin + s_vector->z * cos;
	*s_vector = s_vector_res;
}

void			rotate_vector_y(t_coordinates *s_vector, double sin, double cos)
{
	t_coordinates	s_vector_res;

	s_vector_res.x = s_vector->x * cos + s_vector->z * sin;
	s_vector_res.y = s_vector->y;
	s_vector_res.z = s_vector->x * -sin + s_vector->z * cos;
	*s_vector = s_vector_res;
}

void			rotate_vector_z(t_coordinates *s_vector, double sin, double cos)
{
	t_coordinates	s_vector_res;

	s_vector_res.x = s_vector->x * cos - s_vector->y * sin;
	s_vector_res.y = s_vector->x * sin + s_vector->y * cos;
	s_vector_res.z = s_vector->z;
	*s_vector = s_vector_res;
}