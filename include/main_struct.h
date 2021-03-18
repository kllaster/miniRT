#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

typedef struct	s_mlx_img {
	void			*img_ptr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			*addr;
}				t_mlx_img;

typedef	struct	s_aa_sample {
	float			matrix[10][2];
}				t_aa_sample;

typedef	struct	s_vscreen {
	float			width;
	float			height;
	float			z;
}				t_vscreen;

typedef	struct	s_cam {
	t_matrix		s_matrix_rotate;
	t_vscreen		s_vscreen;
	t_mlx_img		s_mlx_img;
	t_vec			s_vec_o;
	t_vec			s_vec_dir;
	int				render_ready;
	int				fov;
	int				count;
	int				init;
}				t_cam;

typedef	struct	s_light {
	t_vec			s_vec_o;
	t_rgb			s_color;
}				t_light;

typedef	struct	s_tdata {
	t_aa_sample		s_aa_sample;
	t_cam			*s_main_cam;
	t_lst			*s_lst_lights;
	t_lst_objs		*s_lst_objs;
	t_rgb			*s_ambient_color;
	int				anti_aliasing;
	int				height;
	int				width;
	int				start_y;
	int				end_y;
}				t_tdata;

typedef	struct	s_stage {
	t_aa_sample		s_aa_sample;
	t_cam			*s_main_cam;
	t_lst			*s_lst_lights;
	t_lst_objs		*s_lst_objs;
	t_rgb			*s_ambient_color;
	int				anti_aliasing;
	int				height;
	int				width;
	t_lst			*s_lst_cams;
}				t_stage;

typedef	struct	s_rt {
	t_stage			s_stage;
	t_tdata			s_tdata[COUNT_THREADS];
	pthread_t		threads[COUNT_THREADS];
	t_vec			s_vec_dir;
	t_vec			s_vec_pos;
	void			*mlx_window;
	void			*mlx_p;
	int				change_obj;
	int				change_cam;
	int				render_now;
}				t_rt;

#endif
