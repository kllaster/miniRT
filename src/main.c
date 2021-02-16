#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	t_stage s_stage;
	int		error;

	if (argc == 1)
		error_end("Неверное кол-во аргументов", 2);
	parse_file(argv[1], &s_stage);
	debug_print_s_stage(&s_stage);
	if ((error = render(&s_stage)) < 0)
		error_end("Ошибка рендера", error);
	return (0);
}
