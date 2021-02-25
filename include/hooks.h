#ifndef HOOKS_H
# define HOOKS_H

enum e_keys
{
	KEY_ESC		= 53,
	KEY_SPACE	= 49
};

void	get_another_camera(t_stage *s_stage);
int		key_hook(int keycode, t_stage *s_stage);

#endif