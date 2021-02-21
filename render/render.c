#include "mini_rt.h"

void 	inter_sphere(t_sphere *s_sphere, t_ray *s_ray)
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
		s_ray_inter.s_vector_inter_length = vector_mul(&s_ray_inter.s_vector_start_normal, x_one);
		*s_ray = s_ray_inter;
	}
	else if (discriminant > 0 && x_two > 0 && x_two < s_ray->length)
	{
        s_ray_inter.length = x_two;
		s_ray_inter.s_vector_inter_length = vector_mul(&s_ray_inter.s_vector_start_normal, x_two);
		*s_ray = s_ray_inter;
	}
}

void 	check_inter_objs(t_stage *s_stage, t_ray *s_ray)
{
	t_list_objs	*s_list_obj;

	s_ray->type = OBJ_NONE;
	s_ray->length = MAX_DISTANCE;
	s_list_obj = s_stage->s_list_objs;
	while (s_list_obj)
	{
		if (s_list_obj->type & OBJ_SPHERE)
        {
            inter_sphere(s_list_obj->content, s_ray);
            if (s_ray->length != MAX_DISTANCE)
                s_ray->s_vector_inter_normal = vector_sub(&s_ray->s_vector_inter_length, ((t_sphere *)s_list_obj->content)->s_coordinates);
        }
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
	if (s_ray->length != MAX_DISTANCE)
    {
		s_ray->s_vector_start = vector_sum(&s_ray->s_vector_start, &s_ray->s_vector_inter_length);
        s_ray->s_vector_inter_normal = vector_norm(&s_ray->s_vector_inter_normal);
    }
}

t_rgb	get_light_color(t_stage *s_stage, t_ray *s_ray)
{
	t_ray		    s_light_ray;
	t_rgb           s_color_res;
    t_rgb           s_color_light;
    t_list          *s_list_light;
    double		    angel_incidence;

    s_color_res = rgb_mul(s_stage->s_g_light->s_color,
                          s_stage->s_g_light->brightness);
    s_list_light = s_stage->s_list_lights;
    while (s_list_light)
    {
		s_light_ray.s_vector_start = s_ray->s_vector_start;
		s_light_ray.s_vector_start_normal = vector_sub(&s_light_ray.s_vector_start, ((t_light *)s_list_light->content)->s_coordinates);
        s_light_ray.s_vector_start_normal = vector_norm(&s_light_ray.s_vector_start);
        check_inter_objs(s_stage, &s_light_ray);
        if (s_light_ray.length == MAX_DISTANCE)
        {
            angel_incidence = vector_scalar_mul(&s_light_ray.s_vector_start_normal,
                                            &s_ray->s_vector_inter_normal);
			if (angel_incidence < 0)
            {
                s_color_light = rgb_mul(s_stage->s_g_light->s_color,
                                -angel_incidence *
                                ((t_light *)s_list_light->content)->brightness);
                s_color_res = rgb_sum(&s_color_res, &s_color_light);
            }
        }
        s_list_light = s_list_light->next;
    }
    return (s_color_res);
}

int		get_color_pixel(t_stage *s_stage, t_ray *s_ray)
{
	t_rgb	s_pixel_color;

	s_pixel_color = get_light_color(s_stage, s_ray);
    if (s_ray->type & OBJ_SPHERE)
		s_pixel_color = rgb_mul_arr(((t_sphere *)s_ray->content)->s_color, &s_pixel_color);
//	else if (s_ray->type & OBJ_PLANE)
//		pixel_color = *((t_plane *)s_ray->content)->s_color;
//	else if (s_ray->type & OBJ_SQUARE)
//		pixel_color = *((t_square *)s_ray->content)->s_color;
//	else if (s_ray->type & OBJ_CYLINDER)
//		pixel_color = *((t_cylinder *)s_ray->content)->s_color;
//	else if (s_ray->type & OBJ_TRIANGLE)
//		pixel_color = *((t_triangle *)s_ray->content)->s_color
	return (rgb_get_int(&s_pixel_color));
}

int		start_ray(t_stage *s_stage, t_ray *s_ray)
{
	check_inter_objs(s_stage, s_ray);
	if (s_ray->length < MAX_DISTANCE)
		return (get_color_pixel(s_stage, s_ray));
	return (DEFAULT_COLOR);
}

void	get_another_camera(t_stage *s_stage)
{
	s_stage->s_selected_camera = s_stage->s_list_cameras->content;
	if ((s_stage->s_selected_camera->s_mlx_img = malloc(sizeof(t_mlx_img))) == NULL)
		error_end("Ошибка выделения памяти get_another_camera", 1);
	s_stage->s_selected_camera->s_mlx_img->img = mlx_new_image(s_stage->mlx_p,
												s_stage->s_screen.width,
												s_stage->s_screen.height);
	s_stage->s_selected_camera->s_mlx_img->addr = mlx_get_data_addr(s_stage->s_selected_camera->s_mlx_img->img,
								&(s_stage->s_selected_camera->s_mlx_img->bits_per_pixel),
								&(s_stage->s_selected_camera->s_mlx_img->line_length),
								&(s_stage->s_selected_camera->s_mlx_img->endian));
	s_stage->s_selected_camera->sin_angle_x = sin(s_stage->s_selected_camera->s_angle->x);
	s_stage->s_selected_camera->cos_angle_x = cos(s_stage->s_selected_camera->s_angle->x);
	s_stage->s_selected_camera->sin_angle_y = sin(s_stage->s_selected_camera->s_angle->y);
	s_stage->s_selected_camera->cos_angle_y = cos(s_stage->s_selected_camera->s_angle->y);
	s_stage->s_selected_camera->sin_angle_z = sin(s_stage->s_selected_camera->s_angle->z);
	s_stage->s_selected_camera->cos_angle_z = cos(s_stage->s_selected_camera->s_angle->z);
}

void	init_vscreen(t_screen *s_screen, t_camera *s_camera, t_vscreen *s_vscreen)
{
	double		ratio;

	ratio = (double)s_screen->width / (double)s_screen->height;
	s_vscreen->width = (double)s_screen->width / (2 * tan((double)s_camera->fov / 2 * (M_PI / 180)));
	s_vscreen->height = s_vscreen->width / ratio;
	s_vscreen->x_coef = s_vscreen->width / (double)s_screen->width;
	s_vscreen->y_coef = s_vscreen->height / (double)s_screen->height;
}

int		render(t_stage *s_stage)
{
	int			x;
	int			y;
	t_ray 		s_ray;
	t_screen	s_screen;
	t_vscreen	*s_vscreen;

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
	get_another_camera(s_stage);
	if ((s_vscreen = malloc(sizeof(t_vscreen))) == NULL)
		error_end("Ошибка выделения памяти s_vscreen", 1);
	init_vscreen(&(s_stage->s_screen), s_stage->s_selected_camera, s_vscreen);
	x = 0;
	while (x < s_stage->s_screen.width)
	{
		y = 0;
		while (y < s_stage->s_screen.height)
		{
			s_ray.s_vector_start.x = (x - ((double)s_stage->s_screen.width / 2)) * s_vscreen->x_coef;
			s_ray.s_vector_start.y = (-y + ((double)s_stage->s_screen.height / 2)) * s_vscreen->y_coef;
			s_ray.s_vector_start.z = s_vscreen->width;
			s_ray.s_vector_start = vector_sum(&s_ray.s_vector_start, s_stage->s_selected_camera->s_coordinates);
			s_ray.s_vector_start_normal = vector_norm(&s_ray.s_vector_start);
			s_ray.s_vector_start_normal = vector_sum(&s_ray.s_vector_start_normal, s_stage->s_selected_camera->s_angle);
			s_ray.s_vector_start_normal = vector_norm(&s_ray.s_vector_start_normal);
			my_mlx_pixel_put(s_stage->s_selected_camera->s_mlx_img, x, y, start_ray(s_stage, &s_ray));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(s_stage->mlx_p, s_stage->mlx_window, s_stage->s_selected_camera->s_mlx_img->img, 0, 0);
	mlx_loop(s_stage->mlx_p);
	return (0);
}