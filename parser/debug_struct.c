#include "mini_rt.h"

void	debug_print_s_material(t_material s_material)
{
	printf("——— t_material	s_material:\n");
	printf("—————— float	ref_coeff: %f\n", s_material.ref_coeff);
	debug_print_s_color(s_material.s_color);
}

void	debug_print_s_vec(t_vec s_vec, char *s_name)
{
	printf("——— t_vec	%s:\n", s_name);
	printf("—————— float	x: %f\n", s_vec.x);
	printf("—————— float	y: %f\n", s_vec.y);
	printf("—————— float	z: %f\n", s_vec.z);
}

void	debug_print_s_color(t_rgb s_color)
{
	printf("——— t_rgb	s_color:\n");
	printf("—————— int	red: %d\n", s_color.red);
	printf("—————— int	green: %d\n", s_color.green);
	printf("—————— int	blue: %d\n", s_color.blue);
}

void	debug_print_s_cam(t_cam *s_cam)
{
	printf("\n——— t_cam	s_cam:\n");
	printf("——— unsigned int	fov: %u\n", s_cam->fov);
	debug_print_s_vec(s_cam->s_vec_dir, "s_vec_dir");
	debug_print_s_vec(s_cam->s_vec_o, "s_vec_o");
}

void	debug_print_s_lights(t_light *s_light)
{
	printf("\n——— t_light	s_light:\n");
	debug_print_s_color(s_light->s_color);
	debug_print_s_vec(s_light->s_vec_o, "s_vec_o");
}

void	debug_print_s_sphere(t_sphere *s_sphere)
{
	printf("\n——— t_sphere	s_sphere:\n");
	printf("——— float	radius_pow: %f\n", s_sphere->radius_pow);
	debug_print_s_vec(s_sphere->s_vec_o, "s_vec_o");
	debug_print_s_material(s_sphere->s_material);
}

void	debug_print_s_plane(t_plane *s_plane)
{
	printf("\n——— t_plane	s_plane:\n");
	debug_print_s_vec(s_plane->s_vec_dir, "s_vec_dir");
	debug_print_s_vec(s_plane->s_vec_o, "s_vec_o");
	debug_print_s_material(s_plane->s_material);
}

void	debug_print_s_square(t_square *s_square)
{
	printf("\n——— t_square	s_square:\n");
	printf("——— float	side_size: %f\n", s_square->side_size);
	debug_print_s_vec(s_square->s_vec_dir, "s_vec_dir");
	debug_print_s_vec(s_square->s_vec_o, "s_vec_o");
	debug_print_s_material(s_square->s_material);
}

void	debug_print_s_cylinder(t_cylinder *s_cylinder)
{
	printf("\n——— t_cylinder	s_cylinder:\n");
	printf("——— float	diameter: %f\n", s_cylinder->diameter);
	printf("——— float	height: %f\n", s_cylinder->height);
	debug_print_s_vec(s_cylinder->s_vec_dir, "s_vec_dir");
	debug_print_s_vec(s_cylinder->s_vec_o, "s_vec_o");
	debug_print_s_material(s_cylinder->s_material);
}

void	debug_print_s_triangle(t_triangle *s_triangle)
{
	printf("\n——— t_triangle	s_triangle:\n");
	debug_print_s_vec(s_triangle->s_vec_o_1, "s_vec_o_1");
	debug_print_s_vec(s_triangle->s_vec_o_2, "s_vec_o_2");
	debug_print_s_vec(s_triangle->s_vec_o_3, "s_vec_o_3");
	debug_print_s_vec(s_triangle->s_vec_edge_1, "s_vec_edge_1");
	debug_print_s_vec(s_triangle->s_vec_edge_2, "s_vec_edge_2");
	debug_print_s_vec(s_triangle->s_vec_dir, "s_vec_dir");
	debug_print_s_material(s_triangle->s_material);
}

void	debug_print_s_stage(t_stage *s_stage)
{
	t_lst		*s_lst;
	t_lst_objs	*s_lst_obj;

	printf("\n\n\\\\ t_stage s_stage //\n\n");
	printf("——— int	anti_aliasing: %d\n", s_stage->anti_aliasing);
	printf("——— int	height: %d\n", s_stage->height);
	printf("——— int	width: %d\n\n", s_stage->width);
	printf("— t_ambient_light	s_ambient_light:\n");
	debug_print_s_color(*s_stage->s_ambient_color);
	s_lst = s_stage->s_lst_cams;
	while (s_lst)
	{
		debug_print_s_cam(s_lst->content);
		s_lst = s_lst->next;
	}
	s_lst = s_stage->s_lst_lights;
	while (s_lst)
	{
		debug_print_s_lights(s_lst->content);
		s_lst = s_lst->next;
	}
	s_lst_obj = s_stage->s_lst_objs;
	while (s_lst_obj->next != s_stage->s_lst_objs)
	{
		if (s_lst_obj->type & OBJ_SPHERE)
			debug_print_s_sphere(s_lst_obj->content);
		else if (s_lst_obj->type & OBJ_PLANE)
			debug_print_s_plane(s_lst_obj->content);
		else if (s_lst_obj->type & OBJ_SQUARE)
			debug_print_s_square(s_lst_obj->content);
		else if (s_lst_obj->type & OBJ_CYLINDER)
			debug_print_s_cylinder(s_lst_obj->content);
		else if (s_lst_obj->type & OBJ_TRIANGLE)
			debug_print_s_triangle(s_lst_obj->content);
		s_lst_obj = s_lst_obj->next;
	}
}
