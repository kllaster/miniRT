#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 32

int		ft_strlen(char *str);
int		ft_strichr(char *str, int sumb);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		get_next_line(int fd, char **line);

#endif
