#include "mini_rt.h"

void	parse_screen(char *str, t_stage *s_stage)
{
	skip_between_param(&str, 0);
	s_stage->width = ft_atoi_pos(&str, 1);
	if (s_stage->width <= 0)
		error_end("Incorrect window width", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	s_stage->height = ft_atoi_pos(&str, 1);
	if (s_stage->height <= 0)
		error_end("Incorrect window height", PARSE_ERROR, 0, NULL);
	s_stage->anti_aliasing = ft_atoi_pos(&str, 0);
	if (s_stage->anti_aliasing != 0 && s_stage->anti_aliasing != 1)
		error_end("Error: anti_aliasing [0, 1]", PARSE_ERROR, 0, NULL);
}

void	parse_ambient_light(char *str, t_stage *s_stage)
{
	float brightness;

	skip_between_param(&str, 0);
	brightness = parse_float(&str, 1);
	if (brightness < 0.0)
		error_end("Incorrect ambient light brightness", PARSE_ERROR, 0, NULL);
	skip_between_param(&str, 0);
	malloc_void((void **)&s_stage->s_ambient_color, sizeof(t_rgb));
	*s_stage->s_ambient_color = parse_rgb(&str);
	*s_stage->s_ambient_color = rgb_mul(s_stage->s_ambient_color,
												brightness);
}

void	parse_cam(char *str, t_stage *s_stage)
{
	t_cam		*s_cam;

	skip_between_param(&str, 0);
	malloc_void((void **)&s_cam, sizeof(t_cam));
	ft_bzero(s_cam, sizeof(t_cam));
	s_cam->s_vec_o = parse_coordinates(&str);
	skip_between_param(&str, 0);
	s_cam->s_vec_dir = parse_coordinates(&str);
	if (ft_fabs(s_cam->s_vec_dir.x) > 1 ||
		ft_fabs(s_cam->s_vec_dir.y) > 1 ||
		ft_fabs(s_cam->s_vec_dir.z) > 1)
		error_end("Incorrect direction cam", PARSE_ERROR, 0, NULL);
	s_cam->s_vec_dir = vec_norm(&s_cam->s_vec_dir);
	skip_between_param(&str, 0);
	s_cam->fov = ft_atoi_pos(&str, 1);
	if (s_cam->fov <= 0)
		error_end("Incorrect FOV", PARSE_ERROR, 0, NULL);
	ft_lst_add_back(&(s_stage->s_lst_cams), ft_lst_new(s_cam));
}

void	parse_light(char *str, t_stage *s_stage)
{
	float		brightness;
	t_light		*s_light;

	skip_between_param(&str, 0);
	malloc_void((void **)&s_light, sizeof(t_light));
	ft_lst_add_front(&(s_stage->s_lst_lights), ft_lst_new(s_light));
	s_light->s_vec_o = parse_coordinates(&str);
	skip_between_param(&str, 0);
	brightness = parse_float(&str, 1);
	skip_between_param(&str, 0);
	s_light->s_color = parse_rgb(&str);
	s_light->s_color = rgb_mul(&s_light->s_color, brightness);
}

void	parse_check_str(int fd, t_stage *s_stage)
{
	int		error;
	char	*str;

	while ((error = get_next_line(fd, &str)) != -1)
	{
		if (str[0] == 'R' && (str[1] == ' ' || str[1] == '\t'))
			parse_screen(str, s_stage);
		else if (str[0] == 'A' && (str[1] == ' ' || str[1] == '\t'))
			parse_ambient_light(str, s_stage);
		else if (str[0] == 'c' && (str[1] == ' ' || str[1] == '\t'))
			parse_cam(str, s_stage);
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
}

void	parse_file(char *file, t_stage *s_stage)
{
	int	fd;

	if (!ft_strequal_end(file, ".rt"))
		error_end("Invalid scene file format. Expected \".rt\"",
					PARSE_ERROR, 0, NULL);
	if ((fd = open(file, O_RDONLY)) < 0)
		error_end("Error opening the scene file", PARSE_ERROR, 0, NULL);
	parse_check_str(fd, s_stage);
	close(fd);
	ft_end_lst_obj(&s_stage->s_lst_objs);
	if (!s_stage->width || !s_stage->height)
		error_end("Window incorrect", PARSE_ERROR, 0, NULL);
	if (!s_stage->s_lst_cams)
		error_end("The cam is not installed", PARSE_ERROR, 0, NULL);
	if (!s_stage->s_ambient_color)
		error_end("Ambient light is not installed", PARSE_ERROR, 0, NULL);
	if (!s_stage->s_lst_objs)
		error_end("Objects not specified", PARSE_ERROR, 0, NULL);
}
