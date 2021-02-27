#ifndef HOOKS_H
# define HOOKS_H

enum e_keys
{
	KEY_ESC		= 53,
	KEY_SPACE	= 49,
	KEY_W		= 13,
	KEY_A		= 0,
	KEY_S		= 1,
	KEY_D		= 2,
	KEY_Q		= 12,
	KEY_E		= 14,
	KEY_Z		= 6,
	KEY_X		= 7
};

int		new_frame(t_rt *s_rt);
int		key_press(int keycode, t_rt *s_rt);
int		key_release(int keycode, t_rt *s_rt);

#endif