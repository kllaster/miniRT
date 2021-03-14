#include "mini_rt.h"

void	resize_sphere(float *diameter, float *radius_pow, int *change_obj,
				   		float i)
{
	if (*diameter + i * CHANGING_SIZE < 1)
	{
		if (*diameter != 1)
			*diameter = 1;
		else
			return ;
	}
	else
		*diameter += i * CHANGING_SIZE;
	*radius_pow = *diameter * (float)0.5;
	*radius_pow *= *radius_pow;
	*change_obj = 1;
}

void	resize_square(float *side_size, float *side_half, int *change_obj,
				   		float i)
{
	if (*side_size + i * CHANGING_SIZE < 1)
	{
		if (*side_size != 1)
			*side_size = 1;
		else
			return ;
	}
	else
		*side_size += i * CHANGING_SIZE;
	*side_half = *side_size * (float)0.5;
	*change_obj = 1;
}

int		mouse_press(int button, int x, int y, t_rt *s_rt)
{
	float 	i;
	t_ray	s_ray;

	i = 1;
	if (s_rt->render_now || (button != BUTTON_1 && button != BUTTON_2))
		return (0);
	else if (button == BUTTON_2)
		i = -1;
	ft_bzero(&s_ray, sizeof(t_ray));
	s_ray.s_vec_start = s_rt->s_stage.s_main_camera->s_vec_origin;
	s_ray.s_vec_start_dir.x = (float)x -
								s_rt->s_stage.s_main_camera->s_vscreen.width;
	s_ray.s_vec_start_dir.y = (float)-y +
								s_rt->s_stage.s_main_camera->s_vscreen.height;
	s_ray.s_vec_start_dir.z = s_rt->s_stage.s_main_camera->s_vscreen.z;
	s_ray.s_vec_start_dir = matrix_mul(&s_ray.s_vec_start_dir,
							   &s_rt->s_stage.s_main_camera->s_matrix_rotate);
	s_ray.s_vec_start_dir = vec_sub(&s_ray.s_vec_start_dir,
										&s_ray.s_vec_start);
	s_ray.s_vec_start_dir = vec_norm(&s_ray.s_vec_start_dir);
	check_inter_objs(s_rt->s_stage.s_list_objs, &s_ray, MAX_DISTANCE);
	if (s_ray.length < MAX_DISTANCE)
	{
		if (s_ray.last_inter_type & OBJ_SPHERE)
			resize_sphere(&((t_sphere *)s_ray.last_inter_obj)->diameter,
						  	&((t_sphere *)s_ray.last_inter_obj)->radius_pow,
							&s_rt->change_obj, i);
		else if (s_ray.last_inter_type & OBJ_SQUARE)
			resize_square(&((t_square *)s_ray.last_inter_obj)->side_size,
				 			&((t_square *)s_ray.last_inter_obj)->side_half,
				 			&s_rt->change_obj, i);
	}
	return (0);
}

int		mouse_release(int button, int x, int y, t_rt *s_rt)
{
	if (button == BUTTON_1 || button == BUTTON_2)
		s_rt->change_obj = 0;
	(void)x;
	(void)y;
	return (0);
}