#include "mini_rt.h"

void	parse_sphere(char *str, t_stage *s_stage)
{
	t_sphere	*s_sphere;

	if (!(s_sphere = malloc(sizeof(t_sphere))))
		error_end("Ошибка выделения памяти parse_sphere", 1);
	skip_between_arg(&str, 0);
	s_sphere->s_coordinates = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_sphere->diameter = parse_double(&str);
	if (s_sphere->diameter <= 0.0)
		error_end("Неверный диаметр сферы", 1);
	skip_between_arg(&str, 0);
	s_sphere->s_color = parse_rgb(&str);
	ft_lstadd_back_obj(&(s_stage->s_list_objs), ft_lstnew_obj(s_sphere, OBJ_SPHERE));
}

void	parse_plane(char *str, t_stage *s_stage)
{
	t_plane	*s_plane;

	if (!(s_plane = malloc(sizeof(t_sphere))))
		error_end("Ошибка выделения памяти parse_plane", 1);
	skip_between_arg(&str, 0);
	s_plane->s_coordinates = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_plane->s_angle = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_plane->s_color = parse_rgb(&str);
	ft_lstadd_back_obj(&(s_stage->s_list_objs), ft_lstnew_obj(s_plane, OBJ_PLANE));
}

void	parse_square(char *str, t_stage *s_stage)
{
	t_square	*s_square;

	if (!(s_square = malloc(sizeof(t_square))))
		error_end("Ошибка выделения памяти parse_square", 1);
	skip_between_arg(&str, 0);
	s_square->s_coordinates = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_square->s_angle = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_square->side_size = parse_double(&str);
	if (s_square->side_size <= 0.0)
		error_end("Неверный размер стороны куба", 1);
	skip_between_arg(&str, 0);
	s_square->s_color = parse_rgb(&str);
	ft_lstadd_back_obj(&(s_stage->s_list_objs), ft_lstnew_obj(s_square, OBJ_SQUARE));
}

void	parse_cylinder(char *str, t_stage *s_stage)
{
	t_cylinder	*s_cylinder;

	if (!(s_cylinder = malloc(sizeof(t_cylinder))))
		error_end("Ошибка выделения памяти parse_cylinder", 1);
	skip_between_arg(&str, 0);
	s_cylinder->s_coordinates = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_cylinder->s_angle = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_cylinder->s_color = parse_rgb(&str);
	skip_between_arg(&str, 0);
	s_cylinder->diameter = parse_double(&str);
	if (s_cylinder->diameter <= 0.0)
		error_end("Неверный диаметр цилиндра", 1);
	skip_between_arg(&str, 0);
	s_cylinder->height = parse_double(&str);
	if (s_cylinder->height <= 0.0)
		error_end("Неверная высота цилиндра", 1);
	ft_lstadd_back_obj(&(s_stage->s_list_objs), ft_lstnew_obj(s_cylinder, OBJ_CYLINDER));
}

void	parse_triangle(char *str, t_stage *s_stage)
{
	t_triangle	*s_triangle;

	if (!(s_triangle = malloc(sizeof(t_triangle))))
		error_end("Ошибка выделения памяти parse_triangle", 1);
	skip_between_arg(&str, 0);
	s_triangle->s_coordinates_1 = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_triangle->s_coordinates_2 = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_triangle->s_coordinates_3 = parse_coordinates(&str);
	skip_between_arg(&str, 0);
	s_triangle->s_color = parse_rgb(&str);
	ft_lstadd_back_obj(&(s_stage->s_list_objs), ft_lstnew_obj(s_triangle, OBJ_TRIANGLE));
}

void	parse_objs(char *str, t_stage *s_stage)
{
	if (str[0] == 's' && str[1] == 'p' && (str += 2))
		parse_sphere(str, s_stage);
	else if (str[0] == 'p' && str[1] == 'l' && (str += 2))
		parse_plane(str, s_stage);
	else if (str[0] == 's' && str[1] == 'q' && (str += 2))
		parse_square(str, s_stage);
	else if (str[0] == 'c' && str[1] == 'y' && (str += 2))
		parse_cylinder(str, s_stage);
	else if (str[0] == 't' && str[1] == 'r' && (str += 2))
		parse_triangle(str, s_stage);
}
