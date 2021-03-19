#include "mini_rt.h"

t_vec	vec_norm(const t_vec *s_vec)
{
	t_vec	s_vec_norm;
	float	len;

	len = sqrtf(s_vec->x * s_vec->x + s_vec->y * s_vec->y +
									s_vec->z * s_vec->z);
	if (len != 1 && len != 0)
	{
		len = 1 / len;
		s_vec_norm.x = s_vec->x * len;
		s_vec_norm.y = s_vec->y * len;
		s_vec_norm.z = s_vec->z * len;
		return (s_vec_norm);
	}
	return (*s_vec);
}

int		vec_check_unzero(const t_vec *s_vec)
{
	return (s_vec->x || s_vec->y || s_vec->z);
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
