#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

typedef struct  s_mlx_img {
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_mlx_img;

typedef	struct	s_aa_sample {
	float			**matrix;
}				t_aa_sample;

typedef	struct	s_vscreen {
	float			width;
	float			height;
	float			z;
}				t_vscreen;

typedef	struct	s_camera {
	t_matrix		s_matrix_rotate;
	t_vscreen		s_vscreen;
	t_vec			*s_vec_dir;
	t_vec			*s_vec_origin;
	t_mlx_img		s_mlx_img;
	int				render_ready;
	int				fov;
	int				count;
	int				init;
}				t_camera;

typedef	struct	s_light {
	float			brightness;
	t_vec			*s_vec_origin;
	t_rgb			*s_color;
}				t_light;

typedef	struct	s_ambient_light {
	float			brightness;
	t_rgb			*s_color;
}				t_ambient_light;

typedef	struct	s_screen {
	int				height;
	int				width;
}				t_screen;

typedef	struct	s_stage {
	t_aa_sample		s_aa_sample;
	t_screen		s_screen;
	t_ambient_light	s_ambient_light;
	t_camera		*s_main_camera;
	t_list			*s_list_lights;
	t_list_objs		*s_list_objs;
	t_list			*s_list_cameras;
}				t_stage;

typedef	struct	s_thread_data {
	t_aa_sample		s_aa_sample;
	t_screen		s_screen;
	t_ambient_light	s_ambient_light;
	t_camera		*s_main_camera;
	t_list			*s_list_lights;
	t_list_objs		*s_list_objs;
	int 			start_x;
	int 			end_x;
}				t_thread_data;

typedef	struct	s_rt {
	t_stage			s_stage;
	t_thread_data	s_thread_data[COUNT_THREADS];
	pthread_t		threads[COUNT_THREADS];
	t_vec			new_dir;
	int				x_move;
	int				y_move;
	int				z_move;
	void			*mlx_window;
	void			*mlx_p;
	int				render_now;
}				t_rt;

#endif
