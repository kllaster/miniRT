#include "mini_rt.h"

void	debug_print_s_angle(t_angle *s_angle)
{
	printf("——— t_angle	s_angle:\n");
	printf("—————— float	x: %f\n", s_angle->x);
	printf("—————— float	y: %f\n", s_angle->y);
	printf("—————— float	z: %f\n\n", s_angle->z);
}

void	debug_print_s_coordinates(t_coordinates *s_coordinates)
{
	printf("——— t_coordinates	s_coordinates:\n");
	printf("—————— int	x: %d\n", s_coordinates->x);
	printf("—————— int	y: %d\n", s_coordinates->y);
	printf("—————— int	z: %d\n\n", s_coordinates->z);
}

void	debug_print_s_color(t_rgb *s_color)
{
	printf("——— t_rgb	s_color:\n");
	printf("—————— unsigned int	red: %u\n", s_color->red);
	printf("—————— unsigned int	green: %u\n", s_color->green);
	printf("—————— unsigned int	blue: %u\n\n", s_color->blue);
}

void	debug_print_s_camera(t_camera *s_camera)
{
	printf("——— t_camera	s_camera:\n");
	printf("—————— unsigned int	fov: %u\n", s_camera->fov);
	debug_print_s_angle(s_camera->s_angle);
	debug_print_s_coordinates(s_camera->s_coordinates);
}

void	debug_print_s_stage(t_stage *s_stage)
{
	t_list *s_list;

	printf("\n\n\\\\ t_stage s_stage //\n\n");
	printf("— void	*mlx_p: %p\n\n", s_stage->mlx_p);
	printf("— t_screen	s_screen:\n");
	printf("——— unsigned int	height: %u\n", s_stage->s_screen.height);
	printf("——— unsigned int	width: %u\n\n", s_stage->s_screen.width);
	printf("— t_g_light	s_g_light:\n");
	printf("——— float	brightness: %f\n", s_stage->s_g_light->brightness);
	debug_print_s_color(s_stage->s_g_light->s_color);
	s_list = s_stage->s_list_cameras;
	while (s_list)
	{
		debug_print_s_camera(s_list->content);
		s_list = s_list->next;
	}
}
