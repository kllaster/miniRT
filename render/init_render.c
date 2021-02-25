#include "mini_rt.h"

void	init_vscreen(t_screen *s_screen, t_camera *s_camera, t_vscreen *s_vscreen)
{
	s_vscreen->width = (double)s_screen->width / 2.0;
	s_vscreen->height = (double)s_screen->height / 2.0;
	s_vscreen->z = (double)s_screen->width / (2 * tan((double)s_camera->fov / 2 * (M_PI / 180)));
}

void	init_camera(t_stage *s_stage, t_camera *s_camera)
{
	s_camera->s_mlx_img.img = mlx_new_image(s_stage->mlx_p,
											  s_stage->s_screen.width,
											  s_stage->s_screen.height);
	s_camera->s_mlx_img.addr = mlx_get_data_addr(s_camera->s_mlx_img.img,
									   &(s_camera->s_mlx_img.bits_per_pixel),
									   &(s_camera->s_mlx_img.line_length),
									   &(s_camera->s_mlx_img.endian));
	init_vscreen(&s_stage->s_screen, s_camera, &s_camera->s_vscreen);
	s_camera->s_matrix_rotate = get_matrix_rotate(s_camera->s_vec_origin, s_camera->s_vec_dir);
	s_camera->init = 1;
}

void	get_another_camera(t_stage *s_stage)
{
	int		count;
	t_list	*s_list_cameras;

	if (s_stage->s_selected_camera == NULL)
		count = 1;
	else
		count = s_stage->s_selected_camera->count;
	s_list_cameras = s_stage->s_list_cameras;
	while (s_list_cameras)
	{
		if (((t_camera *)s_list_cameras->content)->count < count)
		{
			s_stage->s_selected_camera = s_list_cameras->content;
			s_stage->s_selected_camera->count++;
			if (s_stage->s_selected_camera->init == 0)
				init_camera(s_stage, s_stage->s_selected_camera);
			return ;
		}
		s_list_cameras = s_list_cameras->next;
	}
	s_stage->s_selected_camera = s_stage->s_list_cameras->content;
	s_stage->s_selected_camera->count++;
}

void	check_user_window(t_stage *s_stage)
{
	t_screen	s_screen;

	mlx_get_screen_size(s_stage->mlx_p, &(s_screen.width), &(s_screen.height));
	if (s_stage->s_screen.width > s_screen.width)
		s_stage->s_screen.width = s_screen.width;
	if (s_stage->s_screen.height > s_screen.height)
		s_stage->s_screen.height = s_screen.height;
}

void	init_render(t_stage *s_stage)
{
	s_stage->mlx_p = NULL;
	if ((s_stage->mlx_p = mlx_init()) == NULL)
		error_end("Ошибка при mlx_init()", 1);
	check_user_window(s_stage);
	s_stage->mlx_window = mlx_new_window(s_stage->mlx_p, s_stage->s_screen.width,
										 s_stage->s_screen.height, "miniRT");
	mlx_key_hook(s_stage->mlx_window, key_hook, s_stage);
	get_another_camera(s_stage);
	get_aa_sample(&s_stage->s_aa_sample);
}