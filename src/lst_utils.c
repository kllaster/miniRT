#include "mini_rt.h"

t_lst		*ft_lst_new(void *content)
{
	t_lst	*s_lst;

	malloc_void((void **)&s_lst, sizeof(t_lst));
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

void		ft_lst_map(t_lst *s_lst, void (*func)(void *))
{
	if (!s_lst)
		return ;
	while (s_lst)
	{
		func(s_lst->content);
		s_lst = s_lst->next;
	}
}
