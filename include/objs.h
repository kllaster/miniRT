#ifndef RT_OBJS_H
# define RT_OBJS_H

# include "mini_rt.h"

enum	e_objs {
	OBJ_SPHERE = 0b00000001,
	OBJ_PLANE = 0b00000010,
	OBJ_SQUARE = 0b00000100,
	OBJ_CYLINDER = 0b00001000,
	OBJ_TRIANGLE = 0b00010000
};

typedef	struct	s_material {
	t_rgb		s_color;
	float		ref_coeff;
}				t_material;

typedef	struct	s_sphere {
	t_material	s_material;
	t_vec		s_vec_o;
	float		radius_pow;
	float		diameter;
}				t_sphere;

typedef	struct	s_plane {
	t_material	s_material;
	t_vec		s_vec_dir;
	t_vec		s_vec_o;
}				t_plane;

typedef	struct	s_square {
	t_material	s_material;
	t_vec		s_vec_dir;
	t_vec		s_vec_o;
	float		side_size;
	float		side_half;
}				t_square;

typedef	struct	s_cylinder {
	t_material	s_material;
	t_vec		s_vec_dir;
	t_vec		s_vec_o;
	float		diameter;
	float		radius_pow;
	float		height;
	float		height_half;
}				t_cylinder;

typedef	struct	s_triangle {
	t_material	s_material;
	t_vec		s_vec_dir;
	t_vec		s_vec_o_1;
	t_vec		s_vec_o_2;
	t_vec		s_vec_o_3;
	t_vec		s_vec_edge_1;
	t_vec		s_vec_edge_2;
}				t_triangle;

t_material		parse_material_param(char **str);

#endif
