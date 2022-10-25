#include "./includes/minirt.h"

#define MAX_DEPTH 50

void routine(void *data)
{
	t_minirt	*vars;
	t_ray		init_ray;
	double		u;
	double		v;
	int 		x = vars->x;
	int			y = vars->y;
	int			s = 0;
	
	srand(time(0));
	vars = (t_minirt *)data;
	while (s ++ < vars->scene.anti / 6)
	{
		u = (((double)x + random_double(0, 1, vars->scene.anti)) * 2 / WIDTH) - 1;
		v = (((double)y + random_double(0, 1, vars->scene.anti)) * 2 / HEIGHT) - 1;
		init_ray = ray_primary(&(vars->scene.camera), u, v);
		if (x == 0 && y == 0)
			x = x;
		pthread_mutex_lock(vars->mutex);
		if (vars->is_trace == 1)
			*(vars->color) = vec_sum(vars->ray.color,
					ray_color(init_ray, &vars->scene, MAX_DEPTH));
		else
			*(vars->color) = vec_sum(vars->ray.color,
					ray_color_raw(init_ray, &vars->scene));
		pthread_mutex_unlock(vars->mutex);
	}
}

int threading(t_minirt *vars, int x, int y)
{
	int	i;

	i = 0;
	vars->x = x;
	vars->y = y;
	vars->color = (t_color *)malloc(sizeof(t_color));
	vars->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(vars->mutex, 0);
	while (i < 6)
	{
		if (pthread_create(&((vars->thr)[i]), 0, &routine, (void *)(vars)))
			return (printf("thread create error!\n"));
		pthread_detach(((vars->thr)[i]));
		i ++;
	}
	pthread_mutex_destroy(vars->mutex);
}