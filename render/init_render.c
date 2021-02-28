#include "mini_rt.h"

void	init_vscreen(t_screen *s_screen, t_camera *s_camera, t_vscreen *s_vscreen)
{
	s_vscreen->width = (double)s_screen->width * 0.5;
	s_vscreen->height = (double)s_screen->height * 0.5;
	s_vscreen->z = (double)s_screen->width /
							(2 * tan((double)s_camera->fov / 2 * (M_PI / 180)));
}

void	init_camera(t_rt *s_rt, t_camera *s_camera)
{
	if ((s_camera->s_mlx_img.img_ptr = mlx_new_image(s_rt->mlx_p,
												 s_rt->s_stage.s_screen.width,
												 s_rt->s_stage.s_screen.height)) == NULL)
		error_end("Ошибка при mlx_new_image()", MLX_ERROR);
	if ((s_camera->s_mlx_img.addr = mlx_get_data_addr(s_camera->s_mlx_img.img_ptr,
													  &(s_camera->s_mlx_img.bits_per_pixel),
													  &(s_camera->s_mlx_img.line_length),
													  &(s_camera->s_mlx_img.endian))) == NULL)
		error_end("Ошибка при mlx_get_data_addr()", MLX_ERROR);
	init_vscreen(&s_rt->s_stage.s_screen, s_camera, &s_camera->s_vscreen);
	s_camera->s_matrix_rotate = get_matrix_rotate(s_camera->s_vec_origin,
											   		s_camera->s_vec_dir);
	s_camera->init = 1;
}

void	get_another_camera(t_rt *s_rt)
{
	int		i;
	t_list	*s_list_cameras;

	if (s_rt->s_stage.s_main_camera == NULL)
		i = 1;
	else
		i = s_rt->s_stage.s_main_camera->count;
	s_list_cameras = s_rt->s_stage.s_list_cameras;
	while (s_list_cameras)
	{
		if (((t_camera *)s_list_cameras->content)->count < i)
		{
			s_rt->s_stage.s_main_camera = s_list_cameras->content;
			s_rt->s_stage.s_main_camera->count++;
			if (s_rt->s_stage.s_main_camera->init == 0)
				init_camera(s_rt, s_rt->s_stage.s_main_camera);
			return ;
		}
		s_list_cameras = s_list_cameras->next;
	}
	s_rt->s_stage.s_main_camera = s_rt->s_stage.s_list_cameras->content;
	s_rt->s_stage.s_main_camera->count++;
}

void	check_user_window(t_rt *s_rt)
{
	t_screen	s_screen;

	mlx_get_screen_size(s_rt->mlx_p, &(s_screen.width), &(s_screen.height));
	if (s_rt->s_stage.s_screen.width > s_screen.width)
		s_rt->s_stage.s_screen.width = s_screen.width;
	if (s_rt->s_stage.s_screen.height > s_screen.height)
		s_rt->s_stage.s_screen.height = s_screen.height;
}

void	init_render(t_rt *s_rt)
{
	s_rt->mlx_p = NULL;
	if ((s_rt->mlx_p = mlx_init()) == NULL)
		error_end("Ошибка при mlx_init()", MLX_ERROR);
	check_user_window(s_rt);
	if ((s_rt->mlx_window = mlx_new_window(s_rt->mlx_p, s_rt->s_stage.s_screen.width,
										   s_rt->s_stage.s_screen.height, "miniRT")) == NULL)
		error_end("Ошибка при mlx_new_window()", MLX_ERROR);
	mlx_hook(s_rt->mlx_window, 2, 0, key_press, s_rt);
	mlx_hook(s_rt->mlx_window, 3, 0, key_release, s_rt);
	get_another_camera(s_rt);
	get_aa_sample(&s_rt->s_stage.s_aa_sample);
	create_threads_data(s_rt);
}