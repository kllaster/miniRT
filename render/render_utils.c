#include "mini_rt.h"

t_rgb	rgb_mul_arr(t_rgb *s_rgb1, t_rgb *s_rgb2)
{
    t_rgb	s_rgb_mul_arr;

    s_rgb_mul_arr.red = s_rgb1->red * s_rgb2->red * (1.0/255.0);
    s_rgb_mul_arr.green = s_rgb1->green * s_rgb2->green * (1.0/255.0);
    s_rgb_mul_arr.blue = s_rgb1->blue * s_rgb2->blue * (1.0/255.0);
    return (s_rgb_mul_arr);
}

t_rgb	rgb_mul(t_rgb *s_rgb, double num)
{
	t_rgb	s_rgb_mul;

	s_rgb_mul.red = (int)((double)s_rgb->red * num);
	s_rgb_mul.green = (int)((double)s_rgb->green * num);
	s_rgb_mul.blue =  (int)((double)s_rgb->blue * num);
	return (s_rgb_mul);
}

t_rgb	rgb_sum(t_rgb *s_rgb1, t_rgb *s_rgb2)
{
	t_rgb	s_rgb_sum;

	s_rgb_sum.red = s_rgb1->red + s_rgb2->red;
	s_rgb_sum.green = s_rgb1->green + s_rgb2->green;
	s_rgb_sum.blue = s_rgb1->blue + s_rgb2->blue;
	return (s_rgb_sum);
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

void	my_mlx_pixel_put(t_mlx_img *s_mlx_img, unsigned int x, unsigned int y, int color)
{
	*(unsigned int *)(s_mlx_img->addr + (y * s_mlx_img->line_length + x *
									(s_mlx_img->bits_per_pixel / 8))) = color;
}