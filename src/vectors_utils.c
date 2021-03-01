#include "mini_rt.h"

int		vec_check_unzero(t_vec *s_vec)
{
	return (s_vec->x || s_vec->y || s_vec->z);
}

float	vec_len(t_vec *s_vec)
{
	return (sqrtf(s_vec->x * s_vec->x + s_vec->y * s_vec->y +
									s_vec->z * s_vec->z));
}

t_vec	vec_norm(t_vec *s_vec)
{
	t_vec	s_vec_norm;
	float	len;

	len = vec_len(s_vec);
	if (len != 1 && len != 0)
	{
		s_vec_norm.x = s_vec->x / len;
		s_vec_norm.y = s_vec->y / len;
		s_vec_norm.z = s_vec->z / len;
		return (s_vec_norm);
	}
	return (*s_vec);
}

t_vec	vec_sum(t_vec *s_vec_1, t_vec *s_vec_2)
{
	t_vec	s_vec_sub;

	s_vec_sub.x = s_vec_1->x + s_vec_2->x;
	s_vec_sub.y = s_vec_1->y + s_vec_2->y;
	s_vec_sub.z = s_vec_1->z + s_vec_2->z;
	return (s_vec_sub);
}

t_vec	vec_sub(t_vec *s_vec_1, t_vec *s_vec_2)
{
	t_vec	s_vec_sub;

	s_vec_sub.x = s_vec_1->x - s_vec_2->x;
	s_vec_sub.y = s_vec_1->y - s_vec_2->y;
	s_vec_sub.z = s_vec_1->z - s_vec_2->z;
	return (s_vec_sub);
}

t_vec	vec_mul(t_vec *s_vec, float num)
{
	t_vec	s_vec_mul;

	s_vec_mul.x = s_vec->x * num;
	s_vec_mul.y = s_vec->y * num;
	s_vec_mul.z = s_vec->z * num;
	return (s_vec_mul);
}

t_vec	vec_cross_product(t_vec *s_vec_1, t_vec *s_vec_2)
{
	t_vec	s_vec;

	s_vec.x = s_vec_1->z * s_vec_2->y - s_vec_1->y * s_vec_2->z;
	s_vec.y = s_vec_1->x * s_vec_2->z - s_vec_1->z * s_vec_2->x;
	s_vec.z = s_vec_1->y * s_vec_2->x - s_vec_1->x * s_vec_2->y;
	return (s_vec);
}

float	vec_scalar_mul(t_vec *s_vec_1, t_vec *s_vec_2)
{
	return (s_vec_1->x * s_vec_2->x + s_vec_1->y * s_vec_2->y +
											s_vec_1->z * s_vec_2->z);
}

void	vec_rotate_x(t_vec *s_vec, float sin, float cos)
{
	t_vec	s_vec_res;

	s_vec_res.x = s_vec->x;
	s_vec_res.y = s_vec->y * cos - s_vec->z * sin;
	s_vec_res.z = s_vec->y * sin + s_vec->z * cos;
	*s_vec = s_vec_res;
}

void	vec_rotate_y(t_vec *s_vec, float sin, float cos)
{
	t_vec	s_vec_res;

	s_vec_res.x = s_vec->x * cos + s_vec->z * sin;
	s_vec_res.y = s_vec->y;
	s_vec_res.z = s_vec->x * -sin + s_vec->z * cos;
	*s_vec = s_vec_res;
}

void	vec_rotate_z(t_vec *s_vec, float sin, float cos)
{
	t_vec	s_vec_res;

	s_vec_res.x = s_vec->x * cos - s_vec->y * sin;
	s_vec_res.y = s_vec->x * sin + s_vec->y * cos;
	s_vec_res.z = s_vec->z;
	*s_vec = s_vec_res;
}