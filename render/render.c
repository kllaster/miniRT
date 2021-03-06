#include "mini_rt.h"

void		check_inter_obj(t_ray *s_ray)
{
	if (s_ray->last_inter_type & (unsigned)OBJ_SPHERE)
		inter_sphere(s_ray->last_inter_obj, s_ray);
	else if (s_ray->last_inter_type & (unsigned)OBJ_PLANE)
		inter_plane(s_ray->last_inter_obj, s_ray);
	// else if (s_ray->last_inter_type & (unsigned)OBJ_SQUARE)
	// 	inter_square(s_ray->last_inter_obj, s_ray);
//	else if (s_ray->last_inter_type & (unsigned)OBJ_CYLINDER)
//		inter_cylinder(s_ray->last_inter_obj, s_ray);
	else if (s_ray->last_inter_type & (unsigned)OBJ_TRIANGLE)
		inter_triangle(s_ray->last_inter_obj, s_ray);
}

void		check_inter_objs(t_thread_data *s_thread_data, t_ray *s_ray, float distance)
{
	t_list_objs	*s_list_obj;

	s_ray->length = distance;
	if (s_ray->last_inter_obj)
		check_inter_obj(s_ray);
	s_list_obj = s_thread_data->s_list_objs;
	while (s_list_obj)
	{
		if (s_list_obj->type & (unsigned)OBJ_SPHERE)
			inter_sphere(s_list_obj->content, s_ray);
		else if (s_list_obj->type & (unsigned)OBJ_PLANE)
			inter_plane(s_list_obj->content, s_ray);
		// else if (s_list_obj->type & (unsigned)OBJ_SQUARE)
		// 	inter_square(s_list_obj->content, s_ray);
//		else if (s_list_obj->type & (unsigned)OBJ_CYLINDER)
//			inter_cylinder(s_list_obj->content, s_ray);
		else if (s_list_obj->type & (unsigned)OBJ_TRIANGLE)
			inter_triangle(s_list_obj->content, s_ray);
		s_list_obj = s_list_obj->next;
	}
	if (s_ray->length < distance && s_ray->last_inter_type ^ (unsigned)OBJ_PLANE
									&& s_ray->last_inter_type ^ (unsigned)OBJ_TRIANGLE)
		s_ray->s_vec_inter_dir = vec_norm(&s_ray->s_vec_inter_dir);
}

t_rgb		get_color_pixel(t_thread_data *s_thread_data, t_rays *s_rays)
{
	t_vec	s_vec_halfway;
	t_rgb	s_color_res;
	t_list	*s_list_light;
	float	light_length;
	float	angel_incidence;

	s_color_res = (t_rgb){0,0,0};
	s_list_light = s_thread_data->s_list_lights;
	if (vec_scalar_mul(&s_rays->s_ray.s_vec_inter_dir, &s_rays->s_ray.s_vec_start_dir) > 0)
		s_rays->s_ray.s_vec_inter_dir = vec_mul(&s_rays->s_ray.s_vec_inter_dir, -1);
	while (s_list_light)
	{
		s_rays->s_ray_light.s_vec_start = s_rays->s_ray.s_vec_inter;
		s_rays->s_ray_light.s_vec_start_dir = vec_sub(((t_light *)s_list_light->content)->s_vec_origin, &s_rays->s_ray.s_vec_inter);
		light_length = vec_len(&s_rays->s_ray_light.s_vec_start_dir);
		s_vec_halfway = s_rays->s_ray_light.s_vec_start_dir = vec_norm(&s_rays->s_ray_light.s_vec_start_dir);
		check_inter_objs(s_thread_data, &s_rays->s_ray_light, light_length);
		if (s_rays->s_ray_light.length == light_length)
		{
			if ((angel_incidence = vec_scalar_mul(&s_rays->s_ray_light.s_vec_start_dir,
												  &s_rays->s_ray.s_vec_inter_dir)) > 0)
			{
				rgb_add_light(&s_color_res, &s_rays->s_ray.s_color_obj,
					((t_light *)s_list_light->content)->s_color,
					angel_incidence * ((t_light *)s_list_light->content)->brightness);
				// Blinn–Phong
				s_rays->s_ray_light.s_vec_start_dir = vec_sub(&s_rays->s_ray.s_vec_start,
												  &s_rays->s_ray.s_vec_inter);
				s_rays->s_ray_light.s_vec_start_dir = vec_norm(&s_rays->s_ray_light.s_vec_start_dir);
				s_vec_halfway = vec_sum(&s_vec_halfway, &s_rays->s_ray_light.s_vec_start_dir);
				s_vec_halfway = vec_norm(&s_vec_halfway);
				if ((angel_incidence = vec_scalar_mul(&s_vec_halfway,
													  &s_rays->s_ray.s_vec_inter_dir)) > 0)
				{
					angel_incidence = (float)pow(angel_incidence, 60);
					rgb_add_light(&s_color_res, &s_rays->s_ray.s_color_obj,
						((t_light *)s_list_light->content)->s_color,
						angel_incidence * ((t_light *)s_list_light->content)->brightness);
				}
			}
		}
		s_list_light = s_list_light->next;
	}
	rgb_add_light(&s_color_res, &s_rays->s_ray.s_color_obj,
				  s_thread_data->s_ambient_light.s_color,
				  s_thread_data->s_ambient_light.brightness);
	return (s_color_res);
}

int			anti_aliasing(t_thread_data *s_thread_data, int x, int y, t_rays *s_rays)
{
	int		count_rays;
	t_rgb	s_color_res;
	t_rgb	s_color_ray;

	count_rays = 0;
	s_color_res = (t_rgb){0,0,0};
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
										  s_thread_data->s_main_camera->s_vec_origin);
		s_rays->s_ray.s_vec_start_dir = vec_norm(&s_rays->s_ray.s_vec_start_dir);
		check_inter_objs(s_thread_data, &s_rays->s_ray, MAX_DISTANCE);
		if (s_rays->s_ray.length < MAX_DISTANCE)
			s_color_ray = get_color_pixel(s_thread_data, s_rays);
		else
			s_color_ray = (t_rgb){0,0,0};
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
	s_rays.s_ray.s_vec_start = *s_thread_data->s_main_camera->s_vec_origin;
	x = s_thread_data->start_x;
	while (x < s_thread_data->end_x)
	{
		y = 0;
		while (y < s_thread_data->s_screen.height)
		{
			color_pixel = anti_aliasing(s_thread_data, x, y, &s_rays);
			my_mlx_pixel_put(&s_thread_data->s_main_camera->s_mlx_img,
							 								x, y, color_pixel);
			++y;
		}
		++x;
	}
	return ((void *)"Ready");
}
