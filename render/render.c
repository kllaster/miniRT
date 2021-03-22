#include "mini_rt.h"

void	check_inter_objs(t_lst_objs *s_lst_objs, t_ray *s_ray,
								float distance)
{
	t_lst_objs	*s_lst_obj_prev;

	s_ray->length = distance;
	if (s_ray->last_inter_obj)
		s_ray->func_inter(s_ray->last_inter_obj, s_ray);
	s_lst_obj_prev = s_lst_objs->prev;
	while (s_lst_objs != s_lst_obj_prev &&
			s_lst_objs != s_lst_obj_prev->prev)
	{
		s_lst_objs->func_inter(s_lst_objs->content, s_ray);
		s_lst_obj_prev->func_inter(s_lst_obj_prev->content, s_ray);
		s_lst_objs = s_lst_objs->next;
		s_lst_obj_prev = s_lst_obj_prev->prev;
	}
	s_lst_objs->func_inter(s_lst_objs->content, s_ray);
	if (s_lst_objs == s_lst_obj_prev->prev && s_lst_objs != s_lst_obj_prev)
		s_lst_obj_prev->func_inter(s_lst_obj_prev->content, s_ray);
	if (s_ray->length < distance && s_ray->last_inter_type ^ OBJ_SPHERE &&
			s_ray->last_inter_type ^ OBJ_CYLINDER)
	{
		s_ray->s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, s_ray->length);
		s_ray->s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray->s_vec_inter);
	}
}

int		check_light_inter(t_tdata *s_tdata, t_rays *s_rays, t_vec *s_vec_light)
{
	float	light_length;

	light_length = get_vec_light(&s_rays->s_ray_light,
									&s_rays->s_ray.s_vec_inter, s_vec_light);
	check_inter_objs(s_tdata->s_lst_objs, &s_rays->s_ray_light, light_length);
	return (s_rays->s_ray_light.length == light_length);
}

t_rgb	get_color_pixel(t_tdata *s_tdata, t_rays *s_rays)
{
	t_vec	s_vec_med;
	t_rgb	s_color_res;
	t_rgb	s_color_ref;
	t_lst	*s_lst_light;

	s_color_res = (t_rgb){0, 0, 0};
	s_vec_med = vec_sub(&s_rays->s_ray.s_vec_start, &s_rays->s_ray.s_vec_inter);
	s_vec_med = vec_norm(&s_vec_med);
	s_lst_light = s_tdata->s_lst_lights;
	while (s_lst_light)
	{
		if (check_light_inter(s_tdata, s_rays,
				&((t_light *)s_lst_light->content)->s_vec_o))
			add_light_color(s_rays, &s_color_res,
				&((t_light *)s_lst_light->content)->s_color, &s_vec_med);
		s_lst_light = s_lst_light->next;
	}
	rgb_add_light(&s_color_res, &s_rays->s_ray.s_material->s_color,
					s_tdata->s_ambient_color, 1);
	if (s_rays->s_ray.s_material->ref_coeff)
	{
		s_color_ref = reflection(s_tdata, *s_rays);
		s_color_res = rgb_sum(&s_color_res, &s_color_ref);
	}
	return (s_color_res);
}

int		anti_aliasing(t_tdata *s_tdata, float x, float y, t_rays *s_rays)
{
	int		i;
	int		count_rays;
	t_rgb	s_color_res;
	t_rgb	s_color_ray;

	i = -1;
	count_rays = s_tdata->anti_aliasing ? 3 : 1;
	s_color_res = (t_rgb){0, 0, 0};
	while (++i < count_rays)
	{
		get_vec_start_dir(x + s_tdata->s_aa_sample.matrix[i][0],
							s_tdata->s_aa_sample.matrix[i][1] - y,
							&s_rays->s_ray, s_tdata->s_main_cam);
		check_inter_objs(s_tdata->s_lst_objs, &s_rays->s_ray, MAX_DISTANCE);
		if (s_rays->s_ray.length < MAX_DISTANCE)
			s_color_ray = get_color_pixel(s_tdata, s_rays);
		else
			s_color_ray = (t_rgb){0, 0, 0};
		if (i == 0)
			s_color_res = rgb_average(&s_color_ray, &s_color_res, 0);
		else
			s_color_res = rgb_average(&s_color_ray, &s_color_res, 1);
	}
	return (rgb_get_int(&s_color_res));
}

void	*render(void *data)
{
	int			x;
	int			y;
	int			color_pixel;
	t_rays		s_rays;
	t_tdata		*s_tdata;

	ft_bzero(&s_rays, sizeof(s_rays));
	s_tdata = (t_tdata *)data;
	s_rays.s_ray.s_vec_start = s_tdata->s_main_cam->s_vec_o;
	y = s_tdata->start_y;
	while (y < s_tdata->end_y)
	{
		x = 0;
		while (x < s_tdata->width)
		{
			s_rays.count_ref = -1;
			color_pixel = anti_aliasing(s_tdata, (float)x, (float)y, &s_rays);
			my_mlx_pixel_put(&s_tdata->s_main_cam->s_mlx_img,
								x, y, color_pixel);
			++x;
		}
		++y;
	}
	return ((void *)"Ready");
}
