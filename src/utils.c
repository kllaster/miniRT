#include "mini_rt.h"

int			ft_numlen(int num)
{
	int i;

	if (!num)
		return (1);
	i = 1;
	while (num /= 10)
		i++;
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
		s++;
	}
}

int			ft_atoi_pos(char **str)
{
	unsigned int	res;
	int				sign;

	res = 0;
	sign = 1;
	if (*(*str) == '-' || *(*str) == '+')
		sign = (*(*str)++ == '-') ? -1 : 1;
	while (*(*str) >= '0' && *(*str) <= '9')
	{
		if ((res * 10) < res)
			return ((sign < 1) ? 0 : -1);
		res = res * 10 + (*(*str)++ - '0');
	}
	return ((int)res * sign);
}

t_list		*ft_lstnew(void *content)
{
	t_list	*s_list;

	if (!(s_list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	s_list->content = content;
	s_list->next = NULL;
	return (s_list);
}

void		ft_lstadd_back(t_list **g_list, t_list *new)
{
	t_list		*last;

	if (!(*g_list))
	{
		(*g_list) = new;
		return ;
	}
	last = *g_list;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_list_objs	*ft_lstnew_obj(void *content, unsigned char type)
{
	t_list_objs	*s_list_obj;

	if (!(s_list_obj = (t_list_objs *)malloc(sizeof(t_list_objs))))
		return (NULL);
	s_list_obj->type = OBJ_NONE;
	s_list_obj->type |= type;
	s_list_obj->content = content;
	s_list_obj->next = NULL;
	return (s_list_obj);
}

void		ft_lstadd_back_obj(t_list_objs **g_list, t_list_objs *new)
{
	t_list_objs *last;

	if (!(*g_list))
	{
		(*g_list) = new;
		return ;
	}
	last = *g_list;
	while (last->next)
		last = last->next;
	last->next = new;
}

void		putstr_fd(int fd, char *str)
{
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

void		error_end(char *str_error, int exit_code)
{
	putstr_fd(2, str_error);
	putstr_fd(2, "\n");
	exit(exit_code);
}
