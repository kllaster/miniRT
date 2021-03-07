#include "mini_rt.h"

void	inter_triangle(const t_triangle *s_triangle, t_ray *s_ray)
{
	float	det;
	float	a;
	float	b;
	t_vec	s_vec1;
	t_vec	s_vec2;

	s_vec1 = vec_cross_product(&s_ray->s_vec_start_dir, &s_triangle->s_vec_edge_2);
	det = vec_scalar_mul(&s_triangle->s_vec_edge_1, &s_vec1);
	det = 1 / det;
	s_vec2 = vec_sub(&s_ray->s_vec_start, &s_triangle->s_vec_origin_1);
	a = vec_scalar_mul(&s_vec2, &s_vec1) * det;
	if (a < 0 || a > 1)
		return ;
	s_vec2 = vec_cross_product(&s_vec2, &s_triangle->s_vec_edge_1);
	b = vec_scalar_mul(&s_ray->s_vec_start_dir, &s_vec2) * det;
	det = vec_scalar_mul(&s_triangle->s_vec_edge_2, &s_vec2) * det;
	if (b < 0 || a + b > 1 || det <= MIN_DISTANCE || det >= s_ray->length)
		return ;
	s_ray->length = det;
	s_ray->s_color_obj = s_triangle->s_color;
	s_ray->last_inter_obj = (void *)s_triangle;
	s_ray->last_inter_type = (unsigned)OBJ_TRIANGLE;
	s_ray->s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, det);
	s_ray->s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray->s_vec_inter);
	s_ray->s_vec_inter_dir = s_triangle->s_vec_dir;
}
