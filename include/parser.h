#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"

void	debug_window_put_camera(t_rt *s_rt);
void	debug_print_s_vec(t_vec *s_vec, char *s_name);
void	debug_print_s_color(t_rgb *s_color);
void	debug_print_s_stage(t_stage *s_stage);
void	skip_between_param(char **str, char symb);
float	parse_float(char **str);
t_rgb	*parse_rgb(char **str);
t_vec	*parse_coordinates(char **str);
void	parse_objs(char *str, t_stage *s_stage);
void	parse_file(char *file, t_stage *s_stage);

#endif
