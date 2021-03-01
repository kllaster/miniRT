#include "mini_rt.h"

t_vec		*vec_cpy(t_vec *s_vec)
{
	t_vec	*s_vec_new;

	if ((s_vec_new = malloc(sizeof(t_vec))) == NULL)
		error_end("Ошибка выделения памяти vec_cpy", MALLOC_ERROR);
	*s_vec_new = *s_vec;
	return (s_vec_new);
}

t_rgb		*rgb_cpy(t_rgb *s_color)
{
	t_rgb	*s_color_new;

	if ((s_color_new = malloc(sizeof(t_rgb))) == NULL)
		error_end("Ошибка выделения памяти rgb_cpy", MALLOC_ERROR);
	*s_color_new = *s_color;
	return (s_color_new);
}

void		*camera_cpy(void *data)
{
	t_camera	*s_camera;
	t_camera	*s_camera_new;

	s_camera = (t_camera *)data;
	if ((s_camera_new = malloc(sizeof(t_camera))) == NULL)
		error_end("Ошибка выделения памяти camera_cpy", MALLOC_ERROR);
	ft_memcpy(s_camera_new, s_camera, sizeof(t_camera));
	s_camera_new->s_vec_origin = vec_cpy(s_camera->s_vec_origin);
	s_camera_new->s_vec_dir = vec_cpy(s_camera->s_vec_dir);
	return (s_camera_new);
}

void		*light_cpy(void *data)
{
	t_light	*s_light;
	t_light	*s_light_new;

	s_light = (t_light *)data;
	if ((s_light_new = malloc(sizeof(t_light))) == NULL)
		error_end("Ошибка выделения памяти lights_cpy", MALLOC_ERROR);
	s_light_new->brightness = s_light->brightness;
	s_light_new->s_vec_origin = vec_cpy(s_light->s_vec_origin);
	s_light_new->s_color = rgb_cpy(s_light->s_color);
	return (s_light_new);
}

t_triangle	*triangle_cpy(t_triangle *s_triangle)
{
	t_triangle	*s_triangle_new;

	if ((s_triangle_new = malloc(sizeof(t_triangle))) == NULL)
		error_end("Ошибка выделения памяти triangle_cpy", MALLOC_ERROR);
	s_triangle_new->s_vec_origin_1 = vec_cpy(s_triangle->s_vec_origin_1);
	s_triangle_new->s_vec_origin_2 = vec_cpy(s_triangle->s_vec_origin_2);
	s_triangle_new->s_vec_origin_3 = vec_cpy(s_triangle->s_vec_origin_3);
	s_triangle_new->s_vec_edge_1 = vec_cpy(s_triangle->s_vec_edge_1);
	s_triangle_new->s_vec_edge_2 = vec_cpy(s_triangle->s_vec_edge_2);
	s_triangle_new->s_vec_dir = vec_cpy(s_triangle->s_vec_dir);
	s_triangle_new->s_color = rgb_cpy(s_triangle->s_color);
	return (s_triangle_new);
}

t_cylinder	*cylinder_cpy(t_cylinder *s_cylinder)
{
	t_cylinder	*s_cylinder_new;

	if ((s_cylinder_new = malloc(sizeof(t_cylinder))) == NULL)
		error_end("Ошибка выделения памяти cylinder_cpy", MALLOC_ERROR);
	s_cylinder_new->diameter = s_cylinder->diameter;
	s_cylinder_new->height = s_cylinder->height;
	s_cylinder_new->s_vec_origin = vec_cpy(s_cylinder->s_vec_origin);
	s_cylinder_new->s_vec_dir = vec_cpy(s_cylinder->s_vec_dir);
	s_cylinder_new->s_color = rgb_cpy(s_cylinder->s_color);
	return (s_cylinder_new);
}

t_square	*square_cpy(t_square *s_square)
{
	t_square	*s_square_new;

	if ((s_square_new = malloc(sizeof(t_square))) == NULL)
		error_end("Ошибка выделения памяти square_cpy", MALLOC_ERROR);
	s_square_new->side_size = s_square->side_size;
	s_square_new->s_vec_origin = vec_cpy(s_square->s_vec_origin);
	s_square_new->s_vec_dir = vec_cpy(s_square->s_vec_dir);
	s_square_new->s_color = rgb_cpy(s_square->s_color);
	return (s_square_new);
}

t_plane		*plane_cpy(t_plane *s_plane)
{
	t_plane	*s_plane_new;

	if ((s_plane_new = malloc(sizeof(t_plane))) == NULL)
		error_end("Ошибка выделения памяти plane_cpy", MALLOC_ERROR);
	s_plane_new->s_vec_origin = vec_cpy(s_plane->s_vec_origin);
	s_plane_new->s_vec_dir = vec_cpy(s_plane->s_vec_dir);
	s_plane_new->s_color = rgb_cpy(s_plane->s_color);
	return (s_plane_new);
}

t_sphere	*sphere_cpy(t_sphere *s_sphere)
{
	t_sphere	*s_sphere_new;

	if ((s_sphere_new = malloc(sizeof(t_sphere))) == NULL)
		error_end("Ошибка выделения памяти sphere_cpy", MALLOC_ERROR);
	s_sphere_new->radius = s_sphere->radius;
	s_sphere_new->s_vec_origin = vec_cpy(s_sphere->s_vec_origin);
	s_sphere_new->s_color = rgb_cpy(s_sphere->s_color);
	return (s_sphere_new);
}

void		*obj_cpy(void *data, unsigned char type)
{
	void	*new_obj;

	new_obj = NULL;
	if (type & (unsigned)OBJ_SPHERE)
		new_obj = sphere_cpy(data);
	else if (type & (unsigned)OBJ_PLANE)
		new_obj = plane_cpy(data);
	else if (type & (unsigned)OBJ_SQUARE)
		new_obj = square_cpy(data);
	else if (type & (unsigned)OBJ_CYLINDER)
		new_obj = cylinder_cpy(data);
	else if (type & (unsigned)OBJ_TRIANGLE)
		new_obj = triangle_cpy(data);
	return (new_obj);
}