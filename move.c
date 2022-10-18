#include "miniRT.h"

/*t_vec   micro_vec(t_vec vec)
{
	double len = vec_len(vec);
	if (len == 0)
	{
		printf("Error : the length of vector is 0\n");
		exit(1);
	}
	vec.x /= 5;
	vec.y /= 5;
	vec.z /= 5;
	return (vec);
}*/

t_vec rotate(t_vec axis, t_minirt* vars, int dir)
{
	double c = (1 - cos(dir * 0.1));
	double s = sin(dir * 0.1);
	double x = axis.x;
	double y = axis.y;
	double z = axis.z;

	double i = vars->scene.camera.forward.x;
	double j = vars->scene.camera.forward.y;
	double k = vars->scene.camera.forward.z;

	t_vec new_dir;

	new_dir.x = -i*c*y*y-k*s*y+c*j*x*y-i*c*z*z+j*s*z+c*k*x*z+i;
	new_dir.y = j-c*j*x*x+k*s*x+i*c*x*y-c*j*z*z-i*s*z+c*k*y*z;
	new_dir.z = k-c*k*x*x-j*s*x-c*k*y*y+i*s*y+i*c*x*z+c*j*y*z;

	return (new_dir);
}

int key_hook_move(t_minirt* vars)
{
	if (vars->scene.changed == 1)
	{
		path_render(*vars);
		vars->scene.changed = 0;
	}
	if (vars->is_trace == 0)
	{
		if (vars->is_move == 13){
			t_vec dir = vars->scene.camera.forward;
			t_vec d = vec_division(dir, 1);
			t_vec new_org = vec_sum(vars->scene.camera.origin, d);
			vars->scene.camera.origin = new_org;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
		else if (vars->is_move == 0){
			t_vec dir = vec_scalar_mul(vars->scene.camera.right, -1);
			t_vec d = vec_division(dir, 1);
			t_vec new_org = vec_sum(vars->scene.camera.origin, d);
			vars->scene.camera.origin = new_org;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
		else if (vars->is_move == 1){
			t_vec dir = vars->scene.camera.forward;
			t_vec d = vec_division(dir, 1);
			t_vec new_org = vec_sub(vars->scene.camera.origin, d);
			vars->scene.camera.origin = new_org;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
		else if (vars->is_move == 2){
			t_vec dir = vars->scene.camera.right;
			t_vec d = vec_division(dir, 1);
			t_vec new_org = vec_sum(vars->scene.camera.origin, d);
			vars->scene.camera.origin = new_org;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
		else if (vars->is_move == 126)
		{
			t_vec new_dir;

			new_dir = rotate(vars->scene.camera.right, vars, -1);
			vars->scene.camera.forward = new_dir;
			vars->scene.camera.dir = new_dir;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
		else if (vars->is_move == 123)
		{
			t_vec new_dir;

			new_dir = rotate(vars->scene.camera.up, vars, -1);
			vars->scene.camera.forward = new_dir;
			vars->scene.camera.dir = new_dir;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
		else if (vars->is_move == 125)
		{
			t_vec new_dir;

			new_dir = rotate(vars->scene.camera.right, vars, 1);
			vars->scene.camera.forward = new_dir;
			vars->scene.camera.dir = new_dir;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
		else if (vars->is_move == 124)
		{
			t_vec new_dir;

			new_dir = rotate(vars->scene.camera.up, vars, 1);
			vars->scene.camera.forward = new_dir;
			vars->scene.camera.dir = new_dir;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
		else if (vars->is_move == 4 || vars->is_move == 5)
		{
			double new_fov;

			if ((vars->is_move == 4 && vars->scene.camera.fov <= 10)
				|| (vars->is_move == 5 && vars->scene.camera.fov >= 170))
			{
				printf("cannot zoom more\n");
				vars->is_move = -1;
				return (0);
			}
			if (vars->is_move == 4)
				new_fov = vars->scene.camera.fov - 10;
			else
				new_fov = vars->scene.camera.fov + 10;
			vars->scene.camera.fov = new_fov;
			vars->is_move = -1;
			set_camera(&vars->scene.camera);
			path_render(*vars);
		}
	}
	return (1);
}

int	keybind(int keycode, t_minirt* vars)
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
	if (keycode == 126)
		key_press_up(vars);
	else if (keycode == 123)
		key_press_left(vars);
	else if (keycode == 125)
		key_press_down(vars);
	else if (keycode == 124)
		key_press_right(vars);
	else if (keycode == 15)
	{
		if (vars->is_trace == 0)
		{
			vars->is_trace = 1;
			vars->scene.anti = 100;
			vars->scene.changed = 1;
		}
		else
		{
			vars->is_trace = 0;
			vars->scene.anti = 1;
			vars->scene.changed = 1;
		}
	}
	return (0);
}

int	keyrelease(int keycode, t_minirt* vars)
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
	else if (keycode == 126)
		vars->is_move = -1;
	else if (keycode == 123)
		vars->is_move = -1;
	else if (keycode == 125)
		vars->is_move = -1;
	else if (keycode == 124)
		vars->is_move = -1;
	return (0);
}

int scroll(int mousecode, int x, int y, t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot zoom here\n");
	if (mousecode == 4)
		vars->is_move = 4;
	else if (mousecode == 5)
		vars->is_move = 5;
	return (0);
}

void key_press_w(t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot move here\n");
	else
		vars->is_move = 13;
}

void key_press_a(t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot move here\n");
	else
		vars->is_move = 0;
}

void key_press_s(t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot move here\n");
	else
		vars->is_move = 1;
}

void key_press_d(t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot move here\n");
	else
		vars->is_move = 2;
}

void key_press_up(t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot move here\n");
	else
		vars->is_move = 126;
}

void key_press_left(t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot move here\n");
	else
		vars->is_move = 123;
}

void key_press_down(t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot move here\n");
	else
		vars->is_move = 125;
}

void key_press_right(t_minirt* vars)
{
	if (vars->is_trace == 1)
		printf("cannot move here\n");
	else
		vars->is_move = 124;
}
