NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = $(wildcard src/*.c)
OBJS = ${SRCS:.c=.o}

.c.o:
				${CC} ${CFLAGS} -c $< -I include -o ${<:.c=.o}


${NAME}:		${OBJS}
				cd minilibx_mms && ${MAKE}
				cd minilibx_opengl && ${MAKE}
				${CC} ${CFLAGS} ${OBJS} libmlx.a libmlx.dylib -o ${NAME}

clean:
				${RM} ${OBJS}

fclean:			clean
				cd minilibx_mms && make clean
				cd minilibx_opengl && make clean
				${RM} ${NAME}

.DEFAULT_GOAL:	${NAME}
.PHONY:			all clean fclean
.SILENT:
