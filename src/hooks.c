#include "mini_rt.h"

void	free_rt(t_rt *s_rt)
{
	if (s_rt->mlx_p)
	{
		if (s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr)
			mlx_destroy_image(s_rt->mlx_p,
							  s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr);
		if (s_rt->mlx_window)
			mlx_destroy_window(s_rt->mlx_p, s_rt->mlx_window);
	}
	if (s_rt->s_stage.s_ambient_color)
		free(s_rt->s_stage.s_ambient_color);
	if (s_rt->s_stage.s_list_lights)
		ft_list_func(s_rt->s_stage.s_list_lights, free);
	if (s_rt->s_stage.s_list_cameras)
		ft_list_func(s_rt->s_stage.s_list_cameras, free);
	if (s_rt->s_stage.s_list_objs)
		ft_list_obj_func(s_rt->s_stage.s_list_objs, free);
}

int		end_rt(t_rt *s_rt)
{
	free_rt(s_rt);
	exit(0);
}

void	change_frame(t_rt *s_rt, void *img_old_p)
{
	if (s_rt->s_stage.s_main_camera->render_ready == 0)
		start_render(s_rt);
	if (mlx_clear_window(s_rt->mlx_p, s_rt->mlx_window) == 0)
		error_end("Error at mlx_clear_window()", MLX_ERROR, 0, NULL);
	mlx_put_image_to_window(s_rt->mlx_p, s_rt->mlx_window,
							s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr,
							0, 0);
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
		if ((s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr =
				mlx_new_image(s_rt->mlx_p, s_rt->s_stage.s_screen.width,
								s_rt->s_stage.s_screen.height)) == NULL)
			error_end("Error at mlx_new_image()", MLX_ERROR, 0, NULL);
		if ((s_rt->s_stage.s_main_camera->s_mlx_img.addr =
			mlx_get_data_addr(
				s_rt->s_stage.s_main_camera->s_mlx_img.img_ptr,
				&(s_rt->s_stage.s_main_camera->s_mlx_img.bits_per_pixel),
				&(s_rt->s_stage.s_main_camera->s_mlx_img.line_length),
				&(s_rt->s_stage.s_main_camera->s_mlx_img.endian))) == NULL)
			error_end("Error at mlx_get_data_addr()", MLX_ERROR, 0, NULL);
		s_rt->s_stage.s_main_camera->render_ready = 0;
		change_frame(s_rt, img_old_p);
		update = 0;
	}
	return (0);
}
