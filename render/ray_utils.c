#include "mini_rt.h"

void	add_inter_res(t_ray *s_ray, void (*func_inter)(),
							const void *s_figure, float x)
{
	s_ray->length = x;
	s_ray->func_inter = func_inter;
	s_ray->last_inter_obj = (void *)s_figure;
	s_ray->s_material = s_figure;
}

void	get_vec_reflection(t_vec *s_vec_start_dir, t_vec *s_vec_dir)
{
	t_vec	s_vec;

	*s_vec_start_dir = vec_mul(s_vec_start_dir, -1);
	s_vec = vec_mul(s_vec_dir, 2 * vec_dot(s_vec_dir, s_vec_start_dir));
	*s_vec_start_dir = vec_sub(&s_vec, s_vec_start_dir);
	*s_vec_start_dir = vec_norm(s_vec_start_dir);
}

float	get_vec_light(t_ray *s_ray_light, t_vec *s_vec_inter,
						t_vec *s_vec_light)
{
	float length;

	s_ray_light->s_vec_start = *s_vec_inter;
	s_ray_light->s_vec_start_dir = vec_sub(s_vec_light, s_vec_inter);
	length = sqrtf(vec_dot(&s_ray_light->s_vec_start_dir,
							&s_ray_light->s_vec_start_dir)) -
			(float)MIN_DISTANCE;
	s_ray_light->s_vec_start_dir = vec_norm(&s_ray_light->s_vec_start_dir);
	return (length);
}

void	get_vec_start_dir(float x, float y, t_ray *s_ray, t_cam *s_cam)
{
	s_ray->s_vec_start_dir.x = x - s_cam->s_vscreen.width;
	s_ray->s_vec_start_dir.y = y + s_cam->s_vscreen.height;
	s_ray->s_vec_start_dir.z = s_cam->s_vscreen.z;
	s_ray->s_vec_start_dir = matrix_mul(&s_ray->s_vec_start_dir,
											&s_cam->s_matrix_rotate);
	s_ray->s_vec_start_dir = vec_sub(&s_ray->s_vec_start_dir,
										&s_ray->s_vec_start);
	s_ray->s_vec_start_dir = vec_norm(&s_ray->s_vec_start_dir);
}

void	get_aa_sample(int anti_aliasing, t_aa_sample *s_aa_sample)
{
	ft_bzero(s_aa_sample, sizeof(t_aa_sample));
	if (anti_aliasing == 1)
	{
		s_aa_sample->matrix[0][0] = (float)-0.45;
		s_aa_sample->matrix[0][1] = (float)0.45;
		s_aa_sample->matrix[1][0] = (float)-0.4;
		s_aa_sample->matrix[1][1] = (float)-0.45;
		s_aa_sample->matrix[2][0] = (float)-0.45;
		s_aa_sample->matrix[2][1] = (float)-0.4;
	}
}
