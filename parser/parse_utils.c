#include "mini_rt.h"

void			check_next_arg(char **str)
{
	if (**str == ',')
		(*str)++;
	else
		error_end("Ошибка в проверке на след. аргумент", 1);
}

void			skip_between_arg(char **str)
{
	(*str)++;
	while (**str)
	{
		if (*(*str) == '\t' || *(*str) == ' ')
			(*str)++;
		else if ((*(*str) >= '0' && *(*str) <= '9') ||
			*(*str) == '-' || *(*str) == '+')
			return ;
		else
			error_end("Ошибка в проверке на след. параметр", 1);
	}
}

double			parse_double(char **str)
{
	int		sign;
	double	mantissa;
	double	num;

	sign = 1;
	if (**str == '-')
		sign = -1;
	num = (double)ft_atoi_pos(str);
	if (num < 0)
		sign = 1;
	if (*(*str) == '.' && (++(*str)))
	{
		mantissa = (double)ft_atoi_pos(str);
		num += (mantissa / pow(10.0, ft_numlen(mantissa)));
		num *= sign;
	}
	return (num);
}

t_rgb			*parse_rgb(char **str)
{
	t_rgb	*s_rgb;

	if (!(s_rgb = malloc(sizeof(t_rgb))))
		error_end("Ошибка выделения памяти parse_rgb", 1);
	ft_bzero(s_rgb, sizeof(s_rgb));
	s_rgb->red = ft_atoi_pos(str);
	if (s_rgb->red < 0 || s_rgb->red > 255)
		error_end("Ошибка в проверке цвета red", 1);
	check_next_arg(str);
	s_rgb->green = ft_atoi_pos(str);
	if (s_rgb->green < 0 || s_rgb->green > 255)
		error_end("Ошибка в проверке цвета green", 1);
	check_next_arg(str);
	s_rgb->blue = ft_atoi_pos(str);
	if (s_rgb->blue < 0 || s_rgb->blue > 255)
		error_end("Ошибка в проверке цвета blue", 1);
	return (s_rgb);
}

t_coordinates	*parse_coordinates(char **str)
{
	t_coordinates *s_coordinates;

	if (!(s_coordinates = malloc(sizeof(t_coordinates))))
		error_end("Ошибка выделения памяти parse_coordinates", 1);
	ft_bzero(s_coordinates, sizeof(s_coordinates));
	s_coordinates->x = parse_double(str);
	check_next_arg(str);
	s_coordinates->y = parse_double(str);
	check_next_arg(str);
	s_coordinates->z = parse_double(str);
	return (s_coordinates);
}

t_angle			*parse_angle(char **str)
{
	t_angle	*s_angle;

	if (!(s_angle = malloc(sizeof(t_angle))))
		error_end("Ошибка выделения памяти parse_angle", 1);
	ft_bzero(s_angle, sizeof(s_angle));
	s_angle->x = parse_double(str);
	check_next_arg(str);
	s_angle->y = parse_double(str);
	check_next_arg(str);
	s_angle->z = parse_double(str);
	return (s_angle);
}
