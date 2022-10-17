#ifndef MOVE_H
#define MOVE_H
#include "ft_mlx.h"
#include "miniRT.h"

int	keybind(int keycode, t_minirt* vars);
int	keyrelease(int keycode, t_minirt* vars);
int scroll(int mousecode, int x, int y, t_minirt* vars);
int key_hook_move(t_minirt* vars);
void key_press_w(t_minirt* vars);
void key_press_a(t_minirt* vars);
void key_press_s(t_minirt* vars);
void key_press_d(t_minirt* vars);
void key_press_up(t_minirt* vars);
void key_press_left(t_minirt* vars);
void key_press_down(t_minirt* vars);
void key_press_right(t_minirt* vars);

#endif