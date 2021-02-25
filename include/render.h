#ifndef RENDER_H
# define RENDER_H

# include "mini_rt.h"

typedef	struct	s_ray {
	t_coordinates	s_vector_inter_normal;
	t_coordinates	s_vector_inter;
	t_coordinates	s_vector_start_normal;
	t_coordinates	s_vector_start;
	t_rgb			s_color_obj;
	double			length;
}				t_ray;

void			init_render(t_stage *s_stage);
void			render(t_stage *s_stage);
void			inter_sphere(t_sphere *s_sphere, t_ray *s_ray);
void			inter_plane(t_plane *s_plane, t_ray *s_ray);
t_rgb			rgb_sum(t_rgb *s_rgb1, t_rgb *s_rgb2);
t_rgb			rgb_mul(t_rgb *s_rgb, double num);
t_rgb           rgb_mul_arr(t_rgb *s_rgb1, t_rgb *s_rgb2);
t_rgb			rgb_average(t_rgb *s_rgb1, t_rgb *s_rgb2, int flag);
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
t_coordinates	vector_cross_product(t_coordinates *s_vector_1, t_coordinates *s_vector_2);
t_coordinates	matrix_mul(t_coordinates *u, t_matrix *m);
t_matrix		get_matrix_rotate(t_coordinates *s_vector_orig, t_coordinates *s_vector_dir);

#endif