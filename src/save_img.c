#include "mini_rt.h"

void	add_bmp_header(t_rt *s_rt, int fd, int file_size)
{
	char	file_data[54];

	ft_bzero(&file_data, 54);
	file_data[0] = 'B';
	file_data[1] = 'M';
	file_data[2] = (char)(file_size);
	file_data[3] = (char)(file_size >> 8);
	file_data[4] = (char)(file_size >> 16);
	file_data[5] = (char)(file_size >> 24);
	file_data[10] = (char)(54);
	file_data[14] = (char)(40);
	file_data[18] = (char)(s_rt->s_stage.s_screen.width);
	file_data[19] = (char)(s_rt->s_stage.s_screen.width >> 8);
	file_data[20] = (char)(s_rt->s_stage.s_screen.width >> 16);
	file_data[21] = (char)(s_rt->s_stage.s_screen.width >> 24);
	file_data[22] = (char)(s_rt->s_stage.s_screen.height);
	file_data[23] = (char)(s_rt->s_stage.s_screen.height >> 8);
	file_data[24] = (char)(s_rt->s_stage.s_screen.height >> 16);
	file_data[25] = (char)(s_rt->s_stage.s_screen.height >> 24);
	file_data[26] = (char)(1);
	file_data[28] = (char)(32);
	if (write(fd, file_data, 54) <= 0)
		error_end("Error writing the bpm file header", SAVE_ERROR, 0, NULL);
}

void	save_bmp(t_rt *s_rt, char *file_name)
{
	int i;
	int	fd;

	if ((fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		error_end("Error creating bpm file", SAVE_ERROR, 0, NULL);
	add_bmp_header(s_rt, fd, 54 + 4 * s_rt->s_stage.s_screen.width *
										s_rt->s_stage.s_screen.height);
	i = s_rt->s_stage.s_screen.height;
	while (--i >= 0)
		if (write(fd, s_rt->s_stage.s_main_camera->s_mlx_img.addr +
						i * s_rt->s_stage.s_main_camera->s_mlx_img.line_length,
					s_rt->s_stage.s_screen.width * 4) <= 0)
			error_end("Error writing the bpm file body", SAVE_ERROR, 0, NULL);
	close(fd);
}

void	save_img(t_rt *s_rt, char *argv[])
{
	if (!ft_strncmp("--save", argv[2], 6))
	{
		start_render(s_rt);
		if (ft_strequal_end(argv[3], ".bmp"))
			save_bmp(s_rt, argv[3]);
		else
			error_end("Expected \"--save file_name.bmp\"",
						PARSE_ERROR, 0, NULL);
		end_rt(s_rt);
	}
	else
		error_end("Expected \"--save file_name.bmp\"", PARSE_ERROR, 0, NULL);
}
