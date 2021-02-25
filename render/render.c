#include "mini_rt.h"

void		check_inter_objs(t_stage *s_stage, t_ray *s_ray, double distance)
{
	t_list_objs	*s_list_obj;

	s_ray->length = distance;
	s_list_obj = s_stage->s_list_objs;
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
        s_ray->s_vec_inter_normal = vec_norm(&s_ray->s_vec_inter_normal);
}

t_rgb		get_color_pixel(t_stage *s_stage, t_ray *s_ray)
{
	t_ray	s_light_ray;
	t_rgb	s_color_res;
	t_rgb	s_color_obj;
	t_rgb	s_color_light;
    t_list	*s_list_light;
    double	light_length;
    double	angel_incidence;

	s_color_res = (t_rgb){0,0,0};
	s_list_light = s_stage->s_list_lights;
    if (vec_scalar_mul(&s_ray->s_vec_inter_normal, &s_ray->s_vec_start_normal) > 0)
		s_ray->s_vec_inter_normal = vec_mul(&s_ray->s_vec_inter_normal, -1);
	while (s_list_light)
    {
		s_light_ray.s_vec_start = s_ray->s_vec_inter;
        s_light_ray.s_vec_start_normal = vec_sub(((t_light *)s_list_light->content)->s_vec_origin, &s_ray->s_vec_inter);
        light_length = vec_len(&s_light_ray.s_vec_start_normal);
        s_light_ray.s_vec_start_normal = vec_norm(&s_light_ray.s_vec_start_normal);
        check_inter_objs(s_stage, &s_light_ray, light_length);
		if (s_light_ray.length == light_length)
        {
			angel_incidence = vec_scalar_mul(&s_light_ray.s_vec_start_normal,
												&s_ray->s_vec_inter_normal);
			if (angel_incidence > 0)
            {
                s_color_light = rgb_mul(((t_light *)s_list_light->content)->s_color,
                                angel_incidence *
                                ((t_light *)s_list_light->content)->brightness);
				s_color_obj = rgb_mul_arr(&s_ray->s_color_obj, &s_color_light);
				s_color_res = rgb_sum(&s_color_res, &s_color_obj);
            }
        }
        s_list_light = s_list_light->next;
    }
	s_color_light = rgb_mul(s_stage->s_ambient_light.s_color,
							s_stage->s_ambient_light.brightness);
	s_color_obj = rgb_mul_arr(&s_ray->s_color_obj, &s_color_light);
	s_color_res = rgb_sum(&s_color_res, &s_color_obj);
	return (s_color_res);
}

t_rgb		start_ray(t_stage *s_stage, t_ray *s_ray)
{
	check_inter_objs(s_stage, s_ray, MAX_DISTANCE);
	if (s_ray->length < MAX_DISTANCE)
		return (get_color_pixel(s_stage, s_ray));
	return ((t_rgb){0,0,0});
}

void		get_norm_start_ray(double x, double y, t_ray *s_ray, t_camera *s_camera)
{
	s_ray->s_vec_start_normal.x = x - s_camera->s_vscreen.width;
	s_ray->s_vec_start_normal.y = -y + s_camera->s_vscreen.height;
	s_ray->s_vec_start_normal.z = s_camera->s_vscreen.z;
	s_ray->s_vec_start_normal = matrix_mul(&s_ray->s_vec_start_normal, &s_camera->s_matrix_rotate);
	s_ray->s_vec_start_normal = vec_sub(&s_ray->s_vec_start_normal, s_camera->s_vec_origin);
	s_ray->s_vec_start_normal = vec_norm(&s_ray->s_vec_start_normal);
}

int			anti_aliasing(t_stage *s_stage, int x, int y, t_ray *s_ray)
{
	int		count_rays;
	t_rgb	s_color_res;
	t_rgb	s_color_ray;

	count_rays = 0;
	s_color_res = (t_rgb){0,0,0};
	while (count_rays < ANTI_ALIASING)
	{
		get_norm_start_ray(x + s_stage->s_aa_sample.matrix_sample[count_rays][0],
					 y + s_stage->s_aa_sample.matrix_sample[count_rays][1],
					 s_ray, s_stage->s_selected_camera);
		s_color_ray = start_ray(s_stage, s_ray);
		if (count_rays == 0)
			s_color_res = rgb_average(&s_color_ray, &s_color_res, 0);
		else
			s_color_res = rgb_average(&s_color_ray, &s_color_res, 1);
		count_rays++;
	}
	return (rgb_get_int(&s_color_res));
}

void		render(t_stage *s_stage)
{
	int		x;
	int		y;
	int		color_pixel;
	t_ray	s_ray;

	x = 0;
	s_ray.s_vec_start = *s_stage->s_selected_camera->s_vec_origin;
	while (x < s_stage->s_screen.width)
	{
		y = 0;
		while (y < s_stage->s_screen.height)
		{
			color_pixel = anti_aliasing(s_stage, x, y, &s_ray);
			my_mlx_pixel_put(&s_stage->s_selected_camera->s_mlx_img, x, y, color_pixel);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(s_stage->mlx_p, s_stage->mlx_window, s_stage->s_selected_camera->s_mlx_img.img, 0, 0);
	mlx_loop(s_stage->mlx_p);
}