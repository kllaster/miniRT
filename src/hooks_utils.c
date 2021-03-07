#include "mini_rt.h"

int		change_pos_camera(t_rt *s_rt, int x, int y, int z)
{
	t_vec s_vec;

	if ((x != 0 || y != 0) && s_rt->s_stage.s_main_camera->s_vec_dir.z == -1)
	{
		x *= -1;
		y *= -1;
	}
	if (x != 0)
		s_rt->s_stage.s_main_camera->s_vec_origin.x += (float)x;
	if (y != 0)
		s_rt->s_stage.s_main_camera->s_vec_origin.y += (float)y;
	if (z != 0)
	{
		s_vec = vec_mul(&s_rt->s_stage.s_main_camera->s_vec_dir, (float)z);
		s_rt->s_stage.s_main_camera->s_vec_origin =
				vec_sum(&s_rt->s_stage.s_main_camera->s_vec_origin, &s_vec);
	}
	s_rt->s_stage.s_main_camera->s_matrix_rotate =
			get_matrix_rotate(&s_rt->s_stage.s_main_camera->s_vec_origin,
								&s_rt->s_stage.s_main_camera->s_vec_dir);
	if (x != 0 || y != 0 || z != 0)
		return (1);
	return (0);
}

int		change_dir_camera(t_rt *s_rt, t_vec s_vec)
{
	if (s_vec.x != 0 || s_vec.y != 0 || s_vec.z != 0)
	{
		if (s_vec.x != 0)
			vec_rotate_y(&s_rt->s_stage.s_main_camera->s_vec_dir,
							sinf(s_vec.x), cosf(s_vec.x));
		if (s_vec.y != 0)
			vec_rotate_x(&s_rt->s_stage.s_main_camera->s_vec_dir,
							sinf(s_vec.y), cosf(s_vec.y));
		if (s_vec.z != 0)
			vec_rotate_z(&s_rt->s_stage.s_main_camera->s_vec_dir,
							sinf(s_vec.z), cosf(s_vec.z));
		s_rt->s_stage.s_main_camera->s_matrix_rotate =
				get_matrix_rotate(&s_rt->s_stage.s_main_camera->s_vec_origin,
									&s_rt->s_stage.s_main_camera->s_vec_dir);
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
	else if (keycode == KEY_SPACE && s_rt->change_cam == 0)
	{
		s_rt->change_cam = 1;
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
	{
		s_rt->x_move = 0;
		s_rt->y_move = 0;
		s_rt->z_move = 0;
	}
	else if (keycode == KEY_Q || keycode == KEY_E || keycode == KEY_UP ||
				keycode == KEY_DOWN || keycode == KEY_RIGHT ||
				keycode == KEY_LEFT)
		s_rt->new_dir = (t_vec){0, 0, 0};
	else if (keycode == KEY_SPACE)
		s_rt->change_cam = 0;
	return (0);
}

int		check_hooks(t_rt *s_rt)
{
	int						update;
	static long long int	last_hook_time = 0;

	update = 0;
	if ((last_hook_time + TIME2HOOK) < time_unix_ms())
	{
		if (!s_rt->render_now && vec_check_unzero(&s_rt->new_dir))
		{
			update = change_dir_camera(s_rt, s_rt->new_dir);
			last_hook_time = time_unix_ms();
		}
		else if (!s_rt->render_now &&
					(!s_rt->x_move || !s_rt->y_move || !s_rt->z_move))
		{
			update = change_pos_camera(s_rt, s_rt->x_move, s_rt->y_move, s_rt->z_move);
			last_hook_time = time_unix_ms();
		}
	}
	return (update);
}
