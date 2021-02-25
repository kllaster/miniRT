#include "mini_rt.h"

void	change_img_window(t_stage *s_stage)
{
	if (s_stage->s_selected_camera->render_ready == 1)
	{
		mlx_put_image_to_window(s_stage->mlx_p, s_stage->mlx_window,
						s_stage->s_selected_camera->s_mlx_img.img, 0, 0);
	}
	else
		render(s_stage);
}

int		key_hook(int keycode, t_stage *s_stage)
{
	(void)s_stage;
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_SPACE)
	{
		get_another_camera(s_stage);
		change_img_window(s_stage);
	}
	return (1);
}