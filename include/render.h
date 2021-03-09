#ifndef RENDER_H
# define RENDER_H

# include "mini_rt.h"

typedef	struct	s_ray {
	t_vec			s_vec_inter_dir;
	t_vec			s_vec_inter;
	t_vec			s_vec_start_dir;
	t_vec			s_vec_start;
	t_rgb			s_color_obj;
	void			*last_inter_obj;
	unsigned char	last_inter_type;
	float			length;
}				t_ray;

typedef	struct	s_rays {
	t_ray			s_ray_light;
	t_ray			s_ray;
}				t_rays;

int				start_render(t_rt *s_rt);
void			create_threads_data(t_rt *s_rt);
void			get_another_camera(t_rt *s_rt);
void			init_render(t_rt *s_rt);
void			*render(void *data);
void			inter_plane(const t_plane *s_plane, t_ray *s_ray);
void			inter_square(const t_square *s_square, t_ray *s_ray);
void			inter_sphere(const t_sphere *s_sphere, t_ray *s_ray);
void			inter_triangle(const t_triangle *s_triangle, t_ray *s_ray);
void			my_mlx_pixel_put(const t_mlx_img *s_mlx_img, int x, int y,
									int color);
void			get_aa_sample(t_aa_sample *s_aa_sample);
void			save_img(t_rt *s_rt, char *argv[]);

#endif
