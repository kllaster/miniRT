#ifndef RENDER_H
# define RENDER_H

# include "mini_rt.h"

typedef	struct	s_vscreen {
	double			width;
	double			height;
	double			x_coef;
	double			y_coef;
}				t_vscreen;

typedef	struct	s_ray {
	t_coordinates	s_vector_inter_length;
	t_coordinates	s_vector_inter_normal;
	t_coordinates	s_vector_inter;
	t_coordinates	s_vector_start_normal;
	t_coordinates	s_vector_start;
	double			length;
	unsigned char 	type;
	void			*content;
}				t_ray;

int				render(t_stage *s_stage);
t_rgb			rgb_sum(t_rgb *s_rgb1, t_rgb *s_rgb2);
t_rgb			rgb_mul(t_rgb *s_rgb, double num);
t_rgb           rgb_mul_arr(t_rgb *s_rgb1, t_rgb *s_rgb2);
int				rgb_get_int(t_rgb *s_rgb);
void			my_mlx_pixel_put(t_mlx_img *s_mlx_img, unsigned int x, unsigned int y, int color);
double			vector_len(t_coordinates *s_vector);
t_coordinates	vector_norm(t_coordinates *s_vector);
t_coordinates	vector_sum(t_coordinates *s_vector_1, t_coordinates *s_vector_2);
t_coordinates	vector_sub(t_coordinates *s_vector_1, t_coordinates *s_vector_2);
t_coordinates	vector_mul(t_coordinates *s_vector, double num);
double			vector_scalar_mul(t_coordinates *s_vector_1, t_coordinates *s_vector_2);
void			rotate_vector_x(t_coordinates *s_vector, double sin, double cos);
void			rotate_vector_y(t_coordinates *s_vector, double sin, double cos);
void			rotate_vector_z(t_coordinates *s_vector, double sin, double cos);

#endif