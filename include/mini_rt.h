#ifndef MINI_RT_H
# define MINI_RT_H

# define MAX_FPS		20
# define MAX_DISTANCE	100000
# define MIN_DISTANCE	0.02
# define MAX_REF		5
# define SPEED_MOVE		5
# define ANGEL_ROTATION	3
# define CHANGING_SIZE	2

# include "../minilibx/mlx.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "color.h"
# include "vectors.h"
# include "utils.h"
# include "matrix.h"
# include "main_struct.h"
# include "hooks.h"
# include "parser.h"
# include "objs.h"
# include "get_next_line.h"
# include "render.h"

#endif
