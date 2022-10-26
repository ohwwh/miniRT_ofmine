#include "./includes/minirt.h"

#define MAX_DEPTH 50

int equal(int work[], int idx)
{
	for (int i=0; i<TH; i++)
	{
		if (idx != i && work[idx] - work[i] > 0)
			return (0);
	}
	return (1);
}

void *routine(void *data)
{
	t_thread	*pdata;
	t_ray		init_ray;
	double		u;
	double		v;
	int 		x;
	int			y;
	int			s;
	
	//srand(time(0));
	pdata = (t_thread *)data;
	while (1)
	{
		while (1)
		{
			pthread_mutex_lock(&(pdata->sh->mutex));
			//printf("thr_num[%d], working: %d\n", pdata->thr_num, pdata->sh->working);
			if (pdata->sh->working != 0 && pdata->sh->sampling == 0 && equal(pdata->sh->work, pdata->thr_num) == 1)
			{
				//printf("thr_num[%d]: i'm break, papa!\n", pdata->thr_num);
				x = pdata->sh->x;
				y = pdata->sh->y;
				//pdata->sh->working ++;
				pthread_mutex_unlock(&(pdata->sh->mutex));
				break ;
			}
			pthread_mutex_unlock(&(pdata->sh->mutex));
		}
		s = 0;
		while (s ++ < pdata->sh->vars->scene.anti / TH)
		{
			u = (((double)x + random_double(0, 1, pdata->sh->vars->scene.anti)) * 2 / WIDTH) - 1;
			v = (((double)y + random_double(0, 1, pdata->sh->vars->scene.anti)) * 2 / HEIGHT) - 1;
			//pthread_mutex_lock(&(pdata->sh->mutex));
			init_ray = ray_primary(&(pdata->sh->vars->scene.camera), u, v);
			if (pdata->sh->vars->is_trace == 1)
				pdata->color = vec_sum(pdata->color,
						ray_color(init_ray, &pdata->sh->vars->scene, MAX_DEPTH));
			else
				pdata->color = vec_sum(pdata->color,
						ray_color_raw(init_ray, &pdata->sh->vars->scene));
			//pthread_mutex_unlock(&(pdata->sh->mutex));
			//printf("%lf, %lf, %lf\n", pdata->color.x, pdata->color.y, pdata->color.z);
		}
		pthread_mutex_lock(&(pdata->sh->mutex));
		if (pdata->sh->working > 0)
			pdata->sh->working --;
		pdata->sh->work[pdata->thr_num] ++;
		//sleep(1);
		//	printf("thr_num[%d]: %lf, %lf, %lf, working: %d\n", pdata->thr_num, pdata->color.x, pdata->color.y, pdata->color.z, pdata->sh->work[pdata->thr_num]);
		pthread_mutex_unlock(&(pdata->sh->mutex));
	}
}