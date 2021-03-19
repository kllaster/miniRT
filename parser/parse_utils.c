#include "mini_rt.h"

t_material	parse_material_param(char **str)
{
	t_material	s_material;

	s_material.s_color = parse_rgb(str);
	s_material.ref_coeff = parse_float(str, 0);
	if (s_material.ref_coeff < 0 || s_material.ref_coeff > 1)
		error_end("Error: ref_coeff [0, 1]", PARSE_ERROR, 0, NULL);
	return (s_material);
}

void		check_next_arg(char **str)
{
	if (**str == ',')
		++(*str);
	else
	{
		skip_between_param(str, ',');
		if (**str == ',')
			++(*str);
		else
		{
			printf("\n ---> \"%s\"", *str);
			error_end("Error checking the next argument", PARSE_ERROR, 0, NULL);
		}
	}
}

void		skip_between_param(char **str, char symb)
{
	++(*str);
	while (**str)
	{
		if (*(*str) == '\t' || *(*str) == ' ')
			++(*str);
		else if ((*(*str) >= '0' && *(*str) <= '9') ||
			*(*str) == '-' || *(*str) == '+' || *(*str) == symb)
			return ;
		else
		{
			printf("\n ---> \"%s\"", *str);
			error_end("Error checking the next parameter",
						PARSE_ERROR, 0, NULL);
		}
	}
}

t_rgb		parse_rgb(char **str)
{
	t_rgb	s_rgb;

	s_rgb.red = ft_atoi_pos(str, 1);
	if (s_rgb.red < 0 || s_rgb.red > 255)
		error_end("Error checking red color", PARSE_ERROR, 0, NULL);
	check_next_arg(str);
	s_rgb.green = ft_atoi_pos(str, 1);
	if (s_rgb.green < 0 || s_rgb.green > 255)
		error_end("Error checking green color", PARSE_ERROR, 0, NULL);
	check_next_arg(str);
	s_rgb.blue = ft_atoi_pos(str, 1);
	if (s_rgb.blue < 0 || s_rgb.blue > 255)
		error_end("Error checking blue color", PARSE_ERROR, 0, NULL);
	return (s_rgb);
}

t_vec		parse_coordinates(char **str)
{
	t_vec	s_vec;

	s_vec.x = parse_float(str, 1);
	check_next_arg(str);
	s_vec.y = parse_float(str, 1);
	check_next_arg(str);
	s_vec.z = parse_float(str, 1);
	return (s_vec);
}
