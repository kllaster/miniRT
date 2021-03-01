#include "mini_rt.h"

void	create_threads_data(t_rt *s_rt)
{
	int	i;
	int	width_thread;

	width_thread = s_rt->s_stage.s_screen.width / COUNT_THREADS;
	i = -1;
	while (++i < COUNT_THREADS)
	{
		ft_memcpy(&s_rt->s_thread_data[i], &s_rt->s_stage, sizeof(t_stage) - sizeof(t_list *));
		s_rt->s_thread_data[i].s_main_camera = s_rt->s_stage.s_main_camera;
		ft_list_cpy(&s_rt->s_thread_data[i].s_list_lights, s_rt->s_stage.s_list_lights, light_cpy);
		ft_list_obj_cpy(&s_rt->s_thread_data[i].s_list_objs, s_rt->s_stage.s_list_objs);
		s_rt->s_thread_data[i].start_x = width_thread * i;
		if (i + 1 != COUNT_THREADS)
			s_rt->s_thread_data[i].end_x = s_rt->s_thread_data[i].start_x + width_thread;
		else
			s_rt->s_thread_data[i].end_x = s_rt->s_stage.s_screen.width;
	}
}

int		start_render(t_rt *s_rt)
{
	int			i;

	i = -1;
	s_rt->render_now = 1;
	while (++i < COUNT_THREADS)
		if (pthread_create(&s_rt->threads[i], NULL, render, &(s_rt->s_thread_data[i])) != 0)
			error_end("Ошибка при создании потока create_threads", THREAD_ERROR);
	i =	-1;
	while (++i < COUNT_THREADS)
		pthread_join(s_rt->threads[i], NULL);
	s_rt->s_stage.s_main_camera->render_ready = 1;
	s_rt->render_now = 0;
	return (0);
}
