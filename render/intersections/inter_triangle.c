#include "mini_rt.h"

void 	inter_triangle(t_triangle *s_triangle, t_ray *s_ray)
{
	float	det;
	float	a;
	float	b;
	t_vec	s_vec_edge_1;
	t_vec	s_vec_edge_2;
	t_vec	s_vec_p;
	t_vec	s_vec_t;
	t_ray	s_ray_inter;

	s_vec_edge_1 = vec_sub(s_triangle->s_vec_origin_2, s_triangle->s_vec_origin_1);
	s_vec_edge_2 = vec_sub(s_triangle->s_vec_origin_3, s_triangle->s_vec_origin_1);
	s_vec_p = vec_cross_product(&s_ray->s_vec_start_dir, &s_vec_edge_2);
	det = vec_scalar_mul(&s_vec_edge_1, &s_vec_p);
	if (ft_fabs(det) < EPSILON)
		return ;
	det = 1 / det;
	s_vec_t = vec_sub(&s_ray->s_vec_start, s_triangle->s_vec_origin_1);
	a = vec_scalar_mul(&s_vec_t, &s_vec_p) * det;
	if (a < 0 || a > 1)
		return ;
	s_vec_t = vec_cross_product(&s_vec_t, &s_vec_edge_1);
	b = vec_scalar_mul(&s_ray->s_vec_start_dir, &s_vec_t) * det;
	if (b < 0 || a + b > 1)
		return ;
	det = vec_scalar_mul(&s_vec_edge_2, &s_vec_t) * det;
	if (det > s_ray->length)
		return ;
	s_ray_inter = *s_ray;
	s_ray_inter.length = det;
	s_ray_inter.s_color_obj = *s_triangle->s_color;
	s_ray_inter.last_inter_obj = s_triangle;
	s_ray_inter.last_inter_type = (unsigned)OBJ_TRIANGLE;
	s_ray_inter.s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, det);
	s_ray_inter.s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray_inter.s_vec_inter);
	s_ray_inter.s_vec_inter_dir = vec_cross_product(&s_vec_edge_1, &s_vec_edge_2);
	s_ray_inter.s_vec_inter_dir = vec_norm(&s_ray_inter.s_vec_inter_dir);
	*s_ray = s_ray_inter;
}