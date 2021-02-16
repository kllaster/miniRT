#include "mini_rt.h"

void	parse_screen(char *str, t_stage *s_stage)
{
	skip_between_arg(&str);
	s_stage->s_screen.width = ft_atoi_pos(&str);
	if (s_stage->s_screen.width <= 0)
		error_end("Неверная высота окна", 1);
	skip_between_arg(&str);
	s_stage->s_screen.height = ft_atoi_pos(&str);
	if (s_stage->s_screen.height <= 0)
		error_end("Неверная ширина окна", 1);
}

void	parse_g_light(char *str, t_stage *s_stage)
{
	skip_between_arg(&str);
	if (!(s_stage->s_g_light = malloc(sizeof(t_g_light))))
		error_end("Ошибка выделения памяти parse_g_light", 1);
	s_stage->s_g_light->brightness = parse_double(&str);
	if (s_stage->s_g_light->brightness < 0.0)
		error_end("Неверная яркость глобального света", 1);
	skip_between_arg(&str);
	s_stage->s_g_light->s_color = parse_rgb(&str);
}

void	parse_camera(char *str, t_stage *s_stage)
{
	t_camera		*s_camera;

	skip_between_arg(&str);
	if ((s_camera = malloc(sizeof(t_camera))) == NULL)
		error_end("Ошибка выделения памяти parse_camera", 1);
	s_camera->s_coordinates = parse_coordinates(&str);
	skip_between_arg(&str);
	s_camera->s_angle = parse_angle(&str);
	skip_between_arg(&str);
	s_camera->fov = ft_atoi_pos(&str);
	ft_lstadd_back(&(s_stage->s_list_cameras), ft_lstnew(s_camera));
}

void	parse_light(char *str, t_stage *s_stage)
{
	t_light		*s_light;

	skip_between_arg(&str);
	if ((s_light = malloc(sizeof(t_light))) == NULL)
		error_end("Ошибка выделения памяти parse_light", 1);
	s_light->s_coordinates = parse_coordinates(&str);
	skip_between_arg(&str);
	s_light->brightness = parse_double(&str);
	skip_between_arg(&str);
	s_light->s_color = parse_rgb(&str);
	ft_lstadd_back(&(s_stage->s_list_lights), ft_lstnew(s_light));
}

void	parse_file(char *file, t_stage *s_stage)
{
	int		fd;
	int		error;
	char	*str;

	if (!ft_strequal_end(file, ".rt"))
		error_end("Неверный формат файла сцены. Ожидался \".rt\"", 1);
	fd = open(file, O_RDONLY);
	if (!fd)
		error_end("Файл невозможно прочесть", 1);
	while ((error = get_next_line(fd, &str)) != -1 && error)
	{
		if (str[0] == 'R' && str[1] == ' ')
			parse_screen(str, s_stage);
		else if (str[0] == 'A' && str[1] == ' ')
			parse_g_light(str, s_stage);
		else if (str[0] == 'c' && str[1] == ' ')
			parse_camera(str, s_stage);
		else if (str[0] == 'l' && str[1] == ' ')
			parse_light(str, s_stage);
		else
			parse_objs(str, s_stage);
		free(str);
	}
	if (error != -1)
		free(str);
	close(fd);
}
