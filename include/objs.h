#ifndef RT_OBJS_H
# define RT_OBJS_H

# include "mini_rt.h"

enum e_objs
{
	OBJ_NONE		= 0b00000000,
	OBJ_SPHERE		= 0b00000001,
	OBJ_PLANE		= 0b00000010,
	OBJ_SQUARE		= 0b00000100,
	OBJ_CYLINDER	= 0b00001000,
	OBJ_TRIANGLE	= 0b00010000
};

typedef	struct	s_sphere {
	double			radius;
	t_coordinates	*s_coordinates;
	t_rgb			*s_color;
}				t_sphere;

typedef	struct	s_plane {
	t_coordinates	*s_coordinates;
	t_coordinates	*s_angle;
	t_rgb			*s_color;
}				t_plane;

typedef	struct	s_square {
	double			side_size;
	t_coordinates	*s_coordinates;
	t_coordinates	*s_angle;
	t_rgb			*s_color;
}				t_square;

typedef	struct	s_cylinder {
	double			diameter;
	double			height;
	t_coordinates	*s_coordinates;
	t_coordinates	*s_angle;
	t_rgb			*s_color;
}				t_cylinder;

typedef	struct	s_triangle {
	t_coordinates	*s_coordinates_1;
	t_coordinates	*s_coordinates_2;
	t_coordinates	*s_coordinates_3;
	t_rgb			*s_color;
}				t_triangle;

#endif
