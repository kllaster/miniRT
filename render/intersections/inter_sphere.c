#include "mini_rt.h"

void 	inter_sphere(t_sphere *s_sphere, t_ray *s_ray)
{
	double			b;
	double			c;
	double			d_x;
	t_ray			s_ray_inter;

	s_ray_inter.s_vector_inter = vector_sub(&s_ray->s_vector_start, s_sphere->s_coordinates);
	b = 2 * vector_scalar_mul(&s_ray_inter.s_vector_inter, &s_ray->s_vector_start_normal);
	c = vector_scalar_mul(&s_ray_inter.s_vector_inter, &s_ray_inter.s_vector_inter) -
		(s_sphere->radius * s_sphere->radius);
	d_x = b * b - (4 * c);
	if (d_x < 0)
		return ;
	d_x = (-b - sqrt(d_x)) / 2;
	if (d_x >= 0.0001 && d_x < s_ray->length)
	{
		s_ray_inter = *s_ray;
		s_ray_inter.length = d_x;
		s_ray_inter.s_color_obj = *s_sphere->s_color;
		s_ray_inter.s_vector_inter = vector_mul(&s_ray->s_vector_start_normal, d_x);
		s_ray_inter.s_vector_inter = vector_sum(&s_ray->s_vector_start, &s_ray_inter.s_vector_inter);
		s_ray_inter.s_vector_inter_normal = vector_sub(&s_ray_inter.s_vector_inter, s_sphere->s_coordinates);
		*s_ray = s_ray_inter;
	}
}