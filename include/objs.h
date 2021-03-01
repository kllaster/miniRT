#ifndef RT_OBJS_H
# define RT_OBJS_H

# include "mini_rt.h"

enum e_objs {
	OBJ_NONE		= 0b00000000,
	OBJ_SPHERE		= 0b00000001,
	OBJ_PLANE		= 0b00000010,
	OBJ_SQUARE		= 0b00000100,
	OBJ_CYLINDER	= 0b00001000,
	OBJ_TRIANGLE	= 0b00010000
};

typedef	struct	s_sphere {
	float	radius;
	t_vec	*s_vec_origin;
	t_rgb	*s_color;
}				t_sphere;

typedef	struct	s_plane {
	t_vec	*s_vec_origin;
	t_vec	*s_vec_dir;
	t_rgb	*s_color;
}				t_plane;

typedef	struct	s_square {
	float	side_size;
	t_vec	*s_vec_origin;
	t_vec	*s_vec_dir;
	t_rgb	*s_color;
}				t_square;

typedef	struct	s_cylinder {
	float	diameter;
	float	height;
	t_vec	*s_vec_origin;
	t_vec	*s_vec_dir;
	t_rgb	*s_color;
}				t_cylinder;

typedef	struct	s_triangle {
	t_vec	*s_vec_origin_1;
	t_vec	*s_vec_origin_2;
	t_vec	*s_vec_origin_3;
	t_vec	*s_vec_edge_1;
	t_vec	*s_vec_edge_2;
	t_vec	*s_vec_dir;
	t_rgb	*s_color;
}				t_triangle;

t_vec		*vec_cpy(t_vec *s_vec);
t_rgb		*rgb_cpy(t_rgb *s_color);
void		*light_cpy(void *data);
void		*camera_cpy(void *data);
t_triangle	*triangle_cpy(t_triangle *s_triangle);
t_cylinder	*cylinder_cpy(t_cylinder *s_cylinder);
t_square	*square_cpy(t_square *s_square);
t_plane		*plane_cpy(t_plane *s_plane);
t_sphere	*sphere_cpy(t_sphere *s_sphere);
void		*obj_cpy(void *data, unsigned char type);

#endif
