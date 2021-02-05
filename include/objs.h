#ifndef RT_OBJS_H
# define RT_OBJS_H

# include "mini_rt.h"

# define OBJ_NONE		0b00000000
# define OBJ_SPHERE		0b00000001
# define OBJ_PLANE		0b00000010
# define OBJ_SQUARE		0b00000100
# define OBJ_CYLINDER	0b00001000
# define OBJ_TRIANGLE	0b00010000

typedef	struct	s_sphere {
	float			diameter;
	t_coordinates	*s_coordinates;
	t_rgb			*s_color;
}				t_sphere;

typedef	struct	s_plane {
	t_coordinates	*s_coordinates;
	t_angle			*s_angle;
	t_rgb			*s_color;
}				t_plane;

typedef	struct	s_square {
	float			side_size;
	t_coordinates	*s_coordinates;
	t_angle			*s_angle;
	t_rgb			*s_color;
}				t_square;

typedef	struct	s_cylinder {
	float			diameter;
	float			height;
	t_coordinates	*s_coordinates;
	t_angle			*s_angle;
	t_rgb			*s_color;
}				t_cylinder;

typedef	struct	s_triangle {
	t_coordinates	*s_coordinates_1;
	t_coordinates	*s_coordinates_2;
	t_coordinates	*s_coordinates_3;
	t_rgb			*s_color;
}				t_triangle;

#endif
