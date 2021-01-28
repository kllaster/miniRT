#include "mini_rt.h"

void	parse_sphere(char *str, t_stage *s_stage)
{
	t_sphere	s_sphere;

	skip_between_arg(&str);
	s_sphere.s_coordinates = parse_coordinates(&str);
	skip_between_arg(&str);
	s_sphere.diameter = parse_float(&str);
	skip_between_arg(&str);
	s_sphere.s_color = parse_rgb(&str);
	ft_lstadd_back(&(s_stage->s_list_objs), ft_lstnew(&s_sphere));
}

void	parse_plane(char *str, t_stage *s_stage)
{
	t_plane	s_plane;

	skip_between_arg(&str);
	s_plane.s_coordinates = parse_coordinates(&str);
	skip_between_arg(&str);
	s_plane.s_angle = parse_angle(&str);
	skip_between_arg(&str);
	s_plane.s_color = parse_rgb(&str);
	ft_lstadd_back(&(s_stage->s_list_objs), ft_lstnew(&s_plane));
}

void	parse_objs(char *str, t_stage *s_stage)
{
	if (str[0] == 's' && str[1] == 'p' && (str += 2))
		parse_sphere(str, s_stage);
	else if (str[0] == 'p' && str[1] == 'l' && (str += 2))
		parse_plane(str, s_stage);
}
