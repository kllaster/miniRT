#include "mini_rt.h"

void		add_inter_res(t_ray *s_ray, const t_material *s_material, float x)
{
	s_ray->length = x;
	s_ray->s_vec_inter = vec_mul(&s_ray->s_vec_start_dir, x);
	s_ray->s_vec_inter = vec_sum(&s_ray->s_vec_start, &s_ray->s_vec_inter);
	s_ray->s_material = s_material;
}

void		add_gloss(t_rays *s_rays, t_rgb *s_color_res,
						t_rgb *s_color_light, t_vec *s_vec_phong)
{
	float	angel_incidence;

	s_rays->s_ray_light.s_vec_start_dir =
		vec_sum(&s_rays->s_ray_light.s_vec_start_dir, s_vec_phong);
	s_rays->s_ray_light.s_vec_start_dir =
		vec_norm(&s_rays->s_ray_light.s_vec_start_dir);
	if ((angel_incidence =
				vec_dot(&s_rays->s_ray_light.s_vec_start_dir,
							&s_rays->s_ray.s_vec_inter_dir)) > 0)
	{
		angel_incidence = powf(angel_incidence, 100);
		rgb_add_light(s_color_res, &s_rays->s_ray.s_material->s_color,
						s_color_light, angel_incidence);
	}
}

void		add_light_color(t_rays *s_rays, t_rgb *s_color_res,
							t_rgb *s_color_light, t_vec *s_vec_phong)
{
	float	angel_incidence;

	if ((angel_incidence = vec_dot(&s_rays->s_ray_light.s_vec_start_dir,
									&s_rays->s_ray.s_vec_inter_dir)) > 0)
	{
		rgb_add_light(s_color_res, &s_rays->s_ray.s_material->s_color,
						s_color_light, angel_incidence);
		add_gloss(s_rays, s_color_res, s_color_light, s_vec_phong);
	}
}

void		get_vec_reflection(t_vec *s_vec_start_dir, t_vec *s_vec_dir)
{
	t_vec	s_vec;

	*s_vec_start_dir = vec_mul(s_vec_start_dir, -1);
	s_vec = vec_mul(s_vec_dir, 2 * vec_dot(s_vec_dir, s_vec_start_dir));
	*s_vec_start_dir = vec_sub(&s_vec, s_vec_start_dir);
	*s_vec_start_dir = vec_norm(s_vec_start_dir);
}

t_rgb		reflection(t_thread_data *s_thread_data, t_rays s_rays)
{
	float 	ref_coeff;
	t_rgb	s_color;

	s_color = (t_rgb){0, 0, 0};
	if (++s_rays.count_ref < MAX_REF)
	{
		ref_coeff = s_rays.s_ray.s_material->ref_coeff;
		s_rays.s_ray.s_vec_start = s_rays.s_ray.s_vec_inter;
		get_vec_reflection(&s_rays.s_ray.s_vec_start_dir,
							&s_rays.s_ray.s_vec_inter_dir);
		check_inter_objs(s_thread_data, &s_rays.s_ray, MAX_DISTANCE);
		if (s_rays.s_ray.length < MAX_DISTANCE)
		{
			s_color = get_color_pixel(s_thread_data, &s_rays);
			if (s_rays.s_ray.s_material->ref_coeff)
				s_color = rgb_mul(&s_color, s_rays.s_ray.s_material->ref_coeff);
			s_color = rgb_mul(&s_color, ref_coeff);
		}
	}
	return (s_color);
}

void	get_aa_sample(t_aa_sample *s_aa_sample)
{
	int		i;
	float	aa_sample1[1][2] = {{0,0}};
	float	aa_sample2[2][2] = {{-0.35,0.35}, {0.35,-0.35}};
	float	aa_sample3[3][2] = {{-0.45,0.45}, {-0.4,-0.45}, {-0.45,-0.4}};
	float	aa_sample4[4][2] = {{-0.45,0.4}, {0.4,0.45}, {-0.4,-0.45}, {-0.45,-0.45}};
	float	aa_sample5[5][2] = {{-0.45,0.4}, {0.4,0.45}, {0,0}, {-0.4,-0.45}, {-0.45,-0.45}};

	i = -1;
	while (++i < ANTI_ALIASING)
	{
		if (ANTI_ALIASING == 1)
		{
			s_aa_sample->matrix[i][0] = aa_sample1[i][0];
			s_aa_sample->matrix[i][1] = aa_sample1[i][1];
		}
		else if (ANTI_ALIASING == 2)
		{
			s_aa_sample->matrix[i][0] = aa_sample2[i][0];
			s_aa_sample->matrix[i][1] = aa_sample2[i][1];
		}
		else if (ANTI_ALIASING == 3)
		{
			s_aa_sample->matrix[i][0] = aa_sample3[i][0];
			s_aa_sample->matrix[i][1] = aa_sample3[i][1];
		}
		else if (ANTI_ALIASING == 4)
		{
			s_aa_sample->matrix[i][0] = aa_sample4[i][0];
			s_aa_sample->matrix[i][1] = aa_sample4[i][1];
		}
		else if (ANTI_ALIASING == 5)
		{
			s_aa_sample->matrix[i][0] = aa_sample5[i][0];
			s_aa_sample->matrix[i][1] = aa_sample5[i][1];
		}
	}
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
