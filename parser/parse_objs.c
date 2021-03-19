#include "mini_rt.h"

void	parse_sphere(char *str, t_stage *s_stage)
{
	t_sphere	*s_sphere;

	skip_between_param(&str, 0);
	malloc_void((void **)&s_sphere, sizeof(t_sphere));
	ft_lst_obj_add_front(&(s_stage->s_lst_objs),
							ft_lst_obj_new(s_sphere, OBJ_SPHERE, inter_sphere));
	s_sphere->s_vec_o = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_sphere->diameter = parse_float(&str, 1);
	if (s_sphere->diameter <= 0.0)
		error_end("Incorrect sphere diameter", PARSE_ERROR, 0, NULL);
	s_sphere->radius_pow = s_sphere->diameter * (float)0.5;
	s_sphere->radius_pow *= s_sphere->radius_pow;
	s_sphere->s_material = parse_material_param(&str);
}

void	parse_plane(char *str, t_stage *s_stage)
{
	t_plane	*s_plane;

	skip_between_param(&str, 0);
	malloc_void((void **)&s_plane, sizeof(t_plane));
	ft_lst_obj_add_front(&(s_stage->s_lst_objs),
							ft_lst_obj_new(s_plane, OBJ_PLANE, inter_plane));
	s_plane->s_vec_o = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_plane->s_vec_dir = parse_coordinates(&str);
	if (ft_fabs(s_plane->s_vec_dir.x) > 1 ||
		ft_fabs(s_plane->s_vec_dir.y) > 1 ||
		ft_fabs(s_plane->s_vec_dir.z) > 1)
		error_end("Incorrect direction obj plane",
					PARSE_ERROR, 0, NULL);
	s_plane->s_vec_dir = vec_norm(&s_plane->s_vec_dir);
	s_plane->s_material = parse_material_param(&str);
}

void	parse_square(char *str, t_stage *s_stage)
{
	t_square	*s_square;

	skip_between_param(&str, 0);
	malloc_void((void **)&s_square, sizeof(t_square));
	ft_lst_obj_add_front(&(s_stage->s_lst_objs),
							ft_lst_obj_new(s_square, OBJ_SQUARE, inter_square));
	s_square->s_vec_o = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_square->s_vec_dir = parse_coordinates(&str);
	if (ft_fabs(s_square->s_vec_dir.x) > 1 ||
		ft_fabs(s_square->s_vec_dir.y) > 1 ||
		ft_fabs(s_square->s_vec_dir.z) > 1)
		error_end("Incorrect direction obj square", PARSE_ERROR, 0, NULL);
	s_square->s_vec_dir = vec_norm(&s_square->s_vec_dir);
	skip_between_param(&str, 0);
	s_square->side_size = parse_float(&str, 1);
	if (s_square->side_size <= 0.0)
		error_end("Invalid square side size", PARSE_ERROR, 0, NULL);
	s_square->side_half = s_square->side_size * 0.5;
	s_square->s_material = parse_material_param(&str);
}

void	parse_cylinder(char *str, t_stage *s_stage)
{
	t_cylinder	*s_cylinder;

	skip_between_param(&str, 0);
	malloc_void((void **)&s_cylinder, sizeof(t_cylinder));
	ft_lst_obj_add_front(&(s_stage->s_lst_objs),
				ft_lst_obj_new(s_cylinder, OBJ_CYLINDER, inter_cylinder));
	s_cylinder->s_vec_o = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_cylinder->s_vec_dir = parse_coordinates(&str);
	if (ft_fabs(s_cylinder->s_vec_dir.x) > 1 ||
		ft_fabs(s_cylinder->s_vec_dir.y) > 1 ||
		ft_fabs(s_cylinder->s_vec_dir.z) > 1)
		error_end("Incorrect direction obj cylinder", PARSE_ERROR, 0, NULL);
	s_cylinder->s_vec_dir = vec_norm(&s_cylinder->s_vec_dir);
	skip_between_param(&str, 0);
	s_cylinder->diameter = parse_float(&str, 1);
	if (s_cylinder->diameter <= 0.0)
		error_end("Incorrect cylinder diameter", PARSE_ERROR, 0, NULL);
	s_cylinder->radius_pow = powf(s_cylinder->diameter * (float)0.5, 2);
	skip_between_param(&str, 0);
	s_cylinder->height = parse_float(&str, 1);
	if (s_cylinder->height <= 0.0)
		error_end("Incorrect cylinder height", PARSE_ERROR, 0, NULL);
	s_cylinder->height_half = s_cylinder->height * (float)0.5;
	s_cylinder->s_material = parse_material_param(&str);
}

void	parse_triangle(char *str, t_stage *s_stage)
{
	t_triangle	*s_triangle;

	skip_between_param(&str, 0);
	malloc_void((void **)&s_triangle, sizeof(t_triangle));
	ft_lst_obj_add_front(&(s_stage->s_lst_objs),
				ft_lst_obj_new(s_triangle, OBJ_TRIANGLE, inter_triangle));
	s_triangle->s_vec_o_1 = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_triangle->s_vec_o_2 = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_triangle->s_vec_o_3 = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_triangle->s_material = parse_material_param(&str);
	s_triangle->s_vec_edge_1 = vec_sub(&s_triangle->s_vec_o_2,
										&s_triangle->s_vec_o_1);
	s_triangle->s_vec_edge_2 = vec_sub(&s_triangle->s_vec_o_3,
										&s_triangle->s_vec_o_1);
	s_triangle->s_vec_dir = vec_cproduct(&s_triangle->s_vec_edge_1,
											&s_triangle->s_vec_edge_2);
	s_triangle->s_vec_dir = vec_norm(&s_triangle->s_vec_dir);
}
