#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	t_stage s_stage;

	if (argc == 1)
		error_end("Неверное кол-во аргументов", 2);
	ft_bzero(&s_stage, sizeof(s_stage));
	parse_file(argv[1], &s_stage);
	debug_print_s_stage(&s_stage);
	return (0);
}
