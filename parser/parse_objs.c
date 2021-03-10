#include "mini_rt.h"

void	parse_sphere(char *str, t_stage *s_stage)
{
	t_sphere	*s_sphere;

	if ((s_sphere = malloc(sizeof(t_sphere))) == NULL)
		error_end("Memory allocation error: parse_sphere()",
					MALLOC_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_sphere->s_vec_origin = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_sphere->radius_pow = parse_float(&str);
	if (s_sphere->radius_pow <= 0.0)
		error_end("Incorrect sphere diameter", PARSE_ERROR, 0, NULL);
	s_sphere->radius_pow *= (float)0.5;
	s_sphere->radius_pow *= s_sphere->radius_pow;
	skip_between_param(&str, 0);
	s_sphere->s_color = parse_rgb(&str);
	ft_list_obj_add_front(&(s_stage->s_list_objs),
							ft_list_obj_new(s_sphere, OBJ_SPHERE));
}

void	parse_plane(char *str, t_stage *s_stage)
{
	t_plane	*s_plane;

	if ((s_plane = malloc(sizeof(t_plane))) == NULL)
		error_end("Memory allocation error: parse_plane()",
					MALLOC_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_plane->s_vec_origin = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_plane->s_vec_dir = parse_coordinates(&str);
	if (ft_fabs(s_plane->s_vec_dir.x) > 1 ||
		ft_fabs(s_plane->s_vec_dir.y) > 1 ||
		ft_fabs(s_plane->s_vec_dir.z) > 1)
		error_end("Incorrect direction obj plane",
					PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_plane->s_color = parse_rgb(&str);
	ft_list_obj_add_front(&(s_stage->s_list_objs),
							ft_list_obj_new(s_plane, OBJ_PLANE));
}

void	parse_square(char *str, t_stage *s_stage)
{
	t_square	*s_square;

	if ((s_square = malloc(sizeof(t_square))) == NULL)
		error_end("Memory allocation error: parse_square()",
					MALLOC_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_square->s_vec_origin = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_square->s_vec_dir = parse_coordinates(&str);
	if (ft_fabs(s_square->s_vec_dir.x) > 1 ||
		ft_fabs(s_square->s_vec_dir.y) > 1 ||
		ft_fabs(s_square->s_vec_dir.z) > 1)
		error_end("Incorrect direction obj square", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_square->side_size = parse_float(&str);
	if (s_square->side_size <= 0.0)
		error_end("Invalid square side size", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_square->s_color = parse_rgb(&str);
	ft_list_obj_add_front(&(s_stage->s_list_objs),
							ft_list_obj_new(s_square, OBJ_SQUARE));
}

void	parse_cylinder(char *str, t_stage *s_stage)
{
	t_cylinder	*s_cylinder;

	if ((s_cylinder = malloc(sizeof(t_cylinder))) == NULL)
		error_end("Memory allocation error: parse_cylinder()",
					MALLOC_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_cylinder->s_vec_origin = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_cylinder->s_vec_dir = parse_coordinates(&str);
	if (ft_fabs(s_cylinder->s_vec_dir.x) > 1 ||
		ft_fabs(s_cylinder->s_vec_dir.y) > 1 ||
		ft_fabs(s_cylinder->s_vec_dir.z) > 1)
		error_end("Incorrect direction obj cylinder", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_cylinder->diameter = parse_float(&str);
	if (s_cylinder->diameter <= 0.0)
		error_end("Incorrect cylinder diameter", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_cylinder->height = parse_float(&str);
	if (s_cylinder->height <= 0.0)
		error_end("Incorrect cylinder height", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_cylinder->s_color = parse_rgb(&str);
	ft_list_obj_add_front(&(s_stage->s_list_objs),
							ft_list_obj_new(s_cylinder, OBJ_CYLINDER));
}

void	parse_triangle(char *str, t_stage *s_stage)
{
	t_triangle	*s_triangle;

	if ((s_triangle = malloc(sizeof(t_triangle))) == NULL)
		error_end("Memory allocation error: parse_triangle()",
					MALLOC_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_triangle->s_vec_origin_1 = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_triangle->s_vec_origin_2 = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_triangle->s_vec_origin_3 = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_triangle->s_color = parse_rgb(&str);
	s_triangle->s_vec_edge_1 = vec_sub(&s_triangle->s_vec_origin_2, &s_triangle->s_vec_origin_1);
	s_triangle->s_vec_edge_2 = vec_sub(&s_triangle->s_vec_origin_3, &s_triangle->s_vec_origin_1);
	s_triangle->s_vec_dir = vec_cross_product(&s_triangle->s_vec_edge_1, &s_triangle->s_vec_edge_2);
	s_triangle->s_vec_dir = vec_norm(&s_triangle->s_vec_dir);
	ft_list_obj_add_front(&(s_stage->s_list_objs),
							ft_list_obj_new(s_triangle, OBJ_TRIANGLE));
}

void	parse_objs(char *str, t_stage *s_stage)
{
	if (str[0] == 's' && str[1] == 'p' &&
		(str[2] == ' ' || str[2] == '\t') && (str += 2))
		parse_sphere(str, s_stage);
	else if (str[0] == 'p' && str[1] == 'l' &&
		(str[2] == ' ' || str[2] == '\t') && (str += 2))
		parse_plane(str, s_stage);
	else if (str[0] == 's' && str[1] == 'q' &&
			(str[2] == ' ' || str[2] == '\t') && (str += 2))
		parse_square(str, s_stage);
	else if (str[0] == 'c' && str[1] == 'y' &&
			(str[2] == ' ' || str[2] == '\t') && (str += 2))
		parse_cylinder(str, s_stage);
	else if (str[0] == 't' && str[1] == 'r' &&
			(str[2] == ' ' || str[2] == '\t') && (str += 2))
		parse_triangle(str, s_stage);
}
