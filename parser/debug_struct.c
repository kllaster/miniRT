#include "mini_rt.h"

void	debug_print_s_vec(t_vec *s_vec, char *s_name)
{
	printf("——— t_vec	%s:\n", s_name);
	printf("—————— float	x: %f\n", s_vec->x);
	printf("—————— float	y: %f\n", s_vec->y);
	printf("—————— float	z: %f\n", s_vec->z);
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
	debug_print_s_vec(s_camera->s_vec_dir, "s_vec_dir");
	debug_print_s_vec(s_camera->s_vec_origin, "s_vec_origin");
}

void	debug_print_s_lights(t_light *s_light)
{
	printf("\n——— t_light	s_light:\n");
	printf("——— float	brightness: %f\n", s_light->brightness);
	debug_print_s_color(s_light->s_color);
	debug_print_s_vec(s_light->s_vec_origin, "s_vec_origin");
}

void	debug_print_s_sphere(t_sphere *s_sphere)
{
	printf("\n——— t_sphere	s_sphere:\n");
	printf("——— float	radius: %f\n", s_sphere->radius);
	debug_print_s_color(s_sphere->s_color);
	debug_print_s_vec(s_sphere->s_vec_origin, "s_vec_origin");
}

void	debug_print_s_plane(t_plane *s_plane)
{
	printf("\n——— t_plane	s_plane:\n");
	debug_print_s_color(s_plane->s_color);
	debug_print_s_vec(s_plane->s_vec_dir, "s_vec_dir");
	debug_print_s_vec(s_plane->s_vec_origin, "s_vec_origin");
}

void	debug_print_s_square(t_square *s_square)
{
	printf("\n——— t_square	s_square:\n");
	printf("——— float	side_size: %f\n", s_square->side_size);
	debug_print_s_color(s_square->s_color);
	debug_print_s_vec(s_square->s_vec_dir, "s_vec_dir");
	debug_print_s_vec(s_square->s_vec_origin, "s_vec_origin");
}

void	debug_print_s_cylinder(t_cylinder *s_cylinder)
{
	printf("\n——— t_cylinder	s_cylinder:\n");
	printf("——— float	diameter: %f\n", s_cylinder->diameter);
	printf("——— float	height: %f\n", s_cylinder->height);
	debug_print_s_color(s_cylinder->s_color);
	debug_print_s_vec(s_cylinder->s_vec_dir, "s_vec_dir");
	debug_print_s_vec(s_cylinder->s_vec_origin, "s_vec_origin");
}

void	debug_print_s_triangle(t_triangle *s_triangle)
{
	printf("\n——— t_triangle	s_triangle:\n");
	debug_print_s_vec(s_triangle->s_vec_origin_1, "s_vec_origin_1");
	debug_print_s_vec(s_triangle->s_vec_origin_2, "s_vec_origin_2");
	debug_print_s_vec(s_triangle->s_vec_origin_3, "s_vec_origin_3");
	debug_print_s_vec(s_triangle->s_vec_edge_1, "s_vec_edge_1");
	debug_print_s_vec(s_triangle->s_vec_edge_2, "s_vec_edge_2");
	debug_print_s_vec(s_triangle->s_vec_dir, "s_vec_dir");
	debug_print_s_color(s_triangle->s_color);
}

void	debug_print_s_stage(t_stage *s_stage)
{
	t_list 		*s_list;
	t_list_objs *s_list_obj;

	printf("\n\n\\\\ t_stage s_stage //\n\n");
	printf("— t_screen	s_screen:\n");
	printf("——— int	height: %d\n", s_stage->s_screen.height);
	printf("——— int	width: %d\n\n", s_stage->s_screen.width);
	printf("— t_ambient_light	s_ambient_light:\n");
	printf("——— float	brightness: %f\n", s_stage->s_ambient_light.brightness);
	debug_print_s_color(s_stage->s_ambient_light.s_color);
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
		if (s_list_obj->type & (unsigned)OBJ_SPHERE)
			debug_print_s_sphere(s_list_obj->content);
		else if (s_list_obj->type & (unsigned)OBJ_PLANE)
			debug_print_s_plane(s_list_obj->content);
		else if (s_list_obj->type & (unsigned)OBJ_SQUARE)
			debug_print_s_square(s_list_obj->content);
		else if (s_list_obj->type & (unsigned)OBJ_CYLINDER)
			debug_print_s_cylinder(s_list_obj->content);
		else if (s_list_obj->type & (unsigned)OBJ_TRIANGLE)
			debug_print_s_triangle(s_list_obj->content);
		s_list_obj = s_list_obj->next;
	}
}
