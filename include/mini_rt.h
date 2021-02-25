#ifndef MINI_RT_H
# define MINI_RT_H

enum e_rt
{
    MAX_DISTANCE	= 1000000,
	ANTI_ALIASING	= 1
};

# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "color.h"
# include "vectors.h"
# include "matrix.h"
# include "main_struct.h"
# include "hooks.h"
# include "utils.h"
# include "parser.h"
# include "objs.h"
# include "get_next_line.h"
# include "render.h"

#endif
