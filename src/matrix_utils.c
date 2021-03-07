#include "mini_rt.h"

t_vec		matrix_mul(t_vec *u, t_matrix *m)
{
	t_vec	v;

	v.x = u->x * m->el[0][0] + u->y * m->el[1][0] +
			u->z * m->el[2][0] + m->el[3][0];
	v.y = u->x * m->el[0][1] + u->y * m->el[1][1] +
			u->z * m->el[2][1] + m->el[3][1];
	v.z = u->x * m->el[0][2] + u->y * m->el[1][2] +
			u->z * m->el[2][2] + m->el[3][2];
	return (v);
}

t_matrix	get_matrix_rotate(t_vec *s_vec_orig, t_vec *s_vec_dir)
{
	t_matrix	s_matrix;
	t_vec		s_vec_tmp;

	s_vec_tmp = (t_vec){0, 1, 0};
	s_vec_tmp = vec_cross_product(&s_vec_tmp, s_vec_dir);
	s_vec_tmp = vec_norm(&s_vec_tmp);
	s_matrix.el[0][0] = s_vec_tmp.x;
	s_matrix.el[0][1] = s_vec_tmp.y;
	s_matrix.el[0][2] = s_vec_tmp.z;
	s_vec_tmp = vec_cross_product(s_vec_dir, &s_vec_tmp);
	s_vec_tmp = vec_norm(&s_vec_tmp);
	s_matrix.el[1][0] = s_vec_tmp.x;
	s_matrix.el[1][1] = s_vec_tmp.y;
	s_matrix.el[1][2] = s_vec_tmp.z;
	s_matrix.el[2][0] = s_vec_dir->x;
	s_matrix.el[2][1] = s_vec_dir->y;
	s_matrix.el[2][2] = s_vec_dir->z;
	s_matrix.el[3][0] = s_vec_orig->x;
	s_matrix.el[3][1] = s_vec_orig->y;
	s_matrix.el[3][2] = s_vec_orig->z;
	return (s_matrix);
}
