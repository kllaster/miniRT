#include "mini_rt.h"

t_rgb	rgb_mul_arr(t_rgb *s_rgb1, t_rgb *s_rgb2)
{
	t_rgb	s_rgb_mul_arr;

	s_rgb_mul_arr.red = (int)((float)s_rgb1->red *
								(float)s_rgb2->red * 0.003921568627451);
	s_rgb_mul_arr.green = (int)((float)s_rgb1->green *
								(float)s_rgb2->green * 0.003921568627451);
	s_rgb_mul_arr.blue = (int)((float)s_rgb1->blue *
								(float)s_rgb2->blue * 0.003921568627451);
	return (s_rgb_mul_arr);
}

t_rgb	rgb_mul(t_rgb *s_rgb, float num)
{
	t_rgb	s_rgb_mul;

	s_rgb_mul.red = (int)((float)s_rgb->red * num);
	s_rgb_mul.green = (int)((float)s_rgb->green * num);
	s_rgb_mul.blue = (int)((float)s_rgb->blue * num);
	if (s_rgb_mul.red > 255)
		s_rgb_mul.red = 255;
	if (s_rgb_mul.green > 255)
		s_rgb_mul.green = 255;
	if (s_rgb_mul.blue > 255)
		s_rgb_mul.blue = 255;
	return (s_rgb_mul);
}

t_rgb	rgb_sum(t_rgb *s_rgb1, t_rgb *s_rgb2)
{
	t_rgb	s_rgb_sum;

	s_rgb_sum.red = s_rgb1->red + s_rgb2->red;
	s_rgb_sum.green = s_rgb1->green + s_rgb2->green;
	s_rgb_sum.blue = s_rgb1->blue + s_rgb2->blue;
	if (s_rgb_sum.red > 255)
		s_rgb_sum.red = 255;
	if (s_rgb_sum.green > 255)
		s_rgb_sum.green = 255;
	if (s_rgb_sum.blue > 255)
		s_rgb_sum.blue = 255;
	return (s_rgb_sum);
}

t_rgb	rgb_average(t_rgb *s_rgb1, t_rgb *s_rgb2, int flag)
{
	t_rgb	s_rgb_average;

	if (flag)
	{
		s_rgb_average.red = (int)((s_rgb1->red + s_rgb2->red) * 0.5);
		s_rgb_average.green = (int)((s_rgb1->green + s_rgb2->green) * 0.5);
		s_rgb_average.blue = (int)((s_rgb1->blue + s_rgb2->blue) * 0.5);
		return (s_rgb_average);
	}
	return (*s_rgb1);
}

void	rgb_add_light(t_rgb *s_rgb_res, const t_rgb *s_rgb_obj,
						t_rgb *s_rgb_light, float intensity)
{
	t_rgb	s_rgb_tmp;

	s_rgb_tmp.red = (int)((float)s_rgb_light->red * intensity);
	s_rgb_tmp.green = (int)((float)s_rgb_light->green * intensity);
	s_rgb_tmp.blue = (int)((float)s_rgb_light->blue * intensity);
	s_rgb_tmp.red > 255 ? s_rgb_tmp.red = 255 : 0;
	s_rgb_tmp.green > 255 ? s_rgb_tmp.green = 255 : 0;
	s_rgb_tmp.blue > 255 ? s_rgb_tmp.blue = 255 : 0;
	s_rgb_tmp.red = (int)((float)s_rgb_obj->red *
							(float)s_rgb_tmp.red * 0.003921568627451);
	s_rgb_tmp.green = (int)((float)s_rgb_obj->green *
							(float)s_rgb_tmp.green * 0.003921568627451);
	s_rgb_tmp.blue = (int)((float)s_rgb_obj->blue *
							(float)s_rgb_tmp.blue * 0.003921568627451);
	s_rgb_res->red = s_rgb_res->red + s_rgb_tmp.red;
	s_rgb_res->green = s_rgb_res->green + s_rgb_tmp.green;
	s_rgb_res->blue = s_rgb_res->blue + s_rgb_tmp.blue;
	if (s_rgb_res->red > 255)
		s_rgb_res->red = 255;
	if (s_rgb_res->green > 255)
		s_rgb_res->green = 255;
	if (s_rgb_res->blue > 255)
		s_rgb_res->blue = 255;
}
