#include "mini_rt.h"

void 	inter_plane(t_plane *s_plane, t_ray *s_ray)
{
	float	x;
	t_ray	s_ray_inter;

	x = vec_scalar_mul(&s_ray->s_vec_start_dir, s_plane->s_vec_dir);
	if (ft_fabs(x) <= 0.0001)
		return ;
	s_ray_inter.s_vec_inter = vec_sub(s_plane->s_vec_origin, &s_ray->s_vec_start);
	x = vec_scalar_mul(&s_ray_inter.s_vec_inter, s_plane->s_vec_dir) / x;
	if (x <= 0.0001 || s_ray->length <= x)
		return ;
	s_ray_inter = *s_ray;
	s_ray_inter.length = x;
	s_ray_inter.s_color_obj = *s_plane->s_color;
	s_ray_inter.last_inter_obj = s_plane;
	s_ray_inter.last_inter_type = (unsigned)OBJ_PLANE;
	s_ray_inter.s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, x);
	s_ray_inter.s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray_inter.s_vec_inter);
	s_ray_inter.s_vec_inter_dir = *s_plane->s_vec_dir;
	*s_ray = s_ray_inter;
}