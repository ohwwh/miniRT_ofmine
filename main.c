/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:28:58 by hako              #+#    #+#             */
/*   Updated: 2022/10/25 10:40:12 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	thread_init(t_minirt *vars)
{
	t_shared	*sh;

	sh = (t_shared *)malloc(sizeof(t_shared));
	for (int i=0; i<6; i++)
	{
		vars->thr[i].sh = sh;
		vars->thr[i].thr_num = i;
	}
	vars->thr[0].sh->x = 0;
	vars->thr[0].sh->y = HEIGHT - 2;
	vars->thr[0].sh->color = create_vec(0, 0, 0);
	pthread_mutex_init(&(vars->thr[0].sh->mutex), 0);
	vars->thr[0].sh->sampling = 6;
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
	data->scene.anti = 6;
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
	if (x == 320 && y == 160)
		printf("%lf, %lf, %lf\n", vars->ray.color.x, vars->ray.color.y, vars->ray.color.z);
}

void	path_render(t_minirt *vars)
{
	int	x;
	int	y;
	int	s;
	int	i = 0;

	y = HEIGHT - 1;
	thread_init(vars);
	while (i < 6)
	{
		if (pthread_create(&((vars->thr[i].thr)), 0, routine, (void *)(&(vars->thr[i]))))
		{
			printf("thread create error!\n");
			return ;
		}
		//pthread_detach(((vars->thr)[i]));
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
			/*vars->ray.color = create_vec(0, 0, 0);
			s = 0;
			while (s ++ < vars->scene.anti)
				sampling(vars, x, y);
			vars->ray.color = vec_division(vars->ray.color, vars->scene.anti);*/
			while (1)
			{
				pthread_mutex_lock(&(vars->thr[0].sh->mutex));
				if (vars->thr[0].sh->sampling == 0)
				{
					vars->thr[0].sh->x = x;
					vars->thr[0].sh->y = y;
					vars->thr[0].sh->color = create_vec(0, 0, 0);
					break ;
				}
				pthread_mutex_unlock(&(vars->thr[0].sh->mutex));
			}
			//printf("%d\n", vars->sh->sampling);
			/*if (x==320 && y==160)
				printf("%lf, %lf, %lf\n", vars->sh->color.x, vars->sh->color.y, vars->sh->color.z);*/
			vars->ray.color = vec_division(vars->thr[0].sh->color, vars->scene.anti);
			pthread_mutex_unlock(&(vars->thr[0].sh->mutex));
			put_color(&vars->mlx, x - 1,
				HEIGHT - 2 - y, rgb_to_int(vars->ray.color));
			pthread_mutex_lock(&(vars->thr[0].sh->mutex));
			vars->thr[0].sh->sampling = 6;
			pthread_mutex_unlock(&(vars->thr[0].sh->mutex));
		}
	}
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.mlx_win, vars->mlx.img, 0, 0);
	i = 0;
	//printf("%d, %d\n", x, y);
	/*while (i < 6)
	{
		pthread_join(((vars->thr)[i]), 0);
		i ++;
	}
	printf("%d, %d\n", x, y);*/
	//free(vars->sh);
	//vars->sh = 0;
	pthread_mutex_destroy(&(vars->thr[0].sh->mutex));
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
