#include "mini_rt.h"

void	parse_screen(char *str, t_stage *s_stage)
{
	skip_between_param(&str, 0);
	s_stage->s_screen.width = ft_atoi_pos(&str);
	if (s_stage->s_screen.width <= 0)
		error_end("Неверная высота окна", PARSE_ERROR);
	skip_between_param(&str, 0);
	s_stage->s_screen.height = ft_atoi_pos(&str);
	if (s_stage->s_screen.height <= 0)
		error_end("Неверная ширина окна", PARSE_ERROR);
}

void	parse_ambient_light(char *str, t_stage *s_stage)
{
	float brightness;

	skip_between_param(&str, 0);
	brightness = parse_float(&str);
	if (brightness < 0.0)
		error_end("Неверная яркость глобального света", PARSE_ERROR);
	skip_between_param(&str, 0);
	s_stage->s_ambient_light.s_color = parse_rgb(&str);
	s_stage->s_ambient_light.s_color = rgb_mul(&s_stage->s_ambient_light.s_color,
												brightness);
}

void	parse_camera(char *str, t_stage *s_stage)
{
	t_camera		*s_camera;

	skip_between_param(&str, 0);
	if ((s_camera = malloc(sizeof(t_camera))) == NULL)
		error_end("Ошибка выделения памяти parse_camera", MALLOC_ERROR);
	s_camera->init = 0;
	s_camera->count = 0;
	s_camera->render_ready = 0;
	s_camera->s_vec_origin = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_camera->s_vec_dir = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_camera->fov = ft_atoi_pos(&str);
	if (s_camera->fov < 0)
		error_end("FOV должен быть положительным числом", PARSE_ERROR);
	ft_list_add_back(&(s_stage->s_list_cameras), ft_list_new(s_camera));
}

void	parse_light(char *str, t_stage *s_stage)
{
	float		brightness;
	t_light		*s_light;

	skip_between_param(&str, 0);
	if ((s_light = malloc(sizeof(t_light))) == NULL)
		error_end("Ошибка выделения памяти parse_light", MALLOC_ERROR);
	s_light->s_vec_origin = parse_coordinates(&str);
	skip_between_param(&str, 0);
	brightness = parse_float(&str);
	skip_between_param(&str, 0);
	s_light->s_color = parse_rgb(&str);
	s_light->s_color = rgb_mul(&s_light->s_color, brightness);
	ft_list_add_front(&(s_stage->s_list_lights), ft_list_new(s_light));
}

void	parse_file(char *file, t_stage *s_stage)
{
	int		fd;
	int		error;
	char	*str;

	if (!ft_strequal_end(file, ".rt"))
		error_end("Неверный формат файла сцены. Ожидался \".rt\"", PARSE_ERROR);
	fd = open(file, O_RDONLY);
	if (!fd)
		error_end("Файл невозможно прочесть", PARSE_ERROR);
	while ((error = get_next_line(fd, &str)) != -1)
	{
		if (str[0] == 'R' && (str[1] == ' ' || str[1] == '\t'))
			parse_screen(str, s_stage);
		else if (str[0] == 'A' && (str[1] == ' ' || str[1] == '\t'))
			parse_ambient_light(str, s_stage);
		else if (str[0] == 'c' && (str[1] == ' ' || str[1] == '\t'))
			parse_camera(str, s_stage);
		else if (str[0] == 'l' && (str[1] == ' ' || str[1] == '\t'))
			parse_light(str, s_stage);
		else
			parse_objs(str, s_stage);
		free(str);
		if (error == 0)
			break ;
	}
	if (error == -1)
		error_end("Ошибка при чтении файла сцены", PARSE_ERROR);
	close(fd);
}
