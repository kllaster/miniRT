#include "mini_rt.h"

void	create_threads_data(t_rt *s_rt)
{
	int	i;
	int	height_thread;

	height_thread = s_rt->s_stage.height / COUNT_THREADS;
	i = -1;
	while (++i < COUNT_THREADS)
	{
		ft_memcpy(&s_rt->s_tdata[i], &s_rt->s_stage,
					sizeof(t_stage) - sizeof(t_lst *));
		s_rt->s_tdata[i].s_main_cam = s_rt->s_stage.s_main_cam;
		s_rt->s_tdata[i].start_y = height_thread * i;
		if (i + 1 != COUNT_THREADS)
			s_rt->s_tdata[i].end_y = s_rt->s_tdata[i].start_y + height_thread;
		else
			s_rt->s_tdata[i].end_y = s_rt->s_stage.height;
	}
}

int		start_render(t_rt *s_rt)
{
	int	i;

	i = -1;
	if (COUNT_THREADS > 1)
	{
		while (++i < COUNT_THREADS)
			if (pthread_create(&s_rt->threads[i], NULL, render,
								&(s_rt->s_tdata[i])) != 0)
				error_end("Error while creating thread: start_render()",
							THREAD_ERROR, 0, NULL);
		i = -1;
		while (++i < COUNT_THREADS)
			pthread_join(s_rt->threads[i], NULL);
	}
	else
		render(&s_rt->s_tdata[0]);
	s_rt->s_stage.s_main_cam->render_ready = 1;
	return (0);
}
