#include "mini_rt.h"

t_coordinates	matrix_mul(t_coordinates *u, t_matrix *m)
{
	t_coordinates v;

	v.x = u->x * m->el[0][0] + u->y * m->el[1][0] + u->z * m->el[2][0] + m->el[3][0];
	v.y = u->x * m->el[0][1] + u->y * m->el[1][1] + u->z * m->el[2][1] + m->el[3][1];
	v.z = u->x * m->el[0][2] + u->y * m->el[1][2] + u->z * m->el[2][2] + m->el[3][2];
	return (v);
}

t_matrix		get_matrix_rotate(t_coordinates *s_vector_orig, t_coordinates *s_vector_dir)
{
	t_matrix		s_matrix;
	t_coordinates	s_vector_tmp;

	s_vector_tmp = (t_coordinates){0.0, 1.0, 0.0};
	s_vector_tmp = vector_cross_product(&s_vector_tmp, s_vector_dir);
	s_vector_tmp = vector_norm(&s_vector_tmp);
	s_matrix.el[0][0] = s_vector_tmp.x;
	s_matrix.el[0][1] = s_vector_tmp.y;
	s_matrix.el[0][2] = s_vector_tmp.z;
	s_vector_tmp = vector_cross_product(s_vector_dir, &s_vector_tmp);
	s_vector_tmp = vector_norm(&s_vector_tmp);
	s_matrix.el[1][0] = s_vector_tmp.x;
	s_matrix.el[1][1] = s_vector_tmp.y;
	s_matrix.el[1][2] = s_vector_tmp.z;
	s_matrix.el[2][0] = s_vector_dir->x;
	s_matrix.el[2][1] = s_vector_dir->y;
	s_matrix.el[2][2] = s_vector_dir->z;
	s_matrix.el[3][0] = s_vector_orig->x;
	s_matrix.el[3][1] = s_vector_orig->y;
	s_matrix.el[3][2] = s_vector_orig->z;
	return (s_matrix);
}

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