#include "mini_rt.h"

void		check_inter_obj(t_ray *s_ray)
{
	if (s_ray->last_inter_type & OBJ_SPHERE)
		inter_sphere(s_ray->last_inter_obj, s_ray);
	else if (s_ray->last_inter_type & OBJ_PLANE)
		inter_plane(s_ray->last_inter_obj, s_ray);
	else if (s_ray->last_inter_type & OBJ_SQUARE)
		inter_square(s_ray->last_inter_obj, s_ray);
//	else if (s_ray->last_inter_type & OBJ_CYLINDER)
//		inter_cylinder(s_ray->last_inter_obj, s_ray);
	else if (s_ray->last_inter_type & OBJ_TRIANGLE)
		inter_triangle(s_ray->last_inter_obj, s_ray);
}

void		check_inter_objs(t_list_objs *s_list_objs, t_ray *s_ray,
								float distance)
{
	t_list_objs	*s_list_obj;

	s_ray->length = distance;
	if (s_ray->last_inter_obj)
		check_inter_obj(s_ray);
	s_list_obj = s_list_objs;
	while (s_list_obj)
	{
		if (s_list_obj->type & OBJ_SPHERE)
			inter_sphere(s_list_obj->content, s_ray);
		else if (s_list_obj->type & OBJ_PLANE)
			inter_plane(s_list_obj->content, s_ray);
		else if (s_list_obj->type & OBJ_SQUARE)
			inter_square(s_list_obj->content, s_ray);
//		else if (s_list_obj->type & OBJ_CYLINDER)
//			inter_cylinder(s_list_obj->content, s_ray);
		else if (s_list_obj->type & OBJ_TRIANGLE)
			inter_triangle(s_list_obj->content, s_ray);
		s_list_obj = s_list_obj->next;
	}
	if (s_ray->length < distance && s_ray->last_inter_type ^ OBJ_PLANE &&
			s_ray->last_inter_type ^ OBJ_SQUARE &&
			s_ray->last_inter_type ^ OBJ_TRIANGLE)
		s_ray->s_vec_inter_dir = vec_norm(&s_ray->s_vec_inter_dir);
}

t_rgb		get_color_pixel(t_thread_data *s_thread_data, t_rays *s_rays)
{
	t_vec	s_vec_phong;
	t_rgb	s_color_res;
	t_rgb	s_color_ref;
	t_list	*s_list_light;
	float	light_length;

	s_color_res = (t_rgb){0, 0, 0};
	s_list_light = s_thread_data->s_list_lights;
	s_vec_phong = vec_sub(&s_rays->s_ray.s_vec_start,
							&s_rays->s_ray.s_vec_inter);
	s_vec_phong = vec_norm(&s_vec_phong);
	while (s_list_light)
	{
		s_rays->s_ray_light.s_vec_start = s_rays->s_ray.s_vec_inter;
		s_rays->s_ray_light.s_vec_start_dir =
				vec_sub(&((t_light *)s_list_light->content)->s_vec_origin,
							&s_rays->s_ray.s_vec_inter);
		light_length = vec_len(&s_rays->s_ray_light.s_vec_start_dir) -
							(float)MIN_DISTANCE;
		s_rays->s_ray_light.s_vec_start_dir =
					vec_norm(&s_rays->s_ray_light.s_vec_start_dir);
		check_inter_objs(s_thread_data->s_list_objs, &s_rays->s_ray_light, light_length);
		if (s_rays->s_ray_light.length == light_length)
			add_light_color(s_rays, &s_color_res,
								&((t_light *)s_list_light->content)->s_color,
								&s_vec_phong);
		s_list_light = s_list_light->next;
	}
	rgb_add_light(&s_color_res, &s_rays->s_ray.s_material->s_color,
					s_thread_data->s_ambient_color, 1);
	if (s_rays->s_ray.s_material->ref_coeff)
	{
		s_color_ref = reflection(s_thread_data, *s_rays);
		s_color_res = rgb_sum(&s_color_res, &s_color_ref);
	}
	return (s_color_res);
}

int			anti_aliasing(t_thread_data *s_thread_data, int x, int y,
							t_rays *s_rays)
{
	int		count_rays;
	t_rgb	s_color_res;
	t_rgb	s_color_ray;

	count_rays = 0;
	s_color_res = (t_rgb){0, 0, 0};
	s_rays->count_ref = -1;
	while (count_rays < ANTI_ALIASING)
	{
		s_rays->s_ray.s_vec_start_dir.x = (float)x + s_thread_data->s_aa_sample.matrix[count_rays][0] -
											s_thread_data->s_main_camera->s_vscreen.width;
		s_rays->s_ray.s_vec_start_dir.y = (float)-y + s_thread_data->s_aa_sample.matrix[count_rays][1] +
											s_thread_data->s_main_camera->s_vscreen.height;
		s_rays->s_ray.s_vec_start_dir.z = s_thread_data->s_main_camera->s_vscreen.z;
		s_rays->s_ray.s_vec_start_dir = matrix_mul(&s_rays->s_ray.s_vec_start_dir,
											 &s_thread_data->s_main_camera->s_matrix_rotate);
		s_rays->s_ray.s_vec_start_dir = vec_sub(&s_rays->s_ray.s_vec_start_dir,
												&s_rays->s_ray.s_vec_start);
		s_rays->s_ray.s_vec_start_dir = vec_norm(&s_rays->s_ray.s_vec_start_dir);
		check_inter_objs(s_thread_data->s_list_objs, &s_rays->s_ray, MAX_DISTANCE);
		if (s_rays->s_ray.length < MAX_DISTANCE)
			s_color_ray = get_color_pixel(s_thread_data, s_rays);
		else
			s_color_ray = (t_rgb){0, 0, 0};
		if (count_rays == 0)
			s_color_res = rgb_average(&s_color_ray, &s_color_res, 0);
		else
			s_color_res = rgb_average(&s_color_ray, &s_color_res, 1);
		++count_rays;
	}
	return (rgb_get_int(&s_color_res));
}

void		*render(void *data)
{
	int				x;
	int				y;
	int				color_pixel;
	t_rays			s_rays;
	t_thread_data	*s_thread_data;

	ft_bzero(&s_rays, sizeof(s_rays));
	s_thread_data = (t_thread_data *)data;
	s_rays.s_ray.s_vec_start = s_thread_data->s_main_camera->s_vec_origin;
	y = s_thread_data->start_y;
	while (y < s_thread_data->end_y)
	{
		x = 0;
		while (x < s_thread_data->s_screen.width)
		{
			color_pixel = anti_aliasing(s_thread_data, x, y, &s_rays);
			my_mlx_pixel_put(&s_thread_data->s_main_camera->s_mlx_img,
								x, y, color_pixel);
			++x;
		}
		++y;
	}
	return ((void *)"Ready");
}
