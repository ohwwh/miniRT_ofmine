/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:32:42 by hoh               #+#    #+#             */
/*   Updated: 2022/04/19 15:32:43 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define MAX_DEPTH 50 //재귀의 횟수가 깊어질 수록 그림자의 색깔이 물체의 색깔과 비슷해진다
t_color color;

t_vec rand_sphere()
{
	t_vec ret;

	while (1)
	{
		ret = create_vec(random_double(7), random_double(7), random_double(7));
		if (vec_len(ret) >= 1.0)
			continue ;
		//printf("%lf\n", ret.x);
		return (ret);
	}
}

t_vec rand_hemi_sphere(t_vec normal)
{
	t_vec ret;
	ret = rand_sphere();
	if (vdot(ret, normal) > 0.0)
		return (ret);
	else
		return (vec_scalar_mul(ret, -1));
}

/*t_color ray_color(t_ray ray, void* world[], t_record *rec, int depth)
{
	double t;
	t_vec n;
	int i = 0;

	while (i < 2)
	{
		if (hit_object((t_object*)world[i], &ray, rec))
		{
			if (i == 0)
			{
				n = unit_vec(vec_sub(ray_end(&ray, rec->t), ((t_object*)world[i])->center));
				return (vec_scalar_mul(create_vec(n.x + 1, n.y + 1, n.z + 1), 0.5));
			}
			else
			{
				return (create_vec(0.5, 0.75, 0.27));
			}
		}
		i ++;
	}
	t = 0.5 * (unit_vec((ray.dir)).y + 1.0);
	return (create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)));
}*/

/*int in_shadow()
{

}*/

t_color ray_color_2(t_ray r, void* world[])
{
	t_record rec;
	int i;
	double t;

	rec.t = 0.0;
	rec.t_min = 0.001;
	rec.t_max = INFINITY;
	i = 0;
	while ((t_object *)world[i])
	{
		hit_sphere((t_object*)world[i], &r, &rec);
		i ++;
	}
	if (rec.t > 0)
		return (rec.color); //record에 color까지 저장하고, idx를 굳이 저장하지 말것
	t = 0.5 * (unit_vec((r.dir)).y + 1.0);
	return (vec_scalar_mul(
		create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)), 0.7)
	);
	//return (create_vec(1,1,1));
}

t_color ray_color(t_ray r, t_object* world, int depth)
{
	double t;
	t_vec n;
	int i = 0;
	t_record rec;
	rec.t = 0.0;
	rec.t_min = 0.001;
	rec.t_max = INFINITY;

	if (depth <= 0)
        return (create_vec(0,0,0));
	/*while ((t_object*)world[i])
	{
		hit_sphere((t_object*)world[i], &r, &rec);
		i ++;
	}*/
	find_hitpoint(ray, world, &rec);
	//hit_cylinder(rec, &r, (t_cylinder *)world[5]);
	if (rec.t > 0)
	{
		t_color color;
		color  = rec.color;
		t_vec target;
		if (rec.mat == 0)//diffuse 재질인 경우
		{
			//target = vec_sum(vec_sum(rec.p, rec.normal), rand_sphere()); //wihtout lambertian
			target = vec_sum(rec.p, rand_hemi_sphere(rec.normal)); //with lambertian
			//lambertian 반사 구현할 때, 0으로 나누는 경우가 생김. 원문에서 bullet으로 검색해서 예외 처리 할 것
			color = vec_mul(color, ray_color(ray(rec.p, vec_sub(target, rec.p)), world, depth - 1));
		}
			
		else if (rec.mat == 1) //metal 재질인 경우
		{
			target = reflect(unit_vec(r.dir), rec.normal);
			t_ray scattered = ray(rec.p, target);
			if (vdot(scattered.dir, rec.normal) > 0)
				color = vec_mul(color, ray_color(ray(rec.p, target), world, depth - 1));
			else
				color = create_vec(0, 0, 0);
		}
		else if (rec.mat == -1) //light인 경우
			return (color);
		//color = vec_sum(color, point_light_get(&r, &rec, &light));
		return (color);
	}
	t = 0.5 * (unit_vec((r.dir)).y + 1.0);
	return (vec_scalar_mul(
		create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)), 0.1)
	);
	//return (create_vec(1,1,1));
}

void print_init(t_vars vars)
{
	double u;
	double v;
	t_vec dir;
	t_ray ray_tmp;
	int k = 0;
	for (int j = vars.window_height - 1; j >= 0; --j)
	{
		if (vars.is_trace == 1)
		{
			printf("\rScanlines remaining: %d", j);
			fflush(stdout);
		}
		for (int i = 0; i < vars.window_width; ++i)
		{
			//기본 색상을 어떻게 지정할까? 원하는 색의 rgb값 / 256 * anti 
			//물체마다 따로 지정하려면 어떻게 하나?
			//t_color color = create_vec(0, 0, 0);
			color = create_vec(0, 0, 0);
			for (int s = 0; s < vars.anti; s ++)
			{
				u = ((double)i + random_double(vars.anti)) / (vars.window_width-1);
				v = ((double)j + random_double(vars.anti)) / (vars.window_height-1);
				dir = create_vec(vars.camera.lower_left_corner.x + (u * vars.camera.horizontal.x) + (v * vars.camera.vertical.x) - vars.camera.origin.x,
				vars.camera.lower_left_corner.y + (u * vars.camera.horizontal.y) + (v * vars.camera.vertical.y) - vars.camera.origin.y,
				vars.camera.lower_left_corner.z + (u * vars.camera.horizontal.z) + (v * vars.camera.vertical.z) - vars.camera.origin.z);
				ray_tmp = ray(vars.camera.origin, dir);
				if (vars.is_trace == 1)
					color = vec_sum(color, ray_color(ray_tmp, vars.world, MAX_DEPTH));
				else
					color = vec_sum(color, ray_color_2(ray_tmp, vars.world));
			}
			color = vec_division(color, vars.anti);
			ft_pixel_put(&vars, i, vars.window_height - 1 - j, rgb_to_int(color));
		}
	}
}

int	main(int argc, char *argv[])
{
	t_object light = create_sphere(create_vec(4,8, -1), 4, 
	create_vec(8, 8, 8), -1);
	t_object surface = create_sphere(create_vec(0, -100.5, -1), 100, 
	//create_vec(1, 0.75, 0.8));
	create_vec(0.8, 0.8, 0), 0);
	light.next = &surface;
	t_object sphere = create_sphere(create_vec(0,0,-1), 0.5, 
	create_vec(0.7, 0.3, 0.3), 0);
	surface.next = &sphere;
	t_object metal = create_sphere(create_vec(1,0, -1), 0.5, 
	create_vec(0.8, 0.8, 0.8), 1);
	sphere.next = &metal;
	metal.next = 0;

	/*void *world[10];
	world[4] = 0;
	world[0] = (void *)(&sphere);
	world[1] = (void *)(&surface);
	world[2] = (void *)(&metal);
	world[3] = (void *)(&light);*/
	//world[5] = (void *)(&cylinder);
	//world[4] = (void *)(&light2);
	t_vars	vars;
	vars.is_trace = 0;
	vars.anti = 1;
	vars.is_move = -1;
	vars.changed = 0;
	vars.world = &light;
	vars.window_width = 640;
	vars.window_height = 320;
	int window_width = 640;
	int window_height = 320;
	double ratio = (double)vars.window_width / (double)vars.window_height;

	//t_camera camera = create_camera(create_vec(-1,2,1), create_vec(0,0,-1), create_vec(0, 1, 0), 80, ratio);
	t_camera camera = create_camera(create_vec(0,0,3), create_vec(0,0,-1), create_vec(0, 1, 0), 90, ratio);

	vars.camera = camera;
	ft_mlx_init(&vars);
	print_init(vars);
	mlx_hook(vars.win, 2, 0, &keybind, &vars);
	mlx_hook(vars.win, 3, 0, &keyrelease, &vars);
	//mlx_hook(vars.win,)
	mlx_loop_hook(vars.mlx, &key_hook_move, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
