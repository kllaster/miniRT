#ifndef MINI_RT_H
# define MINI_RT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef	struct	s_rgb {
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
}				t_rgb;

typedef	struct	s_coordinates {
	int				x;
	int				y;
	int				z;
}				t_coordinates;

typedef	struct	s_angle {
	int				x;
	int				y;
	int				z;
}				t_angle;

typedef	struct	s_camera {
	unsigned int	fov;
	t_angle			angle;
	t_coordinates	s_coordinates;
}				t_camera;

typedef	struct	s_g_illumination {
	float			brightness;
	t_rgb			s_color;
}				t_g_illumination;

typedef	struct	s_screen {
	unsigned int	height;
	unsigned int	width;
}				t_screen;

typedef	struct	s_light {
	float			brightness;
	t_coordinates	s_coordinates;
	t_rgb			s_color;
}				t_light;

#endif
