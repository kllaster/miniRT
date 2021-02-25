#include "mini_rt.h"

t_rgb	rgb_mul_arr(t_rgb *s_rgb1, t_rgb *s_rgb2)
{
	t_rgb	s_rgb_mul_arr;

	s_rgb_mul_arr.red = (int)((double)s_rgb1->red * (double)s_rgb2->red / 255.0);
	s_rgb_mul_arr.green = (int)((double)s_rgb1->green * s_rgb2->green / 255.0);
	s_rgb_mul_arr.blue = (int)((double)s_rgb1->blue * (double)s_rgb2->blue / 255.0);
	return (s_rgb_mul_arr);
}

t_rgb	rgb_mul(t_rgb *s_rgb, double num)
{
	t_rgb	s_rgb_mul;

	s_rgb_mul.red = (int)((double)s_rgb->red * num);
	s_rgb_mul.green = (int)((double)s_rgb->green * num);
	s_rgb_mul.blue =  (int)((double)s_rgb->blue * num);
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
		s_rgb_average.red = (s_rgb1->red + s_rgb2->red) / 2;
		s_rgb_average.green = (s_rgb1->green + s_rgb2->green) / 2;
		s_rgb_average.blue = (s_rgb1->blue + s_rgb2->blue) / 2;
		return (s_rgb_average);
	}
	return (*s_rgb1);
}