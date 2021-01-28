#ifndef RT_OBJS_H
# define RT_OBJS_H

# include "mini_rt.h"

typedef	struct	s_sphere {
	unsigned int	diameter;
	t_coordinates	*s_coordinates;
	t_rgb			*s_color;
}				t_sphere;

typedef	struct	s_plane {
	t_coordinates	*s_coordinates;
	t_angle			*s_angle;
	t_rgb			*s_color;
}				t_plane;

#endif
