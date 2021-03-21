#ifndef MATRIX_H
# define MATRIX_H

typedef struct	s_matrix {
	float	el[4][3];
}				t_matrix;

t_vec			matrix_mul(t_vec *u, t_matrix *m);
t_matrix		get_matrix_rotate(t_vec *s_vec_orig, t_vec *s_vec_dir);

#endif
