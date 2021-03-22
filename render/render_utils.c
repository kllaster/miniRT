#include "mini_rt.h"

void	add_gloss(t_rays *s_rays, t_rgb *s_color_res,
						t_rgb *s_color_light, t_vec *s_vec_phong)
{
	float	angel_incidence;

	s_rays->s_ray_light.s_vec_start_dir =
		vec_sum(&s_rays->s_ray_light.s_vec_start_dir, s_vec_phong);
	s_rays->s_ray_light.s_vec_start_dir =
		vec_norm(&s_rays->s_ray_light.s_vec_start_dir);
	angel_incidence = vec_dot(&s_rays->s_ray_light.s_vec_start_dir,
								&s_rays->s_ray.s_vec_inter_dir);
	if (angel_incidence > 0)
	{
		angel_incidence = powf(angel_incidence, 100);
		rgb_add_light(s_color_res, &s_rays->s_ray.s_material->s_color,
						s_color_light, angel_incidence);
	}
}

void	add_light_color(t_rays *s_rays, t_rgb *s_color_res,
							t_rgb *s_color_light, t_vec *s_vec_phong)
{
	float	angel_incidence;

	angel_incidence = vec_dot(&s_rays->s_ray_light.s_vec_start_dir,
								&s_rays->s_ray.s_vec_inter_dir);
	if (angel_incidence > 0)
	{
		rgb_add_light(s_color_res, &s_rays->s_ray.s_material->s_color,
						s_color_light, angel_incidence);
		add_gloss(s_rays, s_color_res, s_color_light, s_vec_phong);
	}
}

t_rgb	reflection(t_tdata *s_tdata, t_rays s_rays)
{
	float	ref_coeff;
	t_rgb	s_color;

	s_color = (t_rgb){0, 0, 0};
	if (++s_rays.count_ref < MAX_REF)
	{
		ref_coeff = s_rays.s_ray.s_material->ref_coeff;
		s_rays.s_ray.s_vec_start = s_rays.s_ray.s_vec_inter;
		get_vec_reflection(&s_rays.s_ray.s_vec_start_dir,
							&s_rays.s_ray.s_vec_inter_dir);
		check_inter_objs(s_tdata->s_lst_objs, &s_rays.s_ray,
							MAX_DISTANCE);
		if (s_rays.s_ray.length < MAX_DISTANCE)
		{
			s_color = get_color_pixel(s_tdata, &s_rays);
			s_color = rgb_mul(&s_color, ref_coeff);
		}
	}
	return (s_color);
}

int		rgb_get_int(t_rgb *s_rgb)
{
	if (!s_rgb)
		return (0);
	if (s_rgb->red > 255)
		s_rgb->red = 255;
	if (s_rgb->green > 255)
		s_rgb->green = 255;
	if (s_rgb->blue > 255)
		s_rgb->blue = 255;
	return (s_rgb->red << 16 | s_rgb->green << 8 | s_rgb->blue);
}

void	my_mlx_pixel_put(const t_mlx_img *s_mlx_img, int x, int y, int color)
{
	*(int *)(s_mlx_img->addr + (y * s_mlx_img->line_length + x * 4)) = color;
}
