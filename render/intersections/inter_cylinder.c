#include "mini_rt.h"

void	inter_cylinder_res(const t_cylinder *s_cylinder, t_ray *s_ray,
							float x[2])
{
	add_inter_res(s_ray, inter_cylinder, s_cylinder, x[0]);
	s_ray->last_inter_type = OBJ_CYLINDER;
	s_ray->s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, x[0]);
	s_ray->s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray->s_vec_inter);
	s_ray->s_vec_inter_dir = vec_sub(&s_ray->s_vec_inter, &s_cylinder->s_vec_o);
	s_ray->s_vec_inter_dir = vec_cproduct(&s_ray->s_vec_inter_dir,
											&s_cylinder->s_vec_dir);
	s_ray->s_vec_inter_dir = vec_cproduct(&s_cylinder->s_vec_dir,
											&s_ray->s_vec_inter_dir);
	s_ray->s_vec_inter_dir = vec_norm(&s_ray->s_vec_inter_dir);
	if (vec_dot(&s_ray->s_vec_inter_dir, &s_ray->s_vec_start_dir) > 0)
		s_ray->s_vec_inter_dir = vec_mul(&s_ray->s_vec_inter_dir, -1);
}

void	inter_cylinder_calc(const t_cylinder *s_cylinder, t_ray *s_ray,
								float x[2], t_vec *s_vec_co)
{
	float	a;
	float	b;
	float	c;
	t_vec	s_vec[3];

	s_vec[1] = vec_mul(&s_cylinder->s_vec_dir, x[0]);
	s_vec[2] = vec_mul(&s_cylinder->s_vec_dir, x[1]);
	c = vec_dot(s_vec_co, &s_cylinder->s_vec_dir);
	a = vec_dot(&s_ray->s_vec_start_dir, &s_vec[1]) + c;
	b = vec_dot(&s_ray->s_vec_start_dir, &s_vec[2]) + c;
	if (ft_fabs(a) >= s_cylinder->height_half)
		x[0] = -1;
	if (ft_fabs(b) >= s_cylinder->height_half)
		x[1] = -1;
	if (x[0] > MIN_DISTANCE && x[1] > MIN_DISTANCE)
		x[0] = x[0] > x[1] ? x[1] : x[0];
	else if (x[0] > MIN_DISTANCE || x[1] > MIN_DISTANCE)
		x[0] = x[0] > x[1] ? x[0] : x[1];
	else
		return ;
	if (x[0] > s_ray->length)
		return ;
	inter_cylinder_res(s_cylinder, s_ray, x);
}

void	inter_cylinder(const t_cylinder *s_cylinder, t_ray *s_ray)
{
	float	x[2];
	float	abc[3];
	float	det;
	t_vec	s_vec_co;

	s_vec_co = vec_sub(&s_ray->s_vec_start, &s_cylinder->s_vec_o);
	abc[0] = vec_dot(&s_ray->s_vec_start_dir, &s_cylinder->s_vec_dir);
	abc[1] = -(2 * (vec_dot(&s_vec_co, &s_cylinder->s_vec_dir) * abc[0] -
				vec_dot(&s_ray->s_vec_start_dir, &s_vec_co)));
	abc[0] = -((abc[0] * abc[0]) - 1);
	abc[2] = vec_dot(&s_vec_co, &s_vec_co) -
				powf(vec_dot(&s_cylinder->s_vec_dir, &s_vec_co), 2) -
				s_cylinder->radius_pow;
	det = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (det < 0)
		return ;
	x[0] = (-abc[1] - sqrtf(det)) / (abc[0] * 2);
	x[1] = (-abc[1] + sqrtf(det)) / (abc[0] * 2);
	inter_cylinder_calc(s_cylinder, s_ray, x, &(s_vec_co));
}
