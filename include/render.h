#ifndef RENDER_H
# define RENDER_H

# include "mini_rt.h"

typedef	struct	s_ray {
	double			length;
	t_coordinates	s_vector_inter_normal;
	t_coordinates	s_vector_inter;
	t_coordinates	s_vector_start_normal;
	t_coordinates	s_vector_start;
	unsigned char 	type;
	void			*content;
}				t_ray;

int				render(t_stage *s_stage);
int				get_int_rgb(t_rgb *s_rgb);
void			my_mlx_pixel_put(t_mlx_img *s_mlx_img, unsigned int x, unsigned int y, int color);
double			vector_len(t_coordinates *s_vector);
t_coordinates	vector_norm(t_coordinates *s_vector);
t_coordinates	vector_sum(t_coordinates *s_vector_1, t_coordinates *s_vector_2);
t_coordinates	vector_sub(t_coordinates *s_vector_1, t_coordinates *s_vector_2);
t_coordinates	vector_mul(t_coordinates *s_vector, double num);
double			vector_scalar_mul(t_coordinates *s_vector_1, t_coordinates *s_vector_2);

#endif