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
		ret = create_vec(random_double(-1,1,7), random_double(-1,1,7), random_double(-1,1,7));
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

t_color ray_color_2(t_ray r, t_object* world)
{
	t_record rec;
	int i;
	double t;

	rec.t = 0.0;
	rec.t_min = 0.001;
	rec.t_max = INFINITY;
	i = 0;
	find_hitpoint(&r, world, &rec);
	if (rec.t > 0)
		return (rec.color);
	t = 0.5 * (unit_vec((r.dir)).y + 1.0);
	return (vec_scalar_mul(
		create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)), 0.2)
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

	find_hitpoint(&r, world, &rec);
	if (rec.t > 0)
	{
		t_color color;
		color  = rec.color;
		t_vec target;
		if (rec.mat == 0)//diffuse 재질인 경우
		{
			/*//target = vec_sum(vec_sum(rec.p, rec.normal), rand_sphere()); //wihtout lambertian
			target = vec_sum(rec.p, rand_hemi_sphere(rec.normal)); //with lambertian
			//lambertian 반사 구현할 때, 0으로 나누는 경우가 생김. 원문에서 bullet으로 검색해서 예외 처리 할 것
			color = vec_mul(color, ray_color(ray(rec.p, vec_sub(target, rec.p)), world, depth - 1));*/
			target = vec_sum(rec.normal, rand_sphere()); 
			color = vec_mul(color, ray_color(ray(rec.p, target), world, depth - 1)); // material 클래스 추가 이후 부터 갑자기 바뀌었다. 왜 램버시안 반사를 없앴지??
			

			/*target = vec_sum(vec_sum(rec.p, rec.normal), unit_vec(rand_sphere()));
			t_ray scattered = ray(rec.p, unit_vec(target));
			double pdf = vdot(rec.normal, scattered.dir) / 3.1415926535897932385;
			double scat_pdf;
			double cos;
			cos = vdot(rec.normal, unit_vec(scattered.dir));
			if (cos < 0)
				scat_pdf = 0;
			else
				scat_pdf = cos / 3.1415926535897932385;
			color = vec_mul(vec_scalar_mul(color, scat_pdf), 
			vec_division(ray_color(ray(rec.p, vec_sub(target, rec.p)), world, depth - 1), pdf));
			//unit_sphere를 이용한 난반사 구현*/
			


			/*target = rand_hemi_sphere(rec.normal);
			t_ray scattered = ray(rec.p, unit_vec(target));
			double pdf = 0.5 / 3.1415926535897932385;
			double scat_pdf;
			double cos;
			cos = vdot(rec.normal, unit_vec(scattered.dir));
			if (cos < 0)
				scat_pdf = 0;
			else
				scat_pdf = cos / 3.1415926535897932385;
			color = vec_mul(vec_scalar_mul(color, scat_pdf), 
			vec_division(ray_color(scattered, world, depth - 1), pdf));
			//hemisphere를 이용한 난반사 구현(lambertian)*/


			/*t_vec on_light = create_vec(random_double(0,4,7), 8, random_double(-3,-1,7));
			t_vec to_light = vec_sub(on_light, rec.p);
			double distance_squared = pow(vec_len(to_light), 2);
			to_light = unit_vec(to_light);

			if (vdot(to_light, rec.normal) < 0)
				return (create_vec(0,0,0));

			double light_area = (2)*(2);
			double light_cosine = fabs(to_light.y);
			if (light_cosine < 0.000001)
				return (create_vec(0,0,0));

			double pdf = distance_squared / (light_cosine * light_area);
			t_ray scattered = ray(rec.p, to_light);
			double scat_pdf;
			double cos;
			cos = vdot(rec.normal, unit_vec(scattered.dir));
			if (cos < 0)
				scat_pdf = 0;
			else
				scat_pdf = cos / 3.1415926535897932385;
			color = vec_mul(vec_scalar_mul(color, scat_pdf), 
			vec_division(ray_color(scattered, world, depth - 1), pdf));
			//light sampling*/
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
		create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)), 0.2)
	);
	//return (create_vec(1,1,1));
}

void print_init(t_vars vars)
{
	//printf("%lf, %lf, %lf\n", vars.camera.origin.x, vars.camera.origin.y, vars.camera.origin.z);
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
			//물체마다 따로 지정하려면 어떻C게 하나?
			//t_color color = create_vec(0, 0, 0);
			color = create_vec(0, 0, 0);
			for (int s = 0; s < vars.anti; s ++)
			{
				u = ((double)i + random_double(-1,1,vars.anti)) / (vars.window_width-1);
				v = ((double)j + random_double(-1,1,vars.anti)) / (vars.window_height-1);
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
	/*t_object light = create_sphere(create_vec(5,8, -1), 0, 
	create_vec(4, 4, 4), -1);

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

	t_object cylinder = create_cylinder(create_vec(1,1,-1), 0.4, 1, 
	create_vec(1,-1,0), create_vec(0.3,0.3,0.7), 0);
	cylinder.next = 0;
	light.next = &surface;
	/*surface.next = &cylinder;
	cylinder.next = &sphere;
	sphere.next = 0;*/




	/*t_object green = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.12, 0.45, 0.15), 0);
	t_object red = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.65, 0.05, 0.05), 0);
	t_object light = create_rectangle_xz(create_vec(213,343,0), create_vec(227,332,0), 554, 
	create_vec(15, 15, 15), -1);
	/*light = create_sphere(create_vec(250,540,210), 90, 
	create_vec(4, 4, 4), -1);*/
	/*t_object white1 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0);
	t_object white2 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.73, 0.73, 0.73), 0);
	t_object white3 = create_rectangle_xy(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0);
	t_object sphere = create_sphere(create_vec(190,90,190), 90, 
	create_vec(0.7, 0.3, 0.3), 0);

	sphere.next = &light;
	light.next = &white2;
	white2.next = &white3;
	white3.next = &green;
	green.next = &red;
	red.next = &white1;
	white1.next = 0;*/

	


	
	/*t_object light = create_rectangle_xy(create_vec(3,5,0), create_vec(1,3,0), 
	-4, create_vec(15, 15, 15), -1);*/
	t_object light = create_sphere(create_vec(2, 8, -10), 2, 
	create_vec(15, 15, 15), -1);

	t_object surface = create_sphere(create_vec(0, -1000, 0), 1000, 
	create_vec(0.8, 0.8, 0), 0);
	light.next = &surface;

	t_object sphere = create_sphere(create_vec(0,2,0), 2, 
	create_vec(0.7, 0.3, 0.3), 0);
	surface.next = &sphere;
	t_object wall = create_plane(create_vec(0, 50, 0), 
	vec_sub(create_vec(0,5,0), create_vec(26,3,6)), create_vec(0.5, 0.5, 0.58), 0);
	sphere.next = 0;
	wall.next = 0;


	t_vars	vars;
	vars.is_trace = 0;
	vars.anti = 1;
	vars.is_move = -1;
	vars.changed = 0;
	vars.world = &light;
	//vars.world = &sphere;
	vars.window_width = 640;
	vars.window_height = 320;
	int window_width = 640;
	int window_height = 320;
	double ratio = (double)vars.window_width / (double)vars.window_height;

	//t_camera camera = create_camera(create_vec(-2,2,1), create_vec(0,0,-1), create_vec(0, 1, 0), 70, ratio);
	//t_camera camera = create_camera(create_vec(0,1,1), create_vec(0,0,-1), create_vec(0, 1, 0), 90, ratio);
	//t_camera camera = create_camera(create_vec(278,278,-800), create_vec(278,278,0), create_vec(0, 1, 0), 40, ratio);
	t_camera camera = create_camera(create_vec(26,3,6), create_vec(0,2,0), create_vec(0, 1, 0), 20, ratio);

	vars.camera = camera;
	ft_mlx_init(&vars);
	print_init(vars);
	//test(&vars);
	mlx_hook(vars.win, 2, 0, &keybind, &vars);
	mlx_hook(vars.win, 3, 0, &keyrelease, &vars);
	//mlx_hook(vars.win,)
	mlx_loop_hook(vars.mlx, &key_hook_move, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
