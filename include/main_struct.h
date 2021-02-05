#ifndef MAIN_STRUCT_H
# define MAIN_STRUCT_H

typedef	struct	s_rgb {
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
}				t_rgb;

typedef	struct	s_coordinates {
	float			x;
	float			y;
	float			z;
}				t_coordinates;

typedef	struct	s_angle {
	float			x;
	float			y;
	float			z;
}				t_angle;

typedef	struct	s_light {
	float			brightness;
	t_coordinates	*s_coordinates;
	t_rgb			*s_color;
}				t_light;

typedef	struct	s_camera {
	unsigned int	fov;
	t_angle			*s_angle;
	t_coordinates	*s_coordinates;
}				t_camera;

typedef	struct	s_g_light {
	float			brightness;
	t_rgb			*s_color;
}				t_g_light;

typedef	struct	s_screen {
	unsigned int	height;
	unsigned int	width;
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
	t_screen	s_screen;
	t_g_light	*s_g_light;
	t_list		*s_list_cameras;
	t_list		*s_list_lights;
	t_list_objs	*s_list_objs;
}				t_stage;

#endif
