#include "mini_rt.h"

void	debug_print_s_angle(t_angle *s_angle)
{
	printf("——— t_angle	s_angle:\n");
	printf("—————— double	x: %f\n", s_angle->x);
	printf("—————— double	y: %f\n", s_angle->y);
	printf("—————— double	z: %f\n", s_angle->z);
}

void	debug_print_s_coordinates(t_coordinates *s_coordinates)
{
	printf("——— t_coordinates	s_coordinates:\n");
	printf("—————— double	x: %f\n", s_coordinates->x);
	printf("—————— double	y: %f\n", s_coordinates->y);
	printf("—————— double	z: %f\n", s_coordinates->z);
}

void	debug_print_s_color(t_rgb *s_color)
{
	printf("——— t_rgb	s_color:\n");
	printf("—————— int	red: %d\n", s_color->red);
	printf("—————— int	green: %d\n", s_color->green);
	printf("—————— int	blue: %d\n", s_color->blue);
}

void	debug_print_s_camera(t_camera *s_camera)
{
	printf("\n——— t_camera	s_camera:\n");
	printf("——— unsigned int	fov: %u\n", s_camera->fov);
	debug_print_s_angle(s_camera->s_angle);
	debug_print_s_coordinates(s_camera->s_coordinates);
}

void	debug_print_s_lights(t_light *s_light)
{
	printf("\n——— t_light	s_light:\n");
	printf("——— double	brightness: %f\n", s_light->brightness);
	debug_print_s_color(s_light->s_color);
	debug_print_s_coordinates(s_light->s_coordinates);
}

void	debug_print_s_sphere(t_sphere *s_sphere)
{
	printf("\n——— t_sphere	s_sphere:\n");
	printf("——— double	diameter: %f\n", s_sphere->diameter);
	debug_print_s_color(s_sphere->s_color);
	debug_print_s_coordinates(s_sphere->s_coordinates);
}

void	debug_print_s_plane(t_plane *s_plane)
{
	printf("\n——— t_plane	s_plane:\n");
	debug_print_s_color(s_plane->s_color);
	debug_print_s_angle(s_plane->s_angle);
	debug_print_s_coordinates(s_plane->s_coordinates);
}

void	debug_print_s_square(t_square *s_square)
{
	printf("\n——— t_square	s_square:\n");
	printf("——— double	side_size: %f\n", s_square->side_size);
	debug_print_s_color(s_square->s_color);
	debug_print_s_angle(s_square->s_angle);
	debug_print_s_coordinates(s_square->s_coordinates);
}

void	debug_print_s_cylinder(t_cylinder *s_cylinder)
{
	printf("\n——— t_cylinder	s_cylinder:\n");
	printf("——— double	diameter: %f\n", s_cylinder->diameter);
	printf("——— double	height: %f\n", s_cylinder->height);
	debug_print_s_color(s_cylinder->s_color);
	debug_print_s_angle(s_cylinder->s_angle);
	debug_print_s_coordinates(s_cylinder->s_coordinates);
}

void	debug_print_s_triangle(t_triangle *s_triangle)
{
	printf("\n——— t_triangle	s_triangle:\n");
	debug_print_s_coordinates(s_triangle->s_coordinates_1);
	debug_print_s_coordinates(s_triangle->s_coordinates_2);
	debug_print_s_coordinates(s_triangle->s_coordinates_3);
	debug_print_s_color(s_triangle->s_color);
}

void	debug_print_s_stage(t_stage *s_stage)
{
	t_list 		*s_list;
	t_list_objs *s_list_obj;

	printf("\n\n\\\\ t_stage s_stage //\n\n");
	printf("— void	*mlx_p: %p\n\n", s_stage->mlx_p);
	printf("— t_screen	s_screen:\n");
	printf("——— int	height: %d\n", s_stage->s_screen.height);
	printf("——— int	width: %d\n\n", s_stage->s_screen.width);
	printf("— t_g_light	s_g_light:\n");
	printf("——— double	brightness: %f\n", s_stage->s_g_light->brightness);
	debug_print_s_color(s_stage->s_g_light->s_color);
	s_list = s_stage->s_list_cameras;
	while (s_list)
	{
		debug_print_s_camera(s_list->content);
		s_list = s_list->next;
	}
	s_list = s_stage->s_list_lights;
	while (s_list)
	{
		debug_print_s_lights(s_list->content);
		s_list = s_list->next;
	}
	s_list_obj = s_stage->s_list_objs;
	while (s_list_obj)
	{
		if (s_list_obj->type & OBJ_SPHERE)
			debug_print_s_sphere(s_list_obj->content);
		else if (s_list_obj->type & OBJ_PLANE)
			debug_print_s_plane(s_list_obj->content);
		else if (s_list_obj->type & OBJ_SQUARE)
			debug_print_s_square(s_list_obj->content);
		else if (s_list_obj->type & OBJ_CYLINDER)
			debug_print_s_cylinder(s_list_obj->content);
		else if (s_list_obj->type & OBJ_TRIANGLE)
			debug_print_s_triangle(s_list_obj->content);
		s_list_obj = s_list_obj->next;
	}
}
