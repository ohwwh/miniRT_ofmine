/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:28:58 by hako              #+#    #+#             */
/*   Updated: 2022/10/2TH 10:17:20 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	thread_init(t_minirt *vars)
{
	t_shared	*sh;

	sh = (t_shared *)malloc(sizeof(t_shared));
	for (int i=0; i<TH; i++)
	{
		vars->thr[i].sh = sh;
		vars->thr[i].thr_num = i;
		vars->thr[0].sh->work[i] = 0;
		vars->thr[i].color = create_vec(0, 0, 0);
	}
	vars->thr[0].sh->x = 0;
	vars->thr[0].sh->y = HEIGHT - 2;
	pthread_mutex_init(&(vars->thr[0].sh->mutex), 0);
	vars->thr[0].sh->sampling = 0;
	vars->thr[0].sh->working = TH;
	vars->thr[0].sh->vars = vars;
}

void	init_rt(t_minirt *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT, "miniRT");
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	data->scene.objs = NULL;
	data->scene.amb.count = 0;
	data->scene.camera.count = 0;
	data->scene.light = NULL;
	data->is_move = -1;
	data->is_trace = 1;
	data->mode = 0;
	data->scene.anti = 102;
	data->scene.changed = 0;
}

void	sampling(t_minirt *vars, int x, int y)
{
	double	u;
	double	v;
	t_ray	init_ray;

	u = (((double)x + random_double(0, 1, vars->scene.anti)) * 2 / WIDTH) - 1;
	v = (((double)y + random_double(0, 1, vars->scene.anti)) * 2 / HEIGHT) - 1;
	init_ray = ray_primary(&(vars->scene.camera), u, v);
	if (x == 0 && y == 0)
		x = x;
	if (vars->is_trace == 1)
		vars->ray.color = vec_sum(vars->ray.color,
				ray_color(init_ray, &vars->scene, MAX_DEPTH));
	else
		vars->ray.color = vec_sum(vars->ray.color,
				ray_color_raw(init_ray, &vars->scene));
	//sleep(1);
	//		printf("%lf, %lf, %lf\n", vars->ray.color.x, vars->ray.color.y, vars->ray.color.z);
	//if (x == 320 && y == 1TH0)
		//printf("%lf, %lf, %lf\n", vars->ray.color.x, vars->ray.color.y, vars->ray.color.z);
}

t_color color_sum(t_minirt *vars)
{
	t_color ret;

	ret = create_vec(0, 0, 0);
	for (int i = 0; i < TH; i ++)
	{
		ret = vec_sum(ret, vars->thr[i].color);
	}

	return (ret);
}

void	path_render_thread(t_minirt *vars)
{
	int	x;
	int	y;
	int	s;
	int	i = 0;
	clock_t		start, end;
	double		result;

	start = clock();
	y = HEIGHT - 1;
	thread_init(vars);
	while (i < TH)
	{
		if (pthread_create(&((vars->thr[i].thr)), 0, routine, (void *)(&(vars->thr[i]))))
		{
			printf("thread create error!\n");
			return ;
		}
		pthread_detach(((vars->thr)[i].thr));
		i ++;
	}
	while (y -- >= 0)
	{
		x = 0;
		if (vars->is_trace == 1)
		{
			printf("\rScanlines remaining: %d", y);
			fflush(stdout);
		}
		while (x ++ < WIDTH)
		{
			while (1)
			{
				pthread_mutex_lock(&(vars->thr[0].sh->mutex));
				if (vars->thr[0].sh->working == 0)
				{
					//printf("i'm' break, son\n");
					vars->thr[0].sh->sampling = 1;
					vars->thr[0].sh->x = x;
					vars->thr[0].sh->y = y;
					break ;
				}
				pthread_mutex_unlock(&(vars->thr[0].sh->mutex));
			}
			vars->ray.color = vec_division(color_sum(vars), vars->scene.anti);
			//sleep(1);
				//printf("%lf, %lf, %lf\n", vars->thr[0].color.x, vars->thr[0].color.y, vars->thr[0].color.z);
				//printf("%lf, %lf, %lf\n", vars->thr[1].color.x, vars->thr[1].color.y, vars->thr[1].color.z);
				//printf("%lf, %lf, %lf\n", vars->thr[2].color.x, vars->thr[2].color.y, vars->thr[2].color.z);
				//printf("%lf, %lf, %lf", vars->ray.color.x, vars->ray.color.y, vars->ray.color.z);
			pthread_mutex_unlock(&(vars->thr[0].sh->mutex));
			put_color(&vars->mlx, x - 1,
				HEIGHT - 2 - y, rgb_to_int(vars->ray.color));
			pthread_mutex_lock(&(vars->thr[0].sh->mutex));
			//printf("\n");
			for (int k = 0; k < TH; k ++)
				vars->thr[k].color = create_vec(0, 0, 0);
			vars->thr[0].sh->working = TH;
			vars->thr[0].sh->sampling = 0;
			pthread_mutex_unlock(&(vars->thr[0].sh->mutex));
		}
	}
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
	end = clock();
	result = (double)(end - start);
	printf("\n%f", result / CLOCKS_PER_SEC);
	pthread_mutex_destroy(&(vars->thr[0].sh->mutex));
}

void	path_render(t_minirt *vars)
{
	int	x;
	int	y;
	int	s;
	int	i = 0;
	clock_t		start, end;
	double		result;

	start = clock();
	y = HEIGHT - 1;
	while (y -- >= 0)
	{
		x = 0;
		if (vars->is_trace == 1)
		{
			printf("\rScanlines remaining: %d", y);
			fflush(stdout);
		}
		while (x ++ < WIDTH)
		{
			vars->ray.color = create_vec(0, 0, 0);
			s = 0;
			if (x == 86 && y == 159)
				x = x;
			while (s ++ < vars->scene.anti)
				sampling(vars, x, y);
			vars->ray.color = vec_division(vars->ray.color, vars->scene.anti);
			put_color(&vars->mlx, x - 1,
				HEIGHT - 2 - y, rgb_to_int(vars->ray.color));
		}
	}
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
	end = clock();
	result = (double)(end - start);
	printf("\n%f\n", result / CLOCKS_PER_SEC);
}


void	set_init_distance(t_minirt *data)
{
	data->scene.camera.distance = vec_len(vec_sub(data->scene.camera.origin,
				data->scene.objs->center));
	data->scene.light->distance = vec_len(vec_sub(data->scene.light->object.center, 
				data->scene.objs->center));
	//빛이 없는 경우 / 오브젝트가 없는 경우?
}

int	main(int ac, char **av)
{
	t_minirt	data;
	int			fd;

	if (check_file(ac, av))
		err_handler("wrong argument");
	fd = open(av[1], O_RDONLY);
	init_rt(&data);
	parse(&data.scene, fd);
	set_init_distance(&data);
	create_light_object(&data.scene);
	set_camera(&data.scene.camera);
	path_render(&data);
	mlx_hook(data.mlx.mlx_win, 2, 0, &keypress, &data);
	mlx_hook(data.mlx.mlx_win, 3, 0, &keyrelease, &data);
	mlx_hook(data.mlx.mlx_win, 4, 0, &scroll, &data);
	mlx_hook(data.mlx.mlx_win, 17, 0L, ft_close, &data);
	mlx_loop_hook(data.mlx.mlx, &key_hook_move, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
