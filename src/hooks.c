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

int		change_pos_camera(t_rt *s_rt, int x, int y, int z)
{
	t_vec s_vec;

	if ((x != 0 || y != 0) && s_rt->s_stage.s_main_camera->s_vec_dir->z == -1)
	{
		x *= -1;
		y *= -1;
	}
	if (x != 0)
		s_rt->s_stage.s_main_camera->s_vec_origin->x += (float)x;
	if (y != 0)
		s_rt->s_stage.s_main_camera->s_vec_origin->y += (float)y;
	if (z != 0)
	{
		s_vec = vec_mul(s_rt->s_stage.s_main_camera->s_vec_dir, (float)z);
		*s_rt->s_stage.s_main_camera->s_vec_origin =
				vec_sum(s_rt->s_stage.s_main_camera->s_vec_origin, &s_vec);
	}
	s_rt->s_stage.s_main_camera->s_matrix_rotate =
			get_matrix_rotate(s_rt->s_stage.s_main_camera->s_vec_origin,
							  s_rt->s_stage.s_main_camera->s_vec_dir);
	if (x != 0 || y != 0 || z != 0)
		return (1);
	return (0);
}

int		change_dir_camera(t_rt *s_rt, t_vec s_vec)
{
	if (s_vec.x != 0 || s_vec.y != 0 || s_vec.z != 0)
	{
		if (s_vec.x != 0)
			vec_rotate_y(s_rt->s_stage.s_main_camera->s_vec_dir,
							(float)sin((double)s_vec.x),
							(float)cos((double)s_vec.x));
		if (s_vec.y != 0)
			vec_rotate_x(s_rt->s_stage.s_main_camera->s_vec_dir,
							(float)sin((double)s_vec.y),
							(float)cos((double)s_vec.y));
		if (s_vec.z != 0)
			vec_rotate_z(s_rt->s_stage.s_main_camera->s_vec_dir,
							(float)sin((double)s_vec.z),
							(float)cos((double)s_vec.z));
		s_rt->s_stage.s_main_camera->s_matrix_rotate =
				get_matrix_rotate(s_rt->s_stage.s_main_camera->s_vec_origin,
								  s_rt->s_stage.s_main_camera->s_vec_dir);
		return (1);
	}
	return (0);
}

int		key_press(int keycode, t_rt *s_rt)
{
	int	i;

	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W)
		s_rt->z_move = SPEED_MOVE;
	else if (keycode == KEY_S)
		s_rt->z_move = -SPEED_MOVE;
	else if (keycode == KEY_A)
		s_rt->x_move = SPEED_MOVE;
	else if (keycode == KEY_D)
		s_rt->x_move = -SPEED_MOVE;
	else if (keycode == KEY_Z)
		s_rt->y_move = SPEED_MOVE;
	else if (keycode == KEY_X)
		s_rt->y_move = -SPEED_MOVE;
	else if (keycode == KEY_Q)
		s_rt->new_dir = (t_vec){ANGEL_ROTATION * 0.01, 0, 0};
	else if (keycode == KEY_E)
		s_rt->new_dir = (t_vec){-ANGEL_ROTATION * (float)0.01, 0, 0};
	else if (keycode == KEY_UP)
		s_rt->new_dir = (t_vec){0, -ANGEL_ROTATION * (float)0.01, 0};
	else if (keycode == KEY_DOWN)
		s_rt->new_dir = (t_vec){0, ANGEL_ROTATION * (float)0.01, 0};
	else if (keycode == KEY_RIGHT)
		s_rt->new_dir = (t_vec){0, 0, ANGEL_ROTATION * (float)0.05};
	else if (keycode == KEY_LEFT)
		s_rt->new_dir = (t_vec){0, 0, -ANGEL_ROTATION * (float)0.05};
	else if (keycode == KEY_SPACE)
	{
		get_another_camera(s_rt);
		i = -1;
		while (++i < COUNT_THREADS)
			s_rt->s_thread_data[i].s_main_camera = s_rt->s_stage.s_main_camera;
		change_frame(s_rt, NULL);
	}
	return (0);
}

int		key_release(int keycode, t_rt *s_rt)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_D ||
		keycode == KEY_S || keycode == KEY_Z || keycode == KEY_X)
		s_rt->z_move = s_rt->y_move = s_rt->x_move = 0;
	else if (keycode == KEY_Q || keycode == KEY_E || keycode == KEY_UP ||
				keycode == KEY_DOWN || keycode == KEY_RIGHT ||
				keycode == KEY_LEFT)
		s_rt->new_dir = (t_vec){0,0,0};
	return (0);
}

int		new_frame(t_rt *s_rt)
{
	static long long int	last_hook_time = 0;
	static int				update = 0;
	void					*img_old_p;

	if ((last_hook_time + (1000 / MAX_FPS)) < time_unix_ms())
	{
		if (!s_rt->render_now && vec_check_unzero(&s_rt->new_dir))
		{
			update = change_dir_camera(s_rt, s_rt->new_dir);
			last_hook_time = time_unix_ms();
		}
		else if (!s_rt->render_now && (!s_rt->x_move || !s_rt->y_move || !s_rt->z_move))
		{
			update = change_pos_camera(s_rt, s_rt->x_move, s_rt->y_move, s_rt->z_move);
			last_hook_time = time_unix_ms();
		}
	}
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
