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
			printf("thr_num[%d], sampling: %d\n", pdata->thr_num, pdata->sh->sampling);
			if (pdata->sh->sampling != 0)
			{
				printf("thr_num[%d]: i'm here, papa!\n", pdata->thr_num);
				x = pdata->sh->x;
				y = pdata->sh->y;
				//pdata->sh->sampling ++;
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
			if (pdata->sh->vars->is_trace == 1)
				pdata->sh->color = vec_sum(pdata->sh->color,
						ray_color(init_ray, &pdata->sh->vars->scene, MAX_DEPTH));
			else
				pdata->sh->color = vec_sum(pdata->sh->color,
						ray_color_raw(init_ray, &pdata->sh->vars->scene));
			/*if (x==320 && y==160)
				printf("%lf, %lf, %lf\n", pdata->sh->color.x, pdata->sh->color.y, pdata->sh->color.z);*/
			pthread_mutex_unlock(&(pdata->sh->mutex));
		}
		pthread_mutex_lock(&(pdata->sh->mutex));
		pdata->sh->working --;
		if (pdata->sh->sampling > 0)
			pdata->sh->sampling --;
		sleep(1);
			printf("thr_num[%d], x: %d, y: %d, sampling: %d\n", pdata->thr_num, x, y, pdata->sh->sampling);
		pthread_mutex_unlock(&(pdata->sh->mutex));
		while (1)
		{
			pthread_mutex_lock(&(pdata->sh->mutex));
			if (pdata->sh->sampling == 0)
			{
				//printf("thr_num[%d]: i'm break!\n", pdata->thr_num);
				pthread_mutex_unlock(&(pdata->sh->mutex));
				break ;
			}
			pthread_mutex_unlock(&(pdata->sh->mutex));
		}
	}
}