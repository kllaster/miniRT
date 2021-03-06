#include "mini_rt.h"

void	change_frame(t_rt *s_rt, void *img_old_p)
{
	if (s_rt->s_stage.s_main_camera->render_ready == 0)
		start_render(s_rt);
	mlx_clear_window(s_rt->mlx_p, s_rt->mlx_window);
	mlx_put_image_to_window(s_rt->mlx_p, s_rt->mlx_window,
							s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr, 0, 0);
	debug_window_put_camera(s_rt);
	if (img_old_p != NULL)
		mlx_destroy_image(s_rt->mlx_p, img_old_p);
}

int		new_frame(t_rt *s_rt)
{
	static int				update = 0;
	void					*img_old_p;

	update = check_hooks(s_rt);
	if (update && !s_rt->render_now)
	{
		img_old_p = s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr;
		if ((s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr = mlx_new_image(s_rt->mlx_p,
																			s_rt->s_stage.s_screen.width,
																			s_rt->s_stage.s_screen.height)) == NULL)
			error_end("Ошибка при mlx_new_image()", MLX_ERROR);
		if ((s_rt->s_stage.s_main_camera->s_mlx_img.addr =
					mlx_get_data_addr(s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr,
										&(s_rt->s_stage.s_main_camera->s_mlx_img.bits_per_pixel),
										&(s_rt->s_stage.s_main_camera->s_mlx_img.line_length),
										&(s_rt->s_stage.s_main_camera->s_mlx_img.endian))) == NULL)
			error_end("Ошибка при mlx_get_data_addr()", MLX_ERROR);
		s_rt->s_stage.s_main_camera->render_ready = 0;
		change_frame(s_rt, img_old_p);
		update = 0;
	}
	return (0);
}
