#include "mini_rt.h"

void	change_img_window(t_rt *s_rt)
{
    mlx_clear_window(s_rt->mlx_p, s_rt->mlx_window);
	if (s_rt->s_stage.s_selected_camera->render_ready == 1)
	{
		mlx_put_image_to_window(s_rt->mlx_p, s_rt->mlx_window,
							s_rt->s_stage.s_selected_camera->s_mlx_img.img, 0, 0);
	}
	else
		start_render(s_rt);
}

int		change_pos_camera(t_rt *s_rt, t_vec *s_vec)
{
	*s_rt->s_stage.s_selected_camera->s_vec_origin =
			vec_sum(s_rt->s_stage.s_selected_camera->s_vec_origin, s_vec);
	return (1);
}

int		change_dir_camera(t_rt *s_rt, t_vec *s_vec)
{
	t_vec	s_vec_new;

	s_vec_new = vec_sum(s_rt->s_stage.s_selected_camera->s_vec_dir, s_vec);
	s_vec_new.x > 1 ? s_vec_new.x = 0 : 0;
	s_vec_new.x < -1 ? s_vec_new.x = 0 : 0;
	s_vec_new.y > 1 ? s_vec_new.y = 0 : 0;
	s_vec_new.y < -1 ? s_vec_new.y = 0 : 0;
	s_vec_new.z > 1 ? s_vec_new.z = 0 : 0;
	s_vec_new.z < -1 ? s_vec_new.z = 0 : 0;
	*s_rt->s_stage.s_selected_camera->s_vec_dir = s_vec_new;
	s_rt->s_stage.s_selected_camera->s_matrix_rotate =
			get_matrix_rotate(s_rt->s_stage.s_selected_camera->s_vec_origin,
								  s_rt->s_stage.s_selected_camera->s_vec_dir);
	return (1);
}

int		key_press(int keycode, t_rt *s_rt)
{
	int	i;

	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W)
		s_rt->new_origin = (t_vec){0, 0, SPEED_MOVE};
	else if (keycode == KEY_A)
		s_rt->new_origin = (t_vec){SPEED_MOVE, 0, 0};
	else if (keycode == KEY_D)
		s_rt->new_origin = (t_vec){-SPEED_MOVE, 0, 0};
	else if (keycode == KEY_S)
		s_rt->new_origin = (t_vec){0, 0, -SPEED_MOVE};
	else if (keycode == KEY_Q)
		s_rt->new_dir = (t_vec){(double)ANGEL_ROTATION * 0.1, 0, 0};
	else if (keycode == KEY_E)
		s_rt->new_dir = (t_vec){(double)-ANGEL_ROTATION * 0.1, 0, 0};
	else if (keycode == KEY_SPACE)
	{
		get_another_camera(s_rt);
		i = -1;
		while (++i < COUNT_THREADS)
			s_rt->s_thread_data[i].s_selected_camera = s_rt->s_stage.s_selected_camera;
		change_img_window(s_rt);
	}
	return (0);
}

int		key_release(int keycode, t_rt *s_rt)
{
	if (keycode == KEY_W)
		s_rt->new_origin = (t_vec){0,0,0};
	else if (keycode == KEY_A)
		s_rt->new_origin = (t_vec){0,0,0};
	else if (keycode == KEY_D)
		s_rt->new_origin = (t_vec){0,0,0};
	else if (keycode == KEY_S)
		s_rt->new_origin = (t_vec){0,0,0};
	else if (keycode == KEY_Q)
		s_rt->new_dir = (t_vec){0,0,0};
	else if (keycode == KEY_E)
		s_rt->new_dir = (t_vec){0,0,0};
	return (0);
}

int		new_frame(t_rt *s_rt)
{
	static int	update = 1;

	if (vec_check_unzero(&s_rt->new_origin))
		update = change_pos_camera(s_rt, &s_rt->new_origin);
	if (vec_check_unzero(&s_rt->new_dir))
		update = change_dir_camera(s_rt, &s_rt->new_dir);
	if (update)
		start_render(s_rt);
	update = 0;
	return (0);
}