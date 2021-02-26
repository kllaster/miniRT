#include "mini_rt.h"

void	change_img_window(t_rt *s_rt)
{
	if (s_rt->s_stage.s_selected_camera->render_ready == 1)
	{
		mlx_put_image_to_window(s_rt->mlx_p, s_rt->mlx_window,
							s_rt->s_stage.s_selected_camera->s_mlx_img.img, 0, 0);
	}
	else
		start_render(s_rt);
}

int		key_hook(int keycode, t_rt *s_rt)
{
	int	i;

	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_SPACE)
	{
		get_another_camera(s_rt);
		i = -1;
		while (++i < COUNT_THREADS)
			s_rt->s_thread_data[i].s_selected_camera = s_rt->s_stage.s_selected_camera;
		change_img_window(s_rt);
	}
	return (1);
}