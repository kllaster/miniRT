#include "mini_rt.h"

void	inter_sphere(const t_sphere *s_sphere, t_ray *s_ray)
{
	float	b;
	float	c;
	float	x;
	t_vec	s_vec1;

	s_vec1 = vec_sub(&s_ray->s_vec_start, &s_sphere->s_vec_o);
	b = 2 * vec_dot(&s_vec1, &s_ray->s_vec_start_dir);
	if ((c = b * b - (4 * (vec_dot(&s_vec1, &s_vec1)
				- s_sphere->radius_pow))) < 0)
		return ;
	x = (float)((-b - sqrtf(c)) * 0.5);
	if (x <= MIN_DISTANCE)
		x = (float)((-b + sqrtf(c)) * 0.5);
	if (x <= MIN_DISTANCE || x >= s_ray->length)
		return ;
	add_inter_res(s_ray, inter_sphere, &s_sphere->s_material, x);
	s_ray->last_inter_obj = (void *)s_sphere;
	s_ray->last_inter_type = OBJ_SPHERE;
	s_ray->s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, x);
	s_ray->s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray->s_vec_inter);
	s_ray->s_vec_inter_dir = vec_sub(&s_ray->s_vec_inter, &s_sphere->s_vec_o);
	s_ray->s_vec_inter_dir = vec_norm(&s_ray->s_vec_inter_dir);
	if (c == -1)
		s_ray->s_vec_inter_dir = vec_mul(&s_ray->s_vec_inter_dir, -1);
}
