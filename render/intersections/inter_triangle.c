#include "mini_rt.h"

void	inter_triangle(const t_triangle *s_triangle, t_ray *s_ray)
{
	float	det;
	float	a;
	float	b;
	t_vec	s_vec1;
	t_vec	s_vec2;

	s_vec1 = vec_cproduct(&s_ray->s_vec_start_dir, &s_triangle->s_vec_edge_2);
	det = 1 / vec_dot(&s_triangle->s_vec_edge_1, &s_vec1);
	s_vec2 = vec_sub(&s_ray->s_vec_start, &s_triangle->s_vec_o_1);
	a = vec_dot(&s_vec2, &s_vec1) * det;
	if (a < 0 || a > 1)
		return ;
	s_vec2 = vec_cproduct(&s_vec2, &s_triangle->s_vec_edge_1);
	b = vec_dot(&s_ray->s_vec_start_dir, &s_vec2) * det;
	det = vec_dot(&s_triangle->s_vec_edge_2, &s_vec2) * det;
	if (b < 0 || a + b > 1 || det <= MIN_DISTANCE || det >= s_ray->length)
		return ;
	add_inter_res(s_ray, inter_triangle, &s_triangle->s_material, det);
	s_ray->last_inter_obj = (void *)s_triangle;
	s_ray->last_inter_type = OBJ_TRIANGLE;
	s_ray->s_vec_inter_dir = s_triangle->s_vec_dir;
	if (vec_dot(&s_ray->s_vec_inter_dir, &s_ray->s_vec_start_dir) > 0)
		s_ray->s_vec_inter_dir = vec_mul(&s_ray->s_vec_inter_dir, -1);
}
