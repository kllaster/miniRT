#include "mini_rt.h"

void 	inter_plane(t_plane *s_plane, t_ray *s_ray)
{
	double			x;
	t_ray			s_ray_inter;

	x = vector_scalar_mul(&s_ray->s_vector_start_normal, s_plane->s_angle);
	if (ft_dabs(x) <= 0.0001)
		return ;
	s_ray_inter.s_vector_inter = vector_sub(s_plane->s_coordinates, &s_ray->s_vector_start);
	x = vector_scalar_mul(&s_ray_inter.s_vector_inter, s_plane->s_angle) / x;
	if (x <= 0.0001 || s_ray->length <= x)
		return ;
	s_ray_inter = *s_ray;
	s_ray_inter.length = x;
	s_ray_inter.s_color_obj = *s_plane->s_color;
	s_ray_inter.s_vector_inter = vector_mul(&s_ray->s_vector_start_normal, x);
	s_ray_inter.s_vector_inter = vector_sum(&s_ray->s_vector_start, &s_ray_inter.s_vector_inter);
	s_ray_inter.s_vector_inter_normal = *s_plane->s_angle;
	*s_ray = s_ray_inter;
}