NAME		= miniRT
CC			= gcc
RM			= rm -f
DEBUG		= 0
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
endif
CFLAGS		= -Wall -Wextra -Werror -MMD $(DEBUG_FLAGS) -D COUNT_THREADS=$(COUNT_THREADS)
CPPFLAGS	= $(CFLAGS) -march=native -O2 -msse4a -flto -pipe
HEADERS		= include/

SRCS =	src/main.c\
		src/utils.c\
		src/save_img.c\
		src/lst_utils.c\
		src/other_utils.c\
		src/lst_obj_utils.c\
		src/colors_utils.c\
		src/matrix_utils.c\
		src/vectors_utils.c\
		src/vectors_other.c\
		hooks/hooks.c\
		hooks/hooks_utils.c\
		hooks/hooks_mouse.c\
		parser/parser.c\
		parser/parse_objs.c\
		parser/parse_utils.c\
		parser/parse_other.c\
		parser/debug_window.c\
		parser/debug_struct.c\
		parser/get_next_line.c\
		parser/get_next_line_utils.c\
		render/render.c\
		render/threads.c\
		render/ray_utils.c\
		render/init_render.c\
		render/render_utils.c\
		render/intersections/inter_plane.c\
		render/intersections/inter_sphere.c\
		render/intersections/inter_square.c\
		render/intersections/inter_triangle.c\
		render/intersections/inter_cylinder.c\

OBJS = $(SRCS:.c=.o)

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	COUNT_THREADS = $(shell sysctl -n hw.ncpu)
else
	COUNT_THREADS = 1
endif

ifeq ($(COUNT_THREADS), 0)
	COUNT_THREADS = 1
endif

$(NAME):		$(OBJS)
				cd minilibx && $(MAKE) && mv libmlx.dylib ../libmlx.dylib
				$(CC) $(CPPFLAGS) -I $(HEADERS) $(OBJS) libmlx.dylib -o $(NAME)

all:			$(NAME)

.c.o:
				$(CC) $(CPPFLAGS) -I $(HEADERS) -o $@ -c $<

$(OBJS):		$(HEADERS)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS:.o=.d)

fclean:			clean
				cd minilibx && $(MAKE) clean
				$(RM) libmlx.dylib
				$(RM) $(NAME)

re:				fclean all

re_rt:			clean all

.PHONY:			all clean fclean re re_rt
.SILENT:
