#ifndef HOOKS_H
# define HOOKS_H

enum e_keys
{
	KEY_ESC		= 53,
	KEY_SPACE	= 49
};

int		key_hook(int keycode, t_rt *s_rt);

#endif