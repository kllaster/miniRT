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

typedef struct		s_list_objs
{
	void				*content;
	struct s_list_objs	*next;
	char				type;
}					t_list_objs;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				error_end(char *str_error, int exit_code, int flag, void *s_rt);
void				putstr_fd(int fd, char *str);
float				ft_fabs(float num);
int					ft_numlen(int num);
long long int		time_unix_ms();
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_strequal_end(char *str, char *end);
void				ft_bzero(void *s, size_t n);
int					ft_atoi_pos(char **str, int error);
float				ft_atoi_pos_mantissa(char **str);
void				*ft_memcpy(void *dest, const void *source, size_t count);
t_list				*ft_list_new(void *content);
void				ft_list_add_front(t_list **s_list_src, t_list *s_list_new);
void				ft_list_add_back(t_list **s_list_src, t_list *new);
void				ft_list_cpy(t_list **s_list_dest, t_list *s_list_src, void *(*f_content_cpy)(void *));
void				ft_list_func(t_list *s_list, void (*func)(void *));
t_list_objs			*ft_list_obj_new(void *content, unsigned char type);
void				ft_list_obj_add_front(t_list_objs **s_list_src, t_list_objs *s_list_new);
void				ft_list_obj_add_back(t_list_objs **s_list_src, t_list_objs *new);
void				ft_list_obj_func(t_list_objs *s_list_objs, void (*func)(void *));

#endif
