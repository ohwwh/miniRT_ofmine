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

#include "ray.h"
#include "ft_mlx.h"
#include "sphere.h"
#include "random.h"
#include "light.h"
#include "camera.h"
#include "libohw/includes/libft.h"
#define MAX_DEPTH 50 //재귀의 횟수가 깊어질 수록 그림자의 색깔이 물체의 색깔과 비슷해진다
//#define ANTI 100


t_vec rand_sphere()
{
	t_vec ret;

	while (1)
	{
		ret = create_vec(random_double(), random_double(), random_double());
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
		if (hit_sphere((t_sphere *)world[i], &ray, rec))
		{
			if (i == 0)
			{
				n = unit_vec(vec_sub(ray_end(&ray, rec->t), ((t_sphere *)world[i])->center));
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

t_color ray_color(t_ray r, void* world[], int depth)
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
	while ((t_sphere *)world[i])
	{
		hit_sphere((t_sphere *)world[i], i, &r, &rec);
		i ++;
	}
	if (rec.t > 0)
	{
		t_color color;
		color  = ((t_sphere *)world[rec.idx])->color;
		t_vec target;
		if (rec.mat == 0)//diffuse 재질인 경우
		{
			//target = vec_sum(vec_sum(rec.p, rec.normal), rand_sphere()); //wihtout lambertian
			target = vec_sum(rec.p, rand_hemi_sphere(rec.normal)); //with lambertian
			//lambertian 반사 구현할 때, 0으로 나누는 경우가 생김. 원문에서 bullet으로 검색해서 예외 처리 할 것
			color = vec_mul(color, ray_color(ray(rec.p, vec_sub(target, rec.p)), world,depth - 1));
		}
			
		else if (rec.mat == 1) //metal 재질인 경우
		{
			target = reflect(unit_vec(r.dir), rec.normal);
			t_ray scattered = ray(rec.p, target);
			if (vdot(scattered.dir, rec.normal) > 0)
				color = vec_mul(color, ray_color(ray(rec.p, target), world,depth - 1));
			else
				color = create_vec(0, 0, 0);
		}
		else if (rec.mat == -1) //light인 경우
			return (color);
		//color = vec_sum(color, point_light_get(&r, &rec, &light));
		return (color);
	}
	/*if (depth < MAX_DEPTH)
		return (create_vec(1, 1, 1)); //하늘 색을 반영할 것인가 말 것인가......*/
	t = 0.5 * (unit_vec((r.dir)).y + 1.0);
	return (vec_scalar_mul(
		create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)), 0.7)
	);
	//return (create_vec(1,1,1));
}

int	main(int argc, char *argv[])
{
	t_sphere sphere = create_sphere(create_vec(0,0,-1), 0.5, 
	create_vec(0.7, 0.3, 0.3), 0);
	t_sphere surface = create_sphere(create_vec(0, -100.5, -1), 100, 
	//create_vec(1, 0.75, 0.8));
	create_vec(0.8, 0.8, 0), 0);
	t_sphere metal = create_sphere(create_vec(-1,0, -1), 0.5, 
	create_vec(0.8, 0.8, 0.8), 1);
	t_sphere light = create_sphere(create_vec(4,8, -1), 4, 
	create_vec(15, 15, 15), -1);
	void *world[10];
	world[4] = 0;
	world[0] = (void *)(&sphere);
	world[1] = (void *)(&surface);
	world[2] = (void *)(&metal);
	world[3] = (void *)(&light);
	t_vars	vars;
	//double ratio = 16.0 / 10.0;
	int window_width = 640;
	int window_height = 320;
	double ratio = (double)window_width / (double)window_height;

	t_camera camera = create_camera(create_vec(0,2,5), create_vec(0,0,-1), create_vec(0, 1, 0), 30, ratio);
	//t_camera camera = create_camera(create_vec(0,0,0), create_vec(0,0,-1), create_vec(0, 1, 0), 90, ratio);
	
	ft_mlx_init(&vars);
	//srand(time(0));
	double u;
	double v;
	t_vec dir;
	t_ray ray_tmp;
	for (int j = window_height - 1; j >= 0; --j)
	{
		for (int i = 0; i < window_width; ++i)
		{
			//t_color color = create_vec(1 * 60.0, 0.2 * 60.0, 0.6 * 60.0); // 여기서 뭔가 바꼈는데??
			//기본 색상을 어떻게 지정할까? 원하는 색의 rgb값 / 256 * anti 
			//물체마다 따로 지정하려면 어떻게 하나?
			t_color color = create_vec(0, 0, 0);
			for (int s = 0; s < ANTI; s ++)
			{
				u = ((double)i + random_double()) / (window_width-1);
				v = ((double)j + random_double()) / (window_height-1);
				dir = create_vec(camera.lower_left_corner.x + (u * camera.horizontal.x) + (v * camera.vertical.x) - camera.origin.x,
				camera.lower_left_corner.y + (u * camera.horizontal.y) + (v * camera.vertical.y) - camera.origin.y,
				camera.lower_left_corner.z + (u * camera.horizontal.z) + (v * camera.vertical.z) - camera.origin.z);
				ray_tmp = ray(camera.origin, dir);
				color = vec_sum(color, ray_color(ray_tmp, world, MAX_DEPTH));
			}
			//ANTI = 0 일때 예외처리
			color = vec_division(color, ANTI);
			ft_pixel_put(&vars, i, window_height - 1 - j, rgb_to_int(color));
			/*t_color color = create_vec(0, 0, 0);
			u = ((double)i) / (window_width-1);
			v = ((double)j) / (window_height-1);
			dir = create_vec(lower_left_corner.x + (u * horizontal.x) + (v * vertical.x) - origin.x,
			lower_left_corner.y + (u * horizontal.y) + (v * vertical.y) - origin.y,
			lower_left_corner.z + (u * horizontal.z) + (v * vertical.z) - origin.z);
			ray_tmp = ray(origin, dir);
			color = vec_sum(color, ray_color(ray_tmp, world, MAX_DEPTH));
			ft_pixel_put(&vars, i, window_height - 1 - j, rgb_to_int(color));*/ //안티앨리어싱 없음
		}
	}
	mlx_loop(vars.mlx);
	return (0);
}
