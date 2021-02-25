#ifndef COLOR_H
# define COLOR_H

typedef	struct	s_rgb {
	int				red;
	int				green;
	int				blue;
}				t_rgb;

t_rgb			rgb_sum(t_rgb *s_rgb1, t_rgb *s_rgb2);
t_rgb			rgb_mul(t_rgb *s_rgb, double num);
t_rgb           rgb_mul_arr(t_rgb *s_rgb1, t_rgb *s_rgb2);
t_rgb			rgb_average(t_rgb *s_rgb1, t_rgb *s_rgb2, int flag);
int				rgb_get_int(t_rgb *s_rgb);

#endif