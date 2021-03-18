#ifndef HOOKS_H
# define HOOKS_H

# include "mini_rt.h"
# define TIME2HOOK (1000 / MAX_FPS)

enum	e_keys {
	KEY_ESC = 53,
	KEY_SPACE = 49,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_Q = 12,
	KEY_E = 14,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_F5 = 96,
	BUTTON_1 = 1,
	BUTTON_2 = 2
};

void	change_frame(t_rt *s_rt, void *img_old_p);
int		new_frame(t_rt *s_rt);
int		key_press(int keycode, t_rt *s_rt);
int		key_release(int keycode, t_rt *s_rt);
int		mouse_press(int button, int x, int y, t_rt *s_rt);
int		change_pos_cam(t_rt *s_rt, t_vec *s_vec_pos);
int		change_dir_cam(t_rt *s_rt, t_vec *s_vec);
void	render_all_images(t_rt *s_rt);
int		check_hooks(t_rt *s_rt);

#endif
