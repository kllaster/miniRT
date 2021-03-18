#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	t_rt	s_rt;

	if (argc == 1 || argc == 3 || argc > 4)
		error_end("Invalid number of arguments", PARSE_ERROR, 0, NULL);
	ft_bzero(&s_rt, sizeof(t_rt));
	error_end("", 0, 1, &s_rt);
	parse_file(argv[1], &s_rt.s_stage);
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
