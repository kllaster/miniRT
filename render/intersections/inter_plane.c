#include "mini_rt.h"

void	inter_plane(const t_plane *s_plane, t_ray *s_ray)
{
	float	x;
	t_vec	s_vec1;

	if ((x = vec_dot(&s_ray->s_vec_start_dir, &s_plane->s_vec_dir)) == 0)
		return ;
	s_vec1 = vec_sub(&s_plane->s_vec_origin, &s_ray->s_vec_start);
	x = vec_dot(&s_vec1, &s_plane->s_vec_dir) / x;
	if (x <= MIN_DISTANCE || s_ray->length <= x)
		return ;
	add_inter_res(s_ray, &s_plane->s_material, x);
	s_ray->last_inter_obj = (void *)s_plane;
	s_ray->last_inter_type = OBJ_PLANE;
	s_ray->s_vec_inter_dir = s_plane->s_vec_dir;
	if (vec_dot(&s_ray->s_vec_inter_dir, &s_ray->s_vec_start_dir) > 0)
		s_ray->s_vec_inter_dir = vec_mul(&s_ray->s_vec_inter_dir, -1);
}
