#include "mini_rt.h"

long long int	time_unix_ms(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return (s_time.tv_sec * 1000 + (int)(s_time.tv_usec * 0.001));
}

float		ft_fabs(float num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int			ft_numlen(int num)
{
	int i;

	if (!num)
		return (1);
	i = 1;
	while ((num = (int)(num * 0.1)))
		++i;
	return (i);
}

int			ft_strequal_end(char *str, char *end)
{
	int i;
	int a;

	if (!str)
		return (0);
	a = ft_strlen(end);
	i = ft_strlen(str);
	while (i >= 0 && a >= 0 && str[i] == end[a])
	{
		--i;
		--a;
	}
	if (a == -1)
		return (1);
	return (0);
}

void		ft_bzero(void *s, size_t n)
{
	size_t i;

	if (!s)
		return ;
	i = -1;
	while (++i < n)
	{
		*((char *)s) = 0;
		++s;
	}
}

int			ft_atoi_pos(char **str)
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
	else
		error_end("Нет числа", PARSE_ERROR);
	return ((int)res * sign);
}

float		ft_atoi_pos_mantissa(char **str)
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
		error_end("Нет мантиссы", PARSE_ERROR);
	return (res);
}

void		*ft_memcpy(void *dest, const void *source, size_t count)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (dest == source)
		return (dest);
	i = -1;
	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)source;
	while (++i != count)
		p1[i] = p2[i];
	return (dest);
}

t_list		*ft_list_new(void *content)
{
	t_list	*s_list;

	if (!(s_list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	s_list->content = content;
	s_list->next = NULL;
	return (s_list);
}

void		ft_list_add_front(t_list **s_list_src, t_list *s_list_new)
{
	if (!(*s_list_src))
	{
		*s_list_src = s_list_new;
		return ;
	}
	s_list_new->next = *s_list_src;
	*s_list_src = s_list_new;
}

void		ft_list_add_back(t_list **s_list_src, t_list *s_list_new)
{
	t_list	*s_list_last;

	if (!(*s_list_src))
	{
		*s_list_src = s_list_new;
		return ;
	}
	s_list_last = *s_list_src;
	while (s_list_last->next)
		s_list_last = s_list_last->next;
	s_list_last->next = s_list_new;
}

void		ft_list_cpy(t_list **s_list_dest, t_list *s_list_src,
							void *(*f_content_cpy)(void *))
{
	t_list		*s_list_new;

	if (!s_list_src)
		return ;
	*s_list_dest = NULL;
	s_list_new = NULL;
	while (s_list_src)
	{
		if (*s_list_dest)
		{
			s_list_new->next = ft_list_new(f_content_cpy(s_list_src->content));
			s_list_new = s_list_new->next;
		}
		else
		{
			s_list_new = ft_list_new(f_content_cpy(s_list_src->content));
			*s_list_dest = s_list_new;
		}
		s_list_src = s_list_src->next;
	}
}

t_list_objs	*ft_list_obj_new(void *content, unsigned char type)
{
	t_list_objs	*s_list_obj;

	if (!(s_list_obj = (t_list_objs *)malloc(sizeof(t_list_objs))))
		return (NULL);
	s_list_obj->type = type;
	s_list_obj->content = content;
	s_list_obj->next = NULL;
	return (s_list_obj);
}

void		ft_list_obj_add_front(t_list_objs **s_list_src,
									t_list_objs *s_list_new)
{
	if (!(*s_list_src))
	{
		*s_list_src = s_list_new;
		return ;
	}
	s_list_new->next = *s_list_src;
	*s_list_src = s_list_new;
}

void		ft_list_obj_add_back(t_list_objs **s_list_src,
									t_list_objs *s_list_new)
{
	t_list_objs *last;

	if (!(*s_list_src))
	{
		(*s_list_src) = s_list_new;
		return ;
	}
	last = *s_list_src;
	while (last->next)
		last = last->next;
	last->next = s_list_new;
}

void		putstr_fd(int fd, char *str)
{
	while (*str)
	{
		write(fd, str, 1);
		++str;
	}
}

void		error_end(char *str_error, int exit_code)
{
	putstr_fd(2, str_error);
	putstr_fd(2, "\n");
	exit(exit_code);
}
