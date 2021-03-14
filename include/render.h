#ifndef RENDER_H
# define RENDER_H

# include "mini_rt.h"

typedef	struct	s_ray {
	const t_material	*s_material;
	t_vec				s_vec_inter_dir;
	t_vec				s_vec_inter;
	t_vec				s_vec_start_dir;
	t_vec				s_vec_start;
	void				*last_inter_obj;
	float				length;
	char				last_inter_type;
}				t_ray;

typedef	struct	s_rays {
	t_ray			s_ray_light;
	t_ray			s_ray;
	int				count_ref;
}				t_rays;

int				start_render(t_rt *s_rt);
void			create_threads_data(t_rt *s_rt);
void			get_another_camera(t_rt *s_rt);
void			init_render(t_rt *s_rt);
void			*render(void *data);
void			check_inter_objs(t_list_objs *s_list_objs, t_ray *s_ray,
							 		float distance);
void			add_gloss(t_rays *s_rays, t_rgb *s_color_res,
							  t_rgb *s_color_light, t_vec *s_vec_phong);
void 			add_light_color(t_rays *s_rays, t_rgb *s_color_res,
									t_rgb *s_color_light, t_vec *s_vec_phong);
t_rgb			get_color_pixel(t_thread_data *s_thread_data, t_rays *s_rays);
t_rgb			reflection(t_thread_data *s_thread_data, t_rays s_rays);
void			add_inter_res(t_ray *s_ray, const t_material *s_material,
					 			float x);
void			inter_plane(const t_plane *s_plane, t_ray *s_ray);
void			inter_square(const t_square *s_square, t_ray *s_ray);
void			inter_sphere(const t_sphere *s_sphere, t_ray *s_ray);
void			inter_triangle(const t_triangle *s_triangle, t_ray *s_ray);
void			my_mlx_pixel_put(const t_mlx_img *s_mlx_img, int x, int y,
									int color);
void			get_aa_sample(t_aa_sample *s_aa_sample);
void			save_img(t_rt *s_rt, char *name, char *argv[]);

#endif
