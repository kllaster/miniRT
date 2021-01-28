#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				error_end(char *str_error, int exit_code);
int					ft_numlen(int num);
int					ft_strequal_end(char *str, char *end);
void				ft_bzero(void *s, size_t n);
int					ft_atoi_pos(char **str);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **g_list, t_list *new);

#endif
