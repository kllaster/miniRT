#include "mini_rt.h"

void	resize_sphere(t_sphere *s_sphere, int *change_obj, float i)
{
	if (s_sphere->diameter + i < 1)
	{
		if (s_sphere->diameter != 1)
			s_sphere->diameter = 1;
		else
			return ;
	}
	else
		s_sphere->diameter += i;
	s_sphere->radius_pow = s_sphere->diameter * (float)0.5;
	s_sphere->radius_pow *= s_sphere->radius_pow;
	*change_obj = 1;
}

void	resize_square(t_square *s_square, int *change_obj, float i)
{
	if (s_square->side_size + i < 1)
	{
		if (s_square->side_size != 1)
			s_square->side_size = 1;
		else
			return ;
	}
	else
		s_square->side_size += i;
	s_square->side_half = s_square->side_size * (float)0.5;
	*change_obj = 1;
}

void	resize_cylinder(t_cylinder *s_cylinder, int *change_obj, float i)
{
	if (s_cylinder->diameter + i < 1)
	{
		if (s_cylinder->diameter != 1)
			s_cylinder->diameter = 1;
	}
	else
		s_cylinder->diameter += i;
	if (s_cylinder->height + i < 1)
	{
		if (s_cylinder->height != 1)
			s_cylinder->height = 1;
	}
	else
		s_cylinder->height += i;
	s_cylinder->radius_pow = s_cylinder->diameter * (float)0.5;
	s_cylinder->radius_pow *= s_cylinder->radius_pow;
	s_cylinder->height_half = s_cylinder->height * (float)0.5;
	*change_obj = 1;
}

void	check_click_figure(float i, t_ray *s_ray, t_rt *s_rt)
{
	if (s_ray->length < MAX_DISTANCE)
	{
		if (s_ray->last_inter_type & OBJ_SPHERE)
			resize_sphere((t_sphere *)s_ray->last_inter_obj,
							&s_rt->change_obj, i);
		else if (s_ray->last_inter_type & OBJ_SQUARE)
			resize_square((t_square *)s_ray->last_inter_obj,
							&s_rt->change_obj, i);
		else if (s_ray->last_inter_type & OBJ_CYLINDER)
			resize_cylinder((t_cylinder *)s_ray->last_inter_obj,
							&s_rt->change_obj, i);
	}
}

int		mouse_press(int button, int x, int y, t_rt *s_rt)
{
	float			i;
	static int		init = 0;
	static t_ray	s_ray;

	i = 1;
	if (s_rt->render_now || s_rt->change_obj ||
		(button != BUTTON_1 && button != BUTTON_2))
		return (0);
	else if (button == BUTTON_2)
		i = -1;
	if (init == 0 && (init = 1))
		ft_bzero(&s_ray, sizeof(t_ray));
	s_ray.s_vec_start = s_rt->s_stage.s_main_cam->s_vec_o;
	get_vec_start_dir((float)x, (float)-y, &s_ray, s_rt->s_stage.s_main_cam);
	check_inter_objs(s_rt->s_stage.s_lst_objs, &s_ray, MAX_DISTANCE);
	check_click_figure(i * CHANGING_SIZE, &s_ray, s_rt);
	return (0);
}
