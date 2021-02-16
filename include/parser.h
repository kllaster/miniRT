#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"

void			debug_print_s_coordinates(t_coordinates *s_coordinates, char *s_name);
void			debug_print_s_stage(t_stage *s_stage);
void			skip_between_arg(char **str);
double			parse_double(char **str);
t_rgb			*parse_rgb(char **str);
t_coordinates	*parse_coordinates(char **str);
void			parse_objs(char *str, t_stage *s_stage);
void			parse_file(char *file, t_stage *s_stage);

#endif
