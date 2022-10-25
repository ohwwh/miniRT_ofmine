#include "./includes/minirt.h"

#define MAX_DEPTH 50

void *routine(void *data)
{
	t_thread	*pdata;
	t_ray		init_ray;
	double		u;
	double		v;
	int 		x;
	int			y;
	int			s = 0;
	
	pdata = (t_thread *)data;
	while (1)
	{
		while (1)
		{
			pthread_mutex_lock(&(pdata->sh->mutex));
			if (pdata->sh->sampling != 0)
			{
				//printf("%d\n", pdata->sh->sampling);
				x = pdata->sh->x;
				y = pdata->sh->y;
				pthread_mutex_unlock(&(pdata->sh->mutex));
				break ;
			}
			pthread_mutex_unlock(&(pdata->sh->mutex));
		}
		while (s ++ < pdata->sh->vars->scene.anti / 6)
		{
			u = (((double)x + random_double(0, 1, pdata->sh->vars->scene.anti)) * 2 / WIDTH) - 1;
			v = (((double)y + random_double(0, 1, pdata->sh->vars->scene.anti)) * 2 / HEIGHT) - 1;
			init_ray = ray_primary(&(pdata->sh->vars->scene.camera), u, v);
			pthread_mutex_lock(&(pdata->sh->mutex));
			/*printf("%p\n", vars->color);
			sleep(5);*/
			if (pdata->sh->vars->is_trace == 1)
				pdata->sh->color = vec_sum(pdata->sh->color,
						ray_color(init_ray, &pdata->sh->vars->scene, MAX_DEPTH));
			else
				pdata->sh->color = vec_sum(pdata->sh->color,
						ray_color_raw(init_ray, &pdata->sh->vars->scene));
			/*if (x==320 && y==160)
				printf("%lf, %lf, %lf\n", pdata->sh->color.x, pdata->sh->color.y, pdata->sh->color.z);*/
			printf("thr_num[%d]: %d, %d\n", pdata->thr_num, x, y);
			pthread_mutex_unlock(&(pdata->sh->mutex));
		}
		pthread_mutex_lock(&(pdata->sh->mutex));
		if (pdata->sh->sampling > 0)
			pdata->sh->sampling --;
		pthread_mutex_unlock(&(pdata->sh->mutex));
		if (x == WIDTH && y == -1)
			break ;
	}
}