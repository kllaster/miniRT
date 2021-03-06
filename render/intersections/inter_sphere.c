#include "mini_rt.h"

void 	inter_sphere(t_sphere *s_sphere, t_ray *s_ray)
{
	float	b;
	float	c;
	float	d_x;
	t_vec	s_vec1;

	s_vec1 = vec_sub(&s_ray->s_vec_start, s_sphere->s_vec_origin);
	b = 2 * vec_scalar_mul(&s_vec1, &s_ray->s_vec_start_dir);
	c = vec_scalar_mul(&s_vec1, &s_vec1) -
		(s_sphere->radius * s_sphere->radius);
	d_x = b * b - (4 * c);
	if (d_x < 0 || (d_x = (float)((-b - sqrtf(d_x)) * 0.5)) <= MIN_DISTANCE ||
		d_x >= s_ray->length)
		return ;
	s_ray->length = d_x;
	s_ray->s_color_obj = *s_sphere->s_color;
	s_ray->last_inter_obj = s_sphere;
	s_ray->last_inter_type = (unsigned)OBJ_SPHERE;
	s_ray->s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, d_x);
	s_ray->s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray->s_vec_inter);
	s_ray->s_vec_inter_dir = vec_sub(&s_ray->s_vec_inter, s_sphere->s_vec_origin);
}
