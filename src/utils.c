#include "mini_rt.h"

void	free_rt(t_rt *s_rt)
{
	t_lst	*s_lst_cams;

	if (s_rt->mlx_p)
	{
		s_lst_cams = s_rt->s_stage.s_lst_cams;
		while (s_lst_cams)
		{
			if (((t_cam *)s_lst_cams->content)->s_mlx_img.img_ptr)
				mlx_destroy_image(s_rt->mlx_p,
						((t_cam *)s_lst_cams->content)->s_mlx_img.img_ptr);
			s_lst_cams = s_lst_cams->next;
		}
		if (s_rt->mlx_window)
			mlx_destroy_window(s_rt->mlx_p, s_rt->mlx_window);
	}
	if (s_rt->s_stage.s_ambient_color)
		free(s_rt->s_stage.s_ambient_color);
	if (s_rt->s_stage.s_lst_lights)
		ft_lst_map(s_rt->s_stage.s_lst_lights, free);
	if (s_rt->s_stage.s_lst_cams)
		ft_lst_map(s_rt->s_stage.s_lst_cams, free);
	if (s_rt->s_stage.s_lst_objs)
		ft_lst_obj_map(s_rt->s_stage.s_lst_objs, free);
}

int		end_rt(t_rt *s_rt)
{
	free_rt(s_rt);
	exit(0);
}

void	malloc_void(void **p, size_t size)
{
	if ((*p = malloc(size)) == NULL)
		error_end("Memory allocation error",
			MALLOC_ERROR, 0, NULL);
}

void	putstr_fd(int fd, char *str)
{
	while (*str)
	{
		write(fd, str, 1);
		++str;
	}
}

void	error_end(char *str_error, int exit_code, int flag, void *s_rt)
{
	static void	*p_rt = NULL;

	if (flag == 1)
		p_rt = s_rt;
	else
	{
		if (p_rt)
			free_rt(p_rt);
		putstr_fd(2, "\n\n");
		putstr_fd(2, str_error);
		putstr_fd(2, "\n");
		exit(exit_code);
	}
}
