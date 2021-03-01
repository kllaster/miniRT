#include "mini_rt.h"

void 	inter_sphere(t_sphere *s_sphere, t_ray *s_ray)
{
	float	b;
	float	c;
	float	d_x;
	t_ray	s_ray_inter;

	s_ray_inter.s_vec_inter = vec_sub(&s_ray->s_vec_start, s_sphere->s_vec_origin);
	b = 2 * vec_scalar_mul(&s_ray_inter.s_vec_inter, &s_ray->s_vec_start_dir);
	c = vec_scalar_mul(&s_ray_inter.s_vec_inter, &s_ray_inter.s_vec_inter) -
		(s_sphere->radius * s_sphere->radius);
	d_x = b * b - (4 * c);
	if (d_x < 0)
		return ;
	d_x = (float)((-b - sqrtf(d_x)) * 0.5);
	if (d_x > EPSILON && d_x < s_ray->length)
	{
		s_ray_inter = *s_ray;
		s_ray_inter.length = d_x;
		s_ray_inter.s_color_obj = *s_sphere->s_color;
		s_ray_inter.last_inter_obj = s_sphere;
		s_ray_inter.last_inter_type = (unsigned)OBJ_SPHERE;
		s_ray_inter.s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, d_x);
		s_ray_inter.s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray_inter.s_vec_inter);
		s_ray_inter.s_vec_inter_dir = vec_sub(&s_ray_inter.s_vec_inter, s_sphere->s_vec_origin);
		*s_ray = s_ray_inter;
	}
}