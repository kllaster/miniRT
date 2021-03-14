#include "mini_rt.h"

int		change_pos_camera(t_rt *s_rt, t_vec *s_vec_pos)
{
	t_vec s_vec;

	s_rt->s_stage.s_main_camera->s_vec_origin.x += s_vec_pos->x;
	s_rt->s_stage.s_main_camera->s_vec_origin.y += s_vec_pos->y;
	if (s_vec_pos->z != 0)
	{
		s_vec = vec_mul(&s_rt->s_stage.s_main_camera->s_vec_dir, (float)s_vec_pos->z);
		s_rt->s_stage.s_main_camera->s_vec_origin =
				vec_sum(&s_rt->s_stage.s_main_camera->s_vec_origin, &s_vec);
	}
	s_rt->s_stage.s_main_camera->s_matrix_rotate =
			get_matrix_rotate(&s_rt->s_stage.s_main_camera->s_vec_origin,
								&s_rt->s_stage.s_main_camera->s_vec_dir);
	return (1);
}

int		change_dir_camera(t_rt *s_rt, t_vec *s_vec)
{
	if (s_vec->x != 0)
		vec_rotate_y(&s_rt->s_stage.s_main_camera->s_vec_dir,
						sinf(s_vec->x), cosf(s_vec->x));
	if (s_vec->y != 0)
		vec_rotate_x(&s_rt->s_stage.s_main_camera->s_vec_dir,
						sinf(s_vec->y), cosf(s_vec->y));
	if (s_vec->z != 0)
		vec_rotate_z(&s_rt->s_stage.s_main_camera->s_vec_dir,
						sinf(s_vec->z), cosf(s_vec->z));
	s_rt->s_stage.s_main_camera->s_matrix_rotate =
			get_matrix_rotate(&s_rt->s_stage.s_main_camera->s_vec_origin,
								&s_rt->s_stage.s_main_camera->s_vec_dir);
	return (1);
}

void	key_press_others(int keycode, t_rt *s_rt)
{
	int			i;
	char		name[30];
	time_t		timer;

	if (keycode == KEY_ESC)
		end_rt(s_rt);
	else if (keycode == KEY_SPACE && s_rt->change_cam == 0)
	{
		s_rt->change_cam = 1;
		get_another_camera(s_rt);
		i = -1;
		while (++i < COUNT_THREADS)
			s_rt->s_thread_data[i].s_main_camera = s_rt->s_stage.s_main_camera;
		change_frame(s_rt, NULL);
	}
	else if (keycode == KEY_F5)
	{
		timer = time(NULL);
		strftime(name, 30, "%d-%m-%Y_%H-%M-%S.bmp", localtime(&timer));
		name[29] = 0;
		save_img(s_rt, name, NULL);
	}
}

int		key_press(int keycode, t_rt *s_rt)
{
	int i;

	i = 1;
	if (keycode == KEY_W || (keycode == KEY_S && (i = -1)))
		s_rt->s_vec_pos = (t_vec){0, 0, i * SPEED_MOVE};
	else if (keycode == KEY_A || (keycode == KEY_D && (i = -1)))
		s_rt->s_vec_pos = (t_vec){i * SPEED_MOVE, 0, 0};
	else if (keycode == KEY_Z || (keycode == KEY_X && (i = -1)))
		s_rt->s_vec_pos = (t_vec){0, i * SPEED_MOVE, 0};
	else if (keycode == KEY_Q || (keycode == KEY_E && (i = -1)))
		s_rt->s_vec_dir = (t_vec){i * ANGEL_ROTATION * 0.01, 0, 0};
	else if (keycode == KEY_DOWN || (keycode == KEY_UP && (i = -1)))
		s_rt->s_vec_dir = (t_vec){0, i * ANGEL_ROTATION * (float)0.01, 0};
	else if (keycode == KEY_RIGHT || (keycode == KEY_LEFT && (i = -1)))
		s_rt->s_vec_dir = (t_vec){0, 0, i * ANGEL_ROTATION * (float)0.05};
	else
		key_press_others(keycode, s_rt);
	return (0);
}

int		key_release(int keycode, t_rt *s_rt)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_D ||
		keycode == KEY_S || keycode == KEY_Z || keycode == KEY_X)
		s_rt->s_vec_pos = (t_vec){0, 0, 0};
	else if (keycode == KEY_Q || keycode == KEY_E || keycode == KEY_UP ||
				keycode == KEY_DOWN || keycode == KEY_RIGHT ||
				keycode == KEY_LEFT)
		s_rt->s_vec_dir = (t_vec){0, 0, 0};
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
		if (!s_rt->render_now && vec_check_unzero(&s_rt->s_vec_dir))
		{
			update = change_dir_camera(s_rt, &s_rt->s_vec_dir);
			last_hook_time = time_unix_ms();
		}
		else if (!s_rt->render_now && vec_check_unzero(&s_rt->s_vec_pos))
		{
			update = change_pos_camera(s_rt, &s_rt->s_vec_pos);
			last_hook_time = time_unix_ms();
		}
	}
	return (update);
}
