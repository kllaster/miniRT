#include "mini_rt.h"

void	debug_window_put_camera(t_rt *s_rt)
{
	char	tmp[10];

	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 20, 16777215, "s_vec_origin");
	sprintf(tmp, "%7.2f", s_rt->s_stage.s_main_camera->s_vec_origin.x);
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 50, 16777215, "x:");
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 35, 50, 16777215, tmp);
	sprintf(tmp, "%7.2f", s_rt->s_stage.s_main_camera->s_vec_origin.y);
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 80, 16777215, "y:");
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 35, 80, 16777215, tmp);
	sprintf(tmp, "%7.2f", s_rt->s_stage.s_main_camera->s_vec_origin.z);
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 110, 16777215, "z:");
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 35, 110, 16777215, tmp);
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 150, 16777215, "s_vec_dir");
	sprintf(tmp, "%7.2f", s_rt->s_stage.s_main_camera->s_vec_dir.x);
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 180, 16777215, "x:");
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 35, 180, 16777215, tmp);
	sprintf(tmp, "%7.2f", s_rt->s_stage.s_main_camera->s_vec_dir.y);
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 210, 16777215, "y:");
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 35, 210, 16777215, tmp);
	sprintf(tmp, "%7.2f", s_rt->s_stage.s_main_camera->s_vec_dir.z);
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 240, 16777215, "z:");
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 35, 240, 16777215, tmp);
	sprintf(tmp, "%d", s_rt->s_stage.s_main_camera->fov);
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 10, 270, 16777215, "FOV:");
	mlx_string_put(s_rt->mlx_p, s_rt->mlx_window, 60, 270, 16777215, tmp);
}
