#ifndef UTILS_H
# define UTILS_H

# include "mini_rt.h"

enum	e_errors {
	MALLOC_ERROR = 1,
	PARSE_ERROR = 2,
	MLX_ERROR = 3,
	THREAD_ERROR = 4,
	SAVE_ERROR = 5
};

typedef struct		s_lst_objs
{
	struct s_lst_objs	*next;
	struct s_lst_objs	*prev;
	void				*content;
	void				(*func_inter)();
	char				type;
}					t_lst_objs;

typedef struct		s_lst
{
	void			*content;
	struct s_lst	*next;
}					t_lst;

void				malloc_void(void **p, size_t size);
void				error_end(char *str_error, int exit_code, int flag,
								void *s_rt);
void				putstr_fd(int fd, char *str);
float				ft_fabs(float num);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_strequal_end(char *str, char *end);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *source, size_t count);
t_lst				*ft_lst_new(void *content);
void				ft_lst_add_front(t_lst **s_lst_src, t_lst *s_lst_new);
void				ft_lst_add_back(t_lst **s_lst_src, t_lst *new);
void				ft_lst_map(t_lst *s_lst, void (*func)(void *));
t_lst_objs			*ft_lst_obj_new(void *content, char type,
										void (*func_inter)());
void				ft_lst_obj_add_front(t_lst_objs **s_lst_src,
											t_lst_objs *s_lst_new);
void				ft_end_lst_obj(t_lst_objs **s_lst_src);
void				ft_lst_obj_map(t_lst_objs *s_lst_objs,
									void (*func)(void *));

#endif
