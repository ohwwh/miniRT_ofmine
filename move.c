#include "move.h"

t_vec   micro_vec(t_vec vec)
{
    double len = vec_len(vec);
    if (len == 0)
    {
        printf("Error : the length of vector is 0\n");
        exit(1);
    }
    vec.x /= (len * 15);
    vec.y /= (len * 15);
    vec.z /= (len * 15);
    return (vec);
}

int key_hook_move(t_vars* vars)
{
    if (vars->changed == 1)
    {
        print_init(*vars);
        vars->changed = 0;
    }
    if (vars->is_trace == 0)
    {
        if (vars->is_move == 13){
            t_vec new_org = vec_sum(vars->camera.origin, micro_vec(vec_sub(vars->camera.lookat, vars->camera.origin)));
            t_vec new_lookat = vec_sum(vars->camera.lookat, micro_vec(vec_sub(vars->camera.lookat, vars->camera.origin)));
            vars->camera = create_camera(new_org, new_lookat, vars->camera.vup, vars->camera.vfov, vars->camera.ratio);
            print_init(*vars);
        }
        else if (vars->is_move == 0){
            t_vec dir = vec_sub(vars->camera.lookat, vars->camera.origin);
            //t_vec a_dir = create_vec(1, vars->camera.origin.y, (-(dir.x + (dir.y * vars->camera.origin.y)) / dir.z));
            t_vec a_dir = vcross(vars->camera.vup, dir);
            t_vec cross = vcross(a_dir, dir);
            if (vdot(cross, create_vec(0,1,0)) > 0)
                vec_scalar_mul(a_dir, -1);
            t_vec new_org = vec_sum(vars->camera.origin, micro_vec(a_dir));
            t_vec new_lookat = vec_sum(vars->camera.lookat, micro_vec(a_dir));
            vars->camera = create_camera(new_org, new_lookat, vars->camera.vup, vars->camera.vfov, vars->camera.ratio);
            print_init(*vars);
        }
        else if (vars->is_move == 1){
            t_vec new_org = vec_sum(vars->camera.origin, micro_vec(vec_sub(vars->camera.origin, vars->camera.lookat)));
            t_vec new_lookat = vec_sum(vars->camera.lookat, micro_vec(vec_sub(vars->camera.origin, vars->camera.lookat)));
            vars->camera = create_camera(new_org, new_lookat, vars->camera.vup, vars->camera.vfov, vars->camera.ratio);
            print_init(*vars);
        }
        else if (vars->is_move == 2){
            t_vec dir = vec_sub(vars->camera.lookat, vars->camera.origin);
            t_vec a_dir = vcross(vars->camera.vup, dir);
            t_vec cross = vcross(a_dir, dir);
            if (vdot(cross, create_vec(0,1,0)) < 0)
                vec_scalar_mul(a_dir, -1);
            t_vec new_org = vec_sub(vars->camera.origin, micro_vec(a_dir));
            t_vec new_lookat = vec_sub(vars->camera.lookat, micro_vec(a_dir));
            vars->camera = create_camera(new_org, new_lookat, vars->camera.vup, vars->camera.vfov, vars->camera.ratio);
            print_init(*vars);
        }
    }
    return (1);
}

int	keybind(int keycode, t_vars* vars)
{
	//printf("keycode=%d\n", keycode);
	if (keycode == 13)
		key_press_w(vars);
    else if (keycode == 0)
		key_press_a(vars);
    else if (keycode == 1)
		key_press_s(vars);
    else if (keycode == 2)
		key_press_d(vars);
    else if (keycode == 15)
    {
        if (vars->is_trace == 0)
        {
            vars->is_trace = 1;
            vars->anti = 100;
            vars->changed = 1;
        }
        else
        {
            vars->is_trace = 0;
            vars->anti = 2;
            vars->changed = 1;
        }
    }
	return (0);
}

int	keyrelease(int keycode, t_vars* vars)
{
	//printf("key release=%d\n", keycode);
	if (keycode == 13)
		vars->is_move = -1;
    else if (keycode == 0)
		vars->is_move = -1;
    else if (keycode == 1)
		vars->is_move = -1;
    else if (keycode == 2)
		vars->is_move = -1;
	return (0);
}

void key_press_w(t_vars* vars)
{
    if (vars->is_trace == 1)
        printf("cannot move here\n");
    else
        vars->is_move = 13;
}

void key_press_a(t_vars* vars)
{
    if (vars->is_trace == 1)
        printf("cannot move here\n");
    else
        vars->is_move = 0;
}

void key_press_s(t_vars* vars)
{
    if (vars->is_trace == 1)
        printf("cannot move here\n");
    else
        vars->is_move = 1;
}

void key_press_d(t_vars* vars)
{
    if (vars->is_trace == 1)
        printf("cannot move here\n");
    else
        vars->is_move = 2;
}
