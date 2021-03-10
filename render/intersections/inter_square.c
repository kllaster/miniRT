#include "mini_rt.h"

void	inter_square(const t_square *s_square, t_ray *s_ray)
{
	float	x;
	float	a;
	t_vec	s_vec1;

	s_vec1 = vec_sub(&s_ray->s_vec_start, &s_square->s_vec_origin);
	x = vec_scalar_mul(&s_vec1, &s_square->s_vec_dir);
	a = vec_scalar_mul(&s_ray->s_vec_start_dir, &s_square->s_vec_dir);
	if (a == 0 || (x < 0 && a < 0) || (x > 0 && a > 0) ||
		(x = -x / a) <= MIN_DISTANCE || s_ray->length <= x)
		return ;
	s_vec1 = vec_mul(&s_ray->s_vec_start_dir, x);
	s_vec1 = vec_sum(&s_vec1, &s_ray->s_vec_start);
	s_vec1 = vec_sub(&s_vec1, &s_square->s_vec_origin);
	a = (float)(s_square->side_size * 0.5);
	if (ft_fabs(s_vec1.x) > a ||
			ft_fabs(s_vec1.y) > a || ft_fabs(s_vec1.z) > a)
		return ;
	s_ray->length = x;
	s_ray->ref_coeff = s_square->ref_coeff;
	s_ray->s_color_obj = s_square->s_color;
	s_ray->last_inter_obj = (void *)s_square;
	s_ray->last_inter_type = (unsigned)OBJ_SQUARE;
	s_ray->s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, x);
	s_ray->s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray->s_vec_inter);
	s_ray->s_vec_inter_dir = s_square->s_vec_dir;
}
