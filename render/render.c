#include "mini_rt.h"

void		check_inter_objs(t_thread_data *s_thread_data, t_ray *s_ray, double distance)
{
	t_list_objs	*s_list_obj;

	s_ray->length = distance;
	s_list_obj = s_thread_data->s_list_objs;
	while (s_list_obj)
	{
		if (s_list_obj->type & (unsigned)OBJ_SPHERE)
			inter_sphere(s_list_obj->content, s_ray);
		else if (s_list_obj->type & (unsigned)OBJ_PLANE)
			inter_plane(s_list_obj->content, s_ray);
//		else if (s_list_obj->type & (unsigned)OBJ_SQUARE)
//			inter_square(s_list_obj->content);
//		else if (s_list_obj->type & (unsigned)OBJ_CYLINDER)
//			inter_cylinder(s_list_obj->content);
//		else if (s_list_obj->type & (unsigned)OBJ_TRIANGLE)
//			inter_triangle(s_list_obj->content);
		s_list_obj = s_list_obj->next;
	}
	if (s_ray->length < distance)
        s_ray->s_vec_inter_dir = vec_norm(&s_ray->s_vec_inter_dir);
}

t_rgb		get_color_pixel(t_thread_data *s_thread_data, t_ray *s_ray)
{
	t_ray	s_light_ray;
	t_rgb	s_color_res;
    t_list	*s_list_light;
    double	light_length;
    double	angel_incidence;

	s_color_res = (t_rgb){0,0,0};
	s_list_light = s_thread_data->s_list_lights;
    if (vec_scalar_mul(&s_ray->s_vec_inter_dir, &s_ray->s_vec_start_dir) > 0)
		s_ray->s_vec_inter_dir = vec_mul(&s_ray->s_vec_inter_dir, -1);
	while (s_list_light)
    {
		s_light_ray.s_vec_start = s_ray->s_vec_inter;
        s_light_ray.s_vec_start_dir = vec_sub(((t_light *)s_list_light->content)->s_vec_origin, &s_ray->s_vec_inter);
        light_length = vec_len(&s_light_ray.s_vec_start_dir);
        s_light_ray.s_vec_start_dir = vec_norm(&s_light_ray.s_vec_start_dir);
        check_inter_objs(s_thread_data, &s_light_ray, light_length);
		if (s_light_ray.length == light_length)
        {
			angel_incidence = vec_scalar_mul(&s_light_ray.s_vec_start_dir,
												&s_ray->s_vec_inter_dir);
			if (angel_incidence > 0)
            {
				rgb_add_light(&s_color_res, &s_ray->s_color_obj,
				  ((t_light *)s_list_light->content)->s_color,
	  		angel_incidence * ((t_light *)s_list_light->content)->brightness);
            }
        }
        s_list_light = s_list_light->next;
    }
	rgb_add_light(&s_color_res, &s_ray->s_color_obj,
				  s_thread_data->s_ambient_light.s_color,
				  s_thread_data->s_ambient_light.brightness);
	return (s_color_res);
}

t_rgb		start_ray(t_thread_data *s_thread_data, t_ray *s_ray)
{
	check_inter_objs(s_thread_data, s_ray, MAX_DISTANCE);
	if (s_ray->length < MAX_DISTANCE)
		return (get_color_pixel(s_thread_data, s_ray));
	return ((t_rgb){0,0,0});
}

void		get_norm_start_ray(double x, double y, t_vec *s_vec_start_dir, t_camera *s_camera)
{
	s_vec_start_dir->x = x - s_camera->s_vscreen.width;
	s_vec_start_dir->y = -y + s_camera->s_vscreen.height;
	s_vec_start_dir->z = s_camera->s_vscreen.z;
	*s_vec_start_dir = matrix_mul(s_vec_start_dir, &s_camera->s_matrix_rotate);
	*s_vec_start_dir = vec_sub(s_vec_start_dir, s_camera->s_vec_origin);
	*s_vec_start_dir = vec_norm(s_vec_start_dir);
}

int			anti_aliasing(t_thread_data *s_thread_data, int x, int y, t_ray *s_ray)
{
	int		count_rays;
	t_rgb	s_color_res;
	t_rgb	s_color_ray;

	count_rays = 0;
	s_color_res = (t_rgb){0,0,0};
	while (count_rays < ANTI_ALIASING)
	{
		get_norm_start_ray(x + s_thread_data->s_aa_sample.matrix[count_rays][0],
						y + s_thread_data->s_aa_sample.matrix[count_rays][1],
						&s_ray->s_vec_start_dir, s_thread_data->s_selected_camera);
		s_color_ray = start_ray(s_thread_data, s_ray);
		if (count_rays == 0)
			s_color_res = rgb_average(&s_color_ray, &s_color_res, 0);
		else
			s_color_res = rgb_average(&s_color_ray, &s_color_res, 1);
		count_rays++;
	}
	return (rgb_get_int(&s_color_res));
}

void		*render(void *data)
{
	int				x;
	int				y;
	int				color_pixel;
	t_ray			s_ray;
	t_thread_data	*s_thread_data;

	s_thread_data = (t_thread_data *)data;
	x = s_thread_data->start_x;
	s_ray.s_vec_start = *s_thread_data->s_selected_camera->s_vec_origin;
	while (x < s_thread_data->end_x)
	{
		y = 0;
		while (y < s_thread_data->s_screen.height)
		{
			color_pixel = anti_aliasing(s_thread_data, x, y, &s_ray);
			my_mlx_pixel_put(&s_thread_data->s_selected_camera->s_mlx_img,
							 								x, y, color_pixel);
			y++;
		}
		x++;
	}
	return ((void *)"Ready");
}