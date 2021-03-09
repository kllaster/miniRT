NAME		= miniRT
CC			= gcc
RM			= rm -f
DEBUG		= 0
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
endif
CFLAGS		= -Wall -Wextra -Werror $(DEBUG_FLAGS) -D COUNT_THREADS=$(COUNT_THREADS)
CPPFLAGS	= $(CFLAGS) -march=native -O2 -msse4a -flto -pipe
HEADER		= include

SRCS =	src/main.c\
		src/utils.c\
		src/save_img.c\
		src/hooks.c\
		src/hooks_utils.c\
		src/colors_utils.c\
		src/matrix_utils.c\
		src/vectors_utils.c\
		parser/debug_window.c\
		parser/debug_struct.c\
		parser/get_next_line.c\
		parser/get_next_line_utils.c\
		parser/parse_utils.c\
		parser/parse_objs.c\
		parser/parser.c\
		render/render.c\
		render/threads.c\
		render/init_render.c\
		render/render_utils.c\
		render/intersections/inter_plane.c\
		render/intersections/inter_sphere.c\
		render/intersections/inter_square.c\
		render/intersections/inter_triangle.c\

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

all:			$(OBJS)
				cd minilibx && $(MAKE) && mv libmlx.dylib ../libmlx.dylib
				$(CC) $(CPPFLAGS) -I $(HEADER) $(OBJS) libmlx.dylib -o $(NAME)

.c.o:
				$(CC) $(CPPFLAGS) -I $(HEADER) -o $@ -c $<

clean:
				$(RM) $(OBJS)

fclean:			clean
				cd minilibx && $(MAKE) clean
				$(RM) libmlx.dylib
				$(RM) $(NAME)

re:				fclean all

re_rt:			clean all

.DEFAULT_GOAL:	$(NAME)
.PHONY:			$(NAME) all clean fclean re re_rt
.SILENT:
