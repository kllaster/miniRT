#include "mini_rt.h"

void	parse_screen(char *str, t_stage *s_stage)
{
	skip_between_param(&str, 0);
	s_stage->s_screen.width = ft_atoi_pos(&str, 1);
	if (s_stage->s_screen.width <= 0)
		error_end("Incorrect window width", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_stage->s_screen.height = ft_atoi_pos(&str, 1);
	if (s_stage->s_screen.height <= 0)
		error_end("Incorrect window height", PARSE_ERROR, 0, NULL);
}

void	parse_ambient_light(char *str, t_stage *s_stage)
{
	float brightness;

	skip_between_param(&str, 0);
	brightness = parse_float(&str, 1);
	if (brightness < 0.0)
		error_end("Incorrect ambient light brightness", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	if ((s_stage->s_ambient_color = malloc(sizeof(t_rgb))) == NULL)
		error_end("Memory allocation error: parse_ambient_light()",
					MALLOC_ERROR, 0, NULL);
	*s_stage->s_ambient_color = parse_rgb(&str);
	*s_stage->s_ambient_color = rgb_mul(s_stage->s_ambient_color,
												brightness);
}

void	parse_camera(char *str, t_stage *s_stage)
{
	t_camera		*s_camera;

	skip_between_param(&str, 0);
	if ((s_camera = malloc(sizeof(t_camera))) == NULL)
		error_end("Memory allocation error: parse_camera()",
					MALLOC_ERROR, 0, NULL);
	ft_bzero(s_camera, sizeof(t_camera));
	s_camera->s_vec_origin = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_camera->s_vec_dir = parse_coordinates(&str);
	if (ft_fabs(s_camera->s_vec_dir.x) > 1 ||
		ft_fabs(s_camera->s_vec_dir.y) > 1 ||
		ft_fabs(s_camera->s_vec_dir.z) > 1)
		error_end("Incorrect direction camera", PARSE_ERROR, 0, NULL);
	s_camera->s_vec_dir = vec_norm(&s_camera->s_vec_dir);
	skip_between_param(&str, 0);
	s_camera->fov = ft_atoi_pos(&str, 1);
	if (s_camera->fov <= 0)
		error_end("Incorrect FOV", PARSE_ERROR, 0, NULL);
	ft_list_add_back(&(s_stage->s_list_cameras), ft_list_new(s_camera));
}

void	parse_light(char *str, t_stage *s_stage)
{
	float		brightness;
	t_light		*s_light;

	skip_between_param(&str, 0);
	if ((s_light = malloc(sizeof(t_light))) == NULL)
		error_end("Memory allocation error: parse_light()",
					MALLOC_ERROR, 0, NULL);
	s_light->s_vec_origin = parse_coordinates(&str);
	skip_between_param(&str, 0);
	brightness = parse_float(&str, 1);
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
		error_end("Invalid scene file format. Expected \".rt\"",
					PARSE_ERROR, 0, NULL);
	if ((fd = open(file, O_RDONLY)) < 0)
		error_end("Error opening the scene file", PARSE_ERROR, 0, NULL);
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
		error_end("Error reading the scene file", PARSE_ERROR, 0, NULL);
	close(fd);
}
