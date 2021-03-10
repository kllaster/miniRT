#include "mini_rt.h"

void	inter_plane(const t_plane *s_plane, t_ray *s_ray)
{
	float	x;
	t_vec	s_vec1;

	if ((x = vec_scalar_mul(&s_ray->s_vec_start_dir, &s_plane->s_vec_dir)) == 0)
		return ;
	s_vec1 = vec_sub(&s_plane->s_vec_origin, &s_ray->s_vec_start);
	x = vec_scalar_mul(&s_vec1, &s_plane->s_vec_dir) / x;
	if (x <= MIN_DISTANCE || s_ray->length <= x)
		return ;
	s_ray->length = x;
	s_ray->ref_coeff = s_plane->ref_coeff;
	s_ray->s_color_obj = s_plane->s_color;
	s_ray->last_inter_obj = (void *)s_plane;
	s_ray->last_inter_type = (unsigned)OBJ_PLANE;
	s_ray->s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, x);
	s_ray->s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray->s_vec_inter);
	s_ray->s_vec_inter_dir = s_plane->s_vec_dir;
}
