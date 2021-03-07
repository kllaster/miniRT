#ifndef VECTORS_H
# define VECTORS_H

typedef	struct	s_vec {
	float	x;
	float	y;
	float	z;
}				t_vec;

float			vec_len(const t_vec *s_vec);
t_vec			vec_norm(const t_vec *s_vec);
t_vec			vec_sum(const t_vec *s_vec_1, const t_vec *s_vec_2);
t_vec			vec_sub(const t_vec *s_vec_1, const t_vec *s_vec_2);
t_vec			vec_mul(const t_vec *s_vec, float num);
t_vec			vec_cross_product(const t_vec *s_vec_1, const t_vec *s_vec_2);
int				vec_check_unzero(const t_vec *s_vec);
float			vec_scalar_mul(const t_vec *s_vec_1, const t_vec *s_vec_2);
void			vec_rotate_x(t_vec *s_vec, float sin, float cos);
void			vec_rotate_y(t_vec *s_vec, float sin, float cos);
void			vec_rotate_z(t_vec *s_vec, float sin, float cos);

#endif
