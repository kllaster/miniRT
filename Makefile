NAME	= miniRT
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
HEADER	= include

SRCS =	src/main.c\
		src/utils.c\
		src/vectors.c\
		parser/debug_struct.c\
		parser/get_next_line.c\
		parser/get_next_line_utils.c\
		parser/parse_utils.c\
		parser/parse_objs.c\
		parser/parser.c\
		render/render.c\
		render/init_render.c\
		render/render_utils.c\
		render/intersections/inter_sphere.c\
		render/intersections/inter_plane.c\


OBJS = ${SRCS:.c=.o}

all:			$(NAME)

%.o: %.c
				$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

${NAME}:		${OBJS}
				cd minilibx && ${MAKE} && mv libmlx.dylib ../libmlx.dylib
				$(CC) $(CFLAGS) -I $(HEADER) $(OBJS) libmlx.dylib -o $(NAME)

clean:
				${RM} ${OBJS}

fclean:			clean
				cd minilibx && ${MAKE} clean
				${RM} libmlx.dylib
				${RM} ${NAME}

re:				fclean all

re_rt:			clean all

.DEFAULT_GOAL:	${NAME}
.PHONY:			all clean fclean
.SILENT:
