#ifndef VECTORS_H
# define VECTORS_H

typedef	struct	s_vec {
	float		x;
	float		y;
	float		z;
}				t_vec;

float	vec_len(t_vec *s_vec);
t_vec	vec_norm(t_vec *s_vec);
t_vec	vec_sum(t_vec *s_vec_1, t_vec *s_vec_2);
t_vec	vec_sub(t_vec *s_vec_1, t_vec *s_vec_2);
t_vec	vec_mul(t_vec *s_vec, float num);
t_vec	vec_cross_product(t_vec *s_vec_1, t_vec *s_vec_2);
int		vec_check_unzero(t_vec *s_vec);
float	vec_scalar_mul(t_vec *s_vec_1, t_vec *s_vec_2);
void	vec_rotate_x(t_vec *s_vec, float sin, float cos);
void	vec_rotate_y(t_vec *s_vec, float sin, float cos);
void	vec_rotate_z(t_vec *s_vec, float sin, float cos);

#endif
