#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

typedef struct  s_mlx_img {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_mlx_img;

typedef	struct	s_rgb {
	int				red;
	int				green;
	int				blue;
}				t_rgb;

typedef	struct	s_coordinates {
	double			x;
	double			y;
	double			z;
}				t_coordinates;

typedef	struct	s_light {
	double			brightness;
	t_coordinates	*s_coordinates;
	t_rgb			*s_color;
}				t_light;

typedef	struct	s_vscreen {
	double			width;
	double			height;
	double			z;
}				t_vscreen;

typedef	struct	s_camera {
	double			sin_angle_x;
	double			cos_angle_x;
	double			sin_angle_y;
	double			cos_angle_y;
	double			sin_angle_z;
	double			cos_angle_z;
	t_vscreen		*s_vscreen;
	t_coordinates	*s_angle;
	t_coordinates	*s_coordinates;
	t_mlx_img		*s_mlx_img;
	int				fov;
}				t_camera;

typedef	struct	s_g_light {
	double			brightness;
	t_rgb			*s_color;
}				t_g_light;

typedef	struct	s_screen {
	int				height;
	int				width;
}				t_screen;

typedef struct		s_list_objs
{
	unsigned char 		type;
	void				*content;
	struct s_list_objs	*next;
}					t_list_objs;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef	struct	s_stage {
	void		*mlx_p;
	void		*mlx_window;
	t_camera	*s_selected_camera;
	t_screen	s_screen;
	t_g_light	*s_g_light;
	t_list		*s_list_cameras;
	t_list		*s_list_lights;
	t_list_objs	*s_list_objs;
}				t_stage;

#endif
