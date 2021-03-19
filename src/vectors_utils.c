#include "mini_rt.h"

t_vec	vec_sum(const t_vec *s_vec_1, const t_vec *s_vec_2)
{
	t_vec	s_vec_sub;

	s_vec_sub.x = s_vec_1->x + s_vec_2->x;
	s_vec_sub.y = s_vec_1->y + s_vec_2->y;
	s_vec_sub.z = s_vec_1->z + s_vec_2->z;
	return (s_vec_sub);
}

t_vec	vec_sub(const t_vec *s_vec_1, const t_vec *s_vec_2)
{
	t_vec	s_vec_sub;

	s_vec_sub.x = s_vec_1->x - s_vec_2->x;
	s_vec_sub.y = s_vec_1->y - s_vec_2->y;
	s_vec_sub.z = s_vec_1->z - s_vec_2->z;
	return (s_vec_sub);
}

t_vec	vec_mul(const t_vec *s_vec, float num)
{
	t_vec	s_vec_mul;

	s_vec_mul.x = s_vec->x * num;
	s_vec_mul.y = s_vec->y * num;
	s_vec_mul.z = s_vec->z * num;
	return (s_vec_mul);
}

t_vec	vec_cproduct(const t_vec *s_vec_1, const t_vec *s_vec_2)
{
	t_vec	s_vec;

	s_vec.x = s_vec_1->z * s_vec_2->y - s_vec_1->y * s_vec_2->z;
	s_vec.y = s_vec_1->x * s_vec_2->z - s_vec_1->z * s_vec_2->x;
	s_vec.z = s_vec_1->y * s_vec_2->x - s_vec_1->x * s_vec_2->y;
	return (s_vec);
}

float	vec_dot(const t_vec *s_vec_1, const t_vec *s_vec_2)
{
	return (s_vec_1->x * s_vec_2->x + s_vec_1->y * s_vec_2->y +
											s_vec_1->z * s_vec_2->z);
}
