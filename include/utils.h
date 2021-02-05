#ifndef UTILS_H
# define UTILS_H

# include "mini_rt.h"

void				error_end(char *str_error, int exit_code);
int					ft_numlen(int num);
int					ft_strequal_end(char *str, char *end);
void				ft_bzero(void *s, size_t n);
int					ft_atoi_pos(char **str);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **g_list, t_list *new);
t_list_objs			*ft_lstnew_obj(void *content, unsigned char type);
void				ft_lstadd_back_obj(t_list_objs **g_list, t_list_objs *new);

#endif
