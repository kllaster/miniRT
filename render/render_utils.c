#include "mini_rt.h"

void		add_gloss(t_rays *s_rays, t_rgb *s_color_res,
					  t_rgb *s_color_light, t_vec *s_vec_halfway,
					  t_vec *s_vec_phong)
{
	float	angel_incidence;

	*s_vec_halfway = vec_sum(s_vec_halfway, s_vec_phong);
	*s_vec_halfway = vec_norm(s_vec_halfway);
	if ((angel_incidence =
				 vec_scalar_mul(s_vec_halfway,
								&s_rays->s_ray.s_vec_inter_dir)) > 0)
	{
		angel_incidence = powf(angel_incidence, 60);
		rgb_add_light(s_color_res, &s_rays->s_ray.s_color_obj,
					  s_color_light,
					  angel_incidence);
	}
}

void 		add_light_color(t_rays *s_rays, t_rgb *s_color_res,
							t_rgb *s_color_light, t_vec *s_vec_phong)
{
	float	angel_incidence;

	if ((angel_incidence = vec_scalar_mul(&s_rays->s_ray_light.s_vec_start_dir,
										  &s_rays->s_ray.s_vec_inter_dir)) > 0)
	{
		rgb_add_light(s_color_res, &s_rays->s_ray.s_color_obj,
					  s_color_light,
					  angel_incidence);
		add_gloss(s_rays, s_color_res,
				  s_color_light,
				  &s_rays->s_ray_light.s_vec_start_dir,
				  s_vec_phong);
	}
}

t_rgb		reflection(t_thread_data *s_thread_data, t_rays *s_rays, float coeff)
{
	int			count;
	t_rgb		s_color;

	s_color = (t_rgb){0, 0, 0};
	s_rays->s_ray.s_vec_start = s_rays->s_ray.s_vec_inter;
	s_rays->s_ray.s_vec_start_dir = s_rays->s_ray.s_vec_inter_dir;
	count = -1;
	while (++count < MAX_REF)
	{
		check_inter_objs(s_thread_data, &s_rays->s_ray, MAX_DISTANCE);
		if (s_rays->s_ray.length < MAX_DISTANCE)
		{
			s_rays->s_ray.s_vec_start = s_rays->s_ray.s_vec_inter;
			s_rays->s_ray.s_vec_start_dir = s_rays->s_ray.s_vec_inter_dir;
		}
		else
		{
			if (count != 0)
			{
				s_rays->s_ray.s_vec_inter = s_rays->s_ray.s_vec_start;
				s_rays->s_ray.s_vec_inter_dir = s_rays->s_ray.s_vec_start_dir;
				s_rays->s_ray.length = 1;
			}
			break ;
		}
	}
	if (count != 0)
	{
		s_color = get_color_pixel(s_thread_data, s_rays);
		s_color = rgb_mul(&s_color, coeff);
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
