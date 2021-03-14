#include "mini_rt.h"

void	inter_square(const t_square *s_square, t_ray *s_ray)
{
	float		x;
	t_vec		s_vec1;
	t_matrix	s_matrix;

	if ((x = vec_dot(&s_ray->s_vec_start_dir, &s_square->s_vec_dir)) == 0)
		return ;
	s_vec1 = vec_sub(&s_square->s_vec_origin, &s_ray->s_vec_start);
	x = vec_dot(&s_vec1, &s_square->s_vec_dir) / x;
	if (x <= MIN_DISTANCE || s_ray->length <= x)
		return ;
	s_vec1 = vec_mul(&s_ray->s_vec_start_dir, x);
	s_vec1 = vec_sum(&s_ray->s_vec_start, &s_vec1);
	s_vec1 = vec_sub(&s_vec1, &s_square->s_vec_origin);
	s_matrix = get_matrix_rotate((t_vec *)&s_square->s_vec_origin,
							  		(t_vec *)&s_square->s_vec_dir);
	if (ft_fabs(vec_dot((t_vec *)&(s_matrix.el[0]), &s_vec1)) >
			s_square->side_size * 0.5 ||
			ft_fabs(vec_dot((t_vec *)&(s_matrix.el[1]), &s_vec1)) >
			s_square->side_size * 0.5)
		return ;
	add_inter_res(s_ray, &s_square->s_material, x);
	s_ray->last_inter_obj = (void *)s_square;
	s_ray->last_inter_type = OBJ_SQUARE;
	s_ray->s_vec_inter_dir = s_square->s_vec_dir;
	if (vec_dot(&s_ray->s_vec_inter_dir, &s_ray->s_vec_start_dir) > 0)
		s_ray->s_vec_inter_dir = vec_mul(&s_ray->s_vec_inter_dir, -1);
}
