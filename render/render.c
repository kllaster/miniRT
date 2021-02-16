#include "mini_rt.h"

int		get_color_pixel(t_ray	*s_ray)
{
	if (s_ray->type & OBJ_SPHERE)
		return (get_int_rgb(((t_sphere *)s_ray->content)->s_color));
//	else if (s_ray->type & OBJ_PLANE)
//		s_color = *((t_plane *)s_ray->content)->s_color;
//	else if (s_ray->type & OBJ_SQUARE)
//		s_color = *((t_square *)s_ray->content)->s_color;
//	else if (s_ray->type & OBJ_CYLINDER)
//		s_color = *((t_cylinder *)s_ray->content)->s_color;
//	else if (s_ray->type & OBJ_TRIANGLE)
//		s_color = *((t_triangle *)s_ray->content)->s_color;
	return (DEFAULT_COLOR);
}

void	inter_sphere(t_sphere *s_sphere, t_ray *s_ray)
{
	double			b;
	double			c;
	double			discriminant;
	double			x_one;
	double			x_two;
	t_ray			s_ray_inter;

	s_ray_inter = *s_ray;
	s_ray_inter.type = OBJ_SPHERE;
	s_ray_inter.content = s_sphere;
	s_ray_inter.s_vector_inter = vector_sub(&(s_ray_inter.s_vector_start_normal), s_sphere->s_coordinates);
	b = 2 * vector_scalar_mul(&s_ray_inter.s_vector_inter, &(s_ray_inter.s_vector_start_normal));
	c = vector_scalar_mul(&s_ray_inter.s_vector_inter, &s_ray_inter.s_vector_inter) -
						(s_sphere->diameter / 2.0 * s_sphere->diameter / 2.0);
	discriminant = b * b - (4 * c);
	if (discriminant < 0)
		return ;
	x_one = (-b - sqrt(discriminant)) / 2;
	x_two = (-b + sqrt(discriminant)) / 2;
	if (x_one > 0 && (discriminant > 0 && x_two > 0 && x_two > x_one) &&
					x_one < s_ray->length)
	{
		s_ray_inter.length = x_one;
		*s_ray = s_ray_inter;
	}
	else if (discriminant > 0 && x_two > 0 && x_two < s_ray->length)
	{
		s_ray_inter.length = x_two;
		*s_ray = s_ray_inter;
	}
}

int		start_ray(t_stage *s_stage, t_ray *s_ray)
{
	t_list_objs	*s_list_obj;

	s_list_obj = s_stage->s_list_objs;
	while (s_list_obj)
	{
		if (s_list_obj->type & OBJ_SPHERE)
			inter_sphere(s_list_obj->content, s_ray);
//		else if (s_list_obj->type & OBJ_PLANE)
//			ray_plane(s_list_obj->content);
//		else if (s_list_obj->type & OBJ_SQUARE)
//			ray_square(s_list_obj->content);
//		else if (s_list_obj->type & OBJ_CYLINDER)
//			ray_cylinder(s_list_obj->content);
//		else if (s_list_obj->type & OBJ_TRIANGLE)
//			ray_triangle(s_list_obj->content);
		s_list_obj = s_list_obj->next;
	}
	if (s_ray->length < MAX_DISTANCE)
		return (get_color_pixel(s_ray));
	return (DEFAULT_COLOR);
}

t_camera	*get_another_camera(t_stage *s_stage)
{
	t_camera	*s_camera;

	s_camera = s_stage->s_list_cameras->content;
	if ((s_camera->s_mlx_img = malloc(sizeof(t_mlx_img))) == NULL)
		error_end("Ошибка выделения памяти get_another_camera", 1);
	s_camera->s_mlx_img->img = mlx_new_image(s_stage->mlx_p,
												s_stage->s_screen.width,
												s_stage->s_screen.height);
	s_camera->s_mlx_img->addr = mlx_get_data_addr(s_camera->s_mlx_img->img,
								&(s_camera->s_mlx_img->bits_per_pixel),
								&(s_camera->s_mlx_img->line_length),
								&(s_camera->s_mlx_img->endian));
	return (s_camera);
}

int			render(t_stage *s_stage)
{
	int			x;
	int			y;
	t_camera	*s_camera;
	t_ray 		s_ray;
	t_screen	s_screen;

	s_stage->mlx_p = NULL;
	if ((s_stage->mlx_p = mlx_init()) == NULL)
		return (-1);
	mlx_get_screen_size(s_stage->mlx_p, &(s_screen.width), &(s_screen.height));
	if (s_stage->s_screen.width > s_screen.width)
		s_stage->s_screen.width = s_screen.width;
	if (s_stage->s_screen.height > s_screen.height)
		s_stage->s_screen.height = s_screen.height;
	s_stage->mlx_window = mlx_new_window(s_stage->mlx_p, s_stage->s_screen.width,
								s_stage->s_screen.height, "miniRT");
	s_camera = get_another_camera(s_stage);
	x = 0;
	while (x < s_stage->s_screen.width)
	{
		y = 0;
		while (y < s_stage->s_screen.height)
		{
			s_ray.length = MAX_DISTANCE;
			s_ray.s_vector_start.x = x - ((double)s_stage->s_screen.width / 2);
			s_ray.s_vector_start.y = -y + ((double)s_stage->s_screen.height / 2);
			s_ray.s_vector_start.z = (double)s_stage->s_screen.width /
					(2 * tan((double)s_camera->fov / 2 * M_PI / 180));
			s_ray.s_vector_start_normal = vector_norm(&s_ray.s_vector_start);
			my_mlx_pixel_put(s_camera->s_mlx_img, x, y, start_ray(s_stage, &s_ray));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(s_stage->mlx_p, s_stage->mlx_window, s_camera->s_mlx_img->img, 0, 0);
	mlx_loop(s_stage->mlx_p);
	return (0);
}