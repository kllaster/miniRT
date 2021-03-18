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

int			ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	i = 0;
	while ((str1[i] || str2[i]) && n > i)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		++i;
	}
	return (0);
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

int			ft_atoi_pos(char **str, int error)
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
		error_end("No mantissa: ft_atoi_pos_mantissa()", PARSE_ERROR, 0, NULL);
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

t_lst		*ft_lst_new(void *content)
{
	t_lst	*s_lst;

	if (!(s_lst = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	s_lst->content = content;
	s_lst->next = NULL;
	return (s_lst);
}

void		ft_lst_add_front(t_lst **s_lst_src, t_lst *s_lst_new)
{
	if (!(*s_lst_src))
	{
		*s_lst_src = s_lst_new;
		return ;
	}
	s_lst_new->next = *s_lst_src;
	*s_lst_src = s_lst_new;
}

void		ft_lst_add_back(t_lst **s_lst_src, t_lst *s_lst_new)
{
	t_lst	*s_lst_last;

	if (!(*s_lst_src))
	{
		*s_lst_src = s_lst_new;
		return ;
	}
	s_lst_last = *s_lst_src;
	while (s_lst_last->next)
		s_lst_last = s_lst_last->next;
	s_lst_last->next = s_lst_new;
}

void		ft_lst_cpy(t_lst **s_lst_dest, t_lst *s_lst_src,
							void *(*f_content_cpy)(void *))
{
	t_lst		*s_lst_new;

	if (!s_lst_src)
		return ;
	*s_lst_dest = NULL;
	s_lst_new = NULL;
	while (s_lst_src)
	{
		if (*s_lst_dest)
		{
			s_lst_new->next = ft_lst_new(f_content_cpy(s_lst_src->content));
			s_lst_new = s_lst_new->next;
		}
		else
		{
			s_lst_new = ft_lst_new(f_content_cpy(s_lst_src->content));
			*s_lst_dest = s_lst_new;
		}
		s_lst_src = s_lst_src->next;
	}
}

void		ft_lst_func(t_lst *s_lst, void (*func)(void *))
{
	if (!s_lst)
		return ;
	while (s_lst)
	{
		func(s_lst->content);
		s_lst = s_lst->next;
	}
}

void		ft_end_lst_obj(t_lst_objs **s_lst_src)
{
	t_lst_objs *last;

	last = *s_lst_src;
	while (last->next)
		last = last->next;
	last->next = *s_lst_src;
	(*s_lst_src)->prev = last;
}

t_lst_objs	*ft_lst_obj_new(void *content, char type, void (*func_inter)())
{
	t_lst_objs	*s_lst_obj;

	if (!(s_lst_obj = (t_lst_objs *)malloc(sizeof(t_lst_objs))))
		return (NULL);
	s_lst_obj->func_inter = func_inter;
	s_lst_obj->content = content;
	s_lst_obj->type = type;
	s_lst_obj->next = NULL;
	s_lst_obj->prev = NULL;
	return (s_lst_obj);
}

void		ft_lst_obj_add_front(t_lst_objs **s_lst_src, t_lst_objs *s_lst_new)
{
	if (!(*s_lst_src))
	{
		*s_lst_src = s_lst_new;
		return ;
	}
	s_lst_new->next = *s_lst_src;
	(*s_lst_src)->prev = s_lst_new;
	*s_lst_src = s_lst_new;
}

void		ft_lst_obj_func(t_lst_objs *s_lst_objs, void (*func)(void *))
{
	t_lst_objs	*s_lst_obj_prev;

	if (!s_lst_objs)
		return ;
	s_lst_obj_prev = s_lst_objs->prev;
	while (s_lst_objs != s_lst_obj_prev &&
			s_lst_obj_prev != s_lst_objs->next)
	{
		func(s_lst_objs->content);
		func(s_lst_obj_prev->content);
		s_lst_objs = s_lst_objs->next;
		s_lst_obj_prev = s_lst_obj_prev->prev;
	}
	func(s_lst_objs->content);
	if (s_lst_obj_prev == s_lst_objs->next && s_lst_objs->next != s_lst_objs)
		func(s_lst_obj_prev->content);
}

void		putstr_fd(int fd, char *str)
{
	while (*str)
	{
		write(fd, str, 1);
		++str;
	}
}

void		error_end(char *str_error, int exit_code, int flag, void *s_rt)
{
	static void	*p_rt = NULL;

	if (flag == 1)
		p_rt = s_rt;
	else
	{
		if (p_rt)
			free_rt(p_rt);
		putstr_fd(2, str_error);
		putstr_fd(2, "\n");
		exit(exit_code);
	}
}
