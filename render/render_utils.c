#include "mini_rt.h"

int		get_int_rgb(t_rgb *s_rgb)
{
	return (s_rgb->red << 16 | s_rgb->green << 8 | s_rgb->blue);
}

void	my_mlx_pixel_put(t_mlx_img *s_mlx_img, unsigned int x, unsigned int y, int color)
{
	*(unsigned int *)(s_mlx_img->addr + (y * s_mlx_img->line_length + x *
									(s_mlx_img->bits_per_pixel / 8))) = color;
}