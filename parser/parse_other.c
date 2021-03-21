#include "mini_rt.h"

void	parse_objs(char *str, t_stage *s_stage)
{
	if (str[0] == 's' && str[1] == 'p')
		parse_sphere(&str[3], s_stage);
	else if (str[0] == 'p' && str[1] == 'l')
		parse_plane(&str[3], s_stage);
	else if (str[0] == 's' && str[1] == 'q')
		parse_square(&str[3], s_stage);
	else if (str[0] == 'c' && str[1] == 'y')
		parse_cylinder(&str[3], s_stage);
	else if (str[0] == 't' && str[1] == 'r')
		parse_triangle(&str[3], s_stage);
	else
		error_end("Error unknown character", PARSE_ERROR, 0, NULL);
}

float	parse_float(char **str, int error)
{
	float	sign;
	float	num;

	sign = 1;
	while (**str)
	{
		if (*(*str) == '\t' || *(*str) == ' ')
			++(*str);
		else if ((*(*str) >= '0' && *(*str) <= '9') ||
					*(*str) == '-' || *(*str) == '+')
			break ;
		else if (error)
			error_end("Error parse_float", PARSE_ERROR, 0, NULL);
		else
			break ;
	}
	if (**str == '-')
		sign = -1;
	num = (float)ft_atoi_pos(str, error);
	if (num < 0)
		num *= sign = -1;
	if (*(*str) == '.' && (++(*str)))
		num += ft_atoi_pos_mantissa(str);
	return (num * sign);
}

int		ft_atoi_pos(char **str, int error)
{
	unsigned int	res;
	int				sign;

	res = 0;
	sign = 1;
	while (*(*str) == '\t' || *(*str) == '\v'
			|| *(*str) == '\f' || *(*str) == '\r'
			|| *(*str) == ' ')
		++(*str);
	if (*(*str) == '-' || *(*str) == '+')
		sign = (*(*str)++ == '-') ? -1 : 1;
	if (*(*str) >= '0' && *(*str) <= '9')
	{
		while (*(*str) >= '0' && *(*str) <= '9')
		{
			if ((res * 10) < res)
				return ((sign < 1) ? 0 : -1);
			res = res * 10 + (*(*str)++ - '0');
		}
	}
	else if (error)
		error_end("No number: ft_atoi_pos()", PARSE_ERROR, 0, NULL);
	return ((int)res * sign);
}

float	ft_atoi_pos_mantissa(char **str)
{
	float	len;
	float	res;

	res = 0;
	while (*(*str) == '\t' || *(*str) == '\v'
			|| *(*str) == '\f' || *(*str) == '\r'
			|| *(*str) == ' ')
		++(*str);
	if (*(*str) >= '0' && *(*str) <= '9')
	{
		len = 0;
		while (*(*str) >= '0' && *(*str) <= '9')
		{
			++len;
			res += powf((float)0.1, len) * (float)(*(*str)++ - '0');
		}
	}
	else
		error_end("No mantissa: ft_atoi_pos_mantissa()", PARSE_ERROR, 0, NULL);
	return (res);
}
