#include "mini_rt.h"

int	mouse_press(int button, int x, int y, t_rt *s_rt)
{
	float 	i;
	t_ray	s_ray;

	i = 1;
	if (button != BUTTON_1 && button != BUTTON_2)
		return (0);
	else if (button == BUTTON_2)
		i = -1;
	ft_bzero(&s_ray, sizeof(t_ray));
	s_ray.s_vec_start = s_rt->s_stage.s_main_camera->s_vec_origin;
	s_ray.s_vec_start_dir.x = (float)x - s_rt->s_stage.s_main_camera->s_vscreen.width;
	s_ray.s_vec_start_dir.y = (float)-y + s_rt->s_stage.s_main_camera->s_vscreen.height;
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
		{
			if (((t_sphere *)s_ray.last_inter_obj)->diameter + i * CHANGING_SIZE < 0)
				return (0);
			((t_sphere *)s_ray.last_inter_obj)->diameter += i * CHANGING_SIZE;
			((t_sphere *)s_ray.last_inter_obj)->radius_pow =
					((t_sphere *)s_ray.last_inter_obj)->diameter * (float)0.5;
			((t_sphere *)s_ray.last_inter_obj)->radius_pow *=
					((t_sphere *)s_ray.last_inter_obj)->radius_pow;
			s_rt->change_obj = 1;
		}
	}
	return (0);
}