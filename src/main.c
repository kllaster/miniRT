#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	t_rt	s_rt;

	if (argc == 1 || argc > 3)
		error_end("Неверное кол-во аргументов", PARSE_ERROR);
	ft_bzero(&s_rt, sizeof(t_rt));
	parse_file(argv[1], &s_rt.s_stage);
	if (!s_rt.s_stage.s_screen.width && !s_rt.s_stage.s_screen.height)
		error_end("Не задано окно", PARSE_ERROR);
	if (!s_rt.s_stage.s_list_cameras)
		error_end("Не задана ни одна камера", PARSE_ERROR);
	if (!s_rt.s_stage.s_ambient_light.s_color)
		error_end("Не задан глобальный свет", PARSE_ERROR);
	if (!s_rt.s_stage.s_list_objs)
		error_end("Не задан ни один объект", PARSE_ERROR);
	init_render(&s_rt);
	debug_print_s_stage(&s_rt.s_stage);
	change_frame(&s_rt, NULL);
	mlx_loop_hook(s_rt.mlx_p, new_frame, &s_rt);
	mlx_loop(s_rt.mlx_p);
	return (0);
}
