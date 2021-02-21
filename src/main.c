#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	t_stage s_stage;
	int		error;

	if (argc == 1)
		error_end("Неверное кол-во аргументов", 2);
	ft_bzero(&s_stage, sizeof(s_stage));
	parse_file(argv[1], &s_stage);
	if (!s_stage.s_screen.width && !s_stage.s_screen.height)
		error_end("Не задано окно", 1);
	if (!s_stage.s_list_cameras)
		error_end("Не задана ни одна камера", 1);
	debug_print_s_stage(&s_stage);
	if ((error = render(&s_stage)) < 0)
		error_end("Ошибка рендера", error);
	return (0);
}
