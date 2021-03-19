#include "mini_rt.h"

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

	malloc_void((void **)&s_lst_obj, sizeof(t_lst_objs));
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

void		ft_lst_obj_map(t_lst_objs *s_lst_objs, void (*func)(void *))
{
	t_lst_objs	*s_lst_obj_prev;

	if (!s_lst_objs)
		return ;
	s_lst_obj_prev = s_lst_objs->prev;
	while (s_lst_objs != s_lst_obj_prev &&
			(s_lst_obj_prev && s_lst_objs != s_lst_obj_prev->prev))
	{
		func(s_lst_objs->content);
		if (s_lst_obj_prev != NULL)
			func(s_lst_obj_prev->content);
		s_lst_objs = s_lst_objs->next;
		if (s_lst_obj_prev != NULL)
			s_lst_obj_prev = s_lst_obj_prev->prev;
	}
	func(s_lst_objs->content);
	if ((s_lst_obj_prev && s_lst_objs == s_lst_obj_prev->prev) &&
		s_lst_objs != s_lst_obj_prev)
		func(s_lst_obj_prev->content);
}
