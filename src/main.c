#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	t_rt	s_rt;

	if (argc == 1 || argc == 3 || argc > 4)
		error_end("Invalid number of arguments", PARSE_ERROR, 0, NULL);
	ft_bzero(&s_rt, sizeof(t_rt));
	error_end("", 0, 1, &s_rt);
	parse_file(argv[1], &s_rt.s_stage);
	if (!s_rt.s_stage.width || !s_rt.s_stage.height)
		error_end("Window incorrect", PARSE_ERROR, 0, NULL);
	if (!s_rt.s_stage.s_list_cameras)
		error_end("The camera is not installed", PARSE_ERROR, 0, NULL);
	if (!s_rt.s_stage.s_ambient_color)
		error_end("Ambient light is not installed", PARSE_ERROR, 0, NULL);
	if (!s_rt.s_stage.s_list_objs)
		error_end("Objects not specified", PARSE_ERROR, 0, NULL);
	init_render(&s_rt);
	debug_print_s_stage(&s_rt.s_stage);
	if (argc == 4)
	{
		save_img(&s_rt, argv[3], argv);
		end_rt(&s_rt);
	}
	change_frame(&s_rt, NULL);
	mlx_loop_hook(s_rt.mlx_p, new_frame, &s_rt);
	mlx_loop(s_rt.mlx_p);
	free_rt(&s_rt);
	return (0);
}
