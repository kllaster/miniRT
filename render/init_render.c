#include "mini_rt.h"

void	init_vscreen(float width, float height, t_cam *s_cam,
						t_vscreen *s_vscreen)
{
	s_vscreen->width = (float)(width * 0.5);
	s_vscreen->height = (float)(height * 0.5);
	s_vscreen->z =
	(width / (2 * tanf(s_cam->fov / 2 * (M_PI / 180))));
}

void	init_cam(void *mlx_p, t_stage *s_stage, t_cam *s_cam)
{
	if ((s_cam->s_mlx_img.img_ptr =
				mlx_new_image(mlx_p, s_stage->width, s_stage->height)) == NULL)
		error_end("Error at mlx_new_image()", MLX_ERROR, 0, NULL);
	if ((s_cam->s_mlx_img.addr =
					mlx_get_data_addr(s_cam->s_mlx_img.img_ptr,
										&(s_cam->s_mlx_img.bits_per_pixel),
										&(s_cam->s_mlx_img.line_length),
										&(s_cam->s_mlx_img.endian))) == NULL)
		error_end("Error at mlx_get_data_addr()", MLX_ERROR, 0, NULL);
	init_vscreen((float)s_stage->width, (float)s_stage->height, s_cam,
					&s_cam->s_vscreen);
	s_cam->s_matrix_rotate = get_matrix_rotate(&s_cam->s_vec_o,
													&s_cam->s_vec_dir);
	s_cam->init = 1;
}

void	get_another_cam(void *mlx_p, t_stage *s_stage)
{
	int		i;
	t_lst	*s_lst_cams;

	if (s_stage->s_main_cam == NULL)
		i = 1;
	else
		i = s_stage->s_main_cam->count;
	s_lst_cams = s_stage->s_lst_cams;
	while (s_lst_cams)
	{
		if (((t_cam *)s_lst_cams->content)->count < i)
		{
			s_stage->s_main_cam = s_lst_cams->content;
			++s_stage->s_main_cam->count;
			if (s_stage->s_main_cam->init == 0)
				init_cam(mlx_p, s_stage, s_stage->s_main_cam);
			return ;
		}
		s_lst_cams = s_lst_cams->next;
	}
	s_stage->s_main_cam = s_stage->s_lst_cams->content;
	++s_stage->s_main_cam->count;
}

void	check_user_window(void *mlx_p, t_stage *s_stage)
{
	int	width;
	int	height;

	mlx_get_screen_size(mlx_p, &width, &height);
	if (s_stage->width > width)
		s_stage->width = width;
	if (s_stage->height > height)
		s_stage->height = height;
}

void	init_render(t_rt *s_rt)
{
	s_rt->mlx_p = NULL;
	if ((s_rt->mlx_p = mlx_init()) == NULL)
		error_end("Error at mlx_init()", MLX_ERROR, 0, NULL);
	check_user_window(s_rt->mlx_p, &s_rt->s_stage);
	if ((s_rt->mlx_window = mlx_new_window(s_rt->mlx_p,
											s_rt->s_stage.width,
											s_rt->s_stage.height,
											"miniRT")) == NULL)
		error_end("Error at mlx_new_window()", MLX_ERROR, 0, NULL);
	mlx_hook(s_rt->mlx_window, 2, 0, key_press, s_rt);
	mlx_hook(s_rt->mlx_window, 3, 0, key_release, s_rt);
	mlx_hook(s_rt->mlx_window, 4, 0, mouse_press, s_rt);
	mlx_hook(s_rt->mlx_window, 17, 0, end_rt, s_rt);
	get_another_cam(s_rt->mlx_p, &s_rt->s_stage);
	get_aa_sample(s_rt->s_stage.anti_aliasing, &s_rt->s_stage.s_aa_sample);
	create_threads_data(s_rt);
}
