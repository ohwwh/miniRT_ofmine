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
#define MAX_DEPTH 50

t_ray       ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;

    ray.origin = cam->origin;
    ray.dir = vec_sum(vec_sum(vec_scalar_mul(cam->up, v * cam->viewport_height),
				vec_scalar_mul(cam->right, u *  cam->viewport_width)), cam->forward);
    ray.dir = unit_vec(ray.dir);
    return (ray);
}

void	init_rt(t_minirt *vars)
{
	vars->mlx.mlx = mlx_init();
	vars->mlx.mlx_win = mlx_new_window(vars->mlx.mlx, WIDTH, HEIGHT, "miniRT");
	vars->mlx.img = mlx_new_image(vars->mlx.mlx, WIDTH, HEIGHT);
	vars->mlx.addr = mlx_get_data_addr(vars->mlx.img, &vars->mlx.bits_per_pixel, \
	&vars->mlx.line_length, &vars->mlx.endian);
	vars->scene.world = NULL;
	vars->scene.ambient.count = 0;
	vars->scene.camera.count = 0;
	vars->scene.light = NULL;
	//생성 실패 시 에러처리 해야 함
}

void path_render(t_minirt vars)
{
	double u;
	double v;
	t_vec dir;
	t_ray init_ray;
	t_color color;
	
	for (int y = HEIGHT - 1; y >= 0; --y)
	{
		if (vars.is_trace == 1)
		{
			printf("\rScanlines remaining: %d", y);
			fflush(stdout);
		}
		for (int x = 0; x < WIDTH; ++x)
		{
			color = create_vec(0, 0, 0);
			for (int s = 0; s < vars.scene.anti; s ++)
			{
				u = (((double)x + random_double(0, 1, vars.scene.anti)) * 2 / WIDTH) - 1;
				v = (((double)y + random_double(0, 1, vars.scene.anti)) * 2 / HEIGHT) - 1;
				init_ray = ray_primary(&(vars.scene.camera), u, v);
				if (x == 0 && y == 0)
						x = x;
				if (vars.is_trace == 1)
					color = vec_sum(color, ray_color(init_ray, vars.scene.world, vars.scene.light, MAX_DEPTH));
					//여러 개의 광원이 있을 때는?
					//광원을 어떻게 구분해서 인자로 넣을 건지?
				else
					color = vec_sum(color, ray_color_2(init_ray, vars.scene.world, vars.scene.light));
			}
			color = vec_division(color, vars.scene.anti);
			put_color(&vars.mlx, x, HEIGHT - 1 - y, rgb_to_int(color));
			//put_color(&vars.mlx, x, HEIGHT - 1 - y, convert_rgb(color.x, color.y, color.z));
		}
	}
	mlx_put_image_to_window(vars.mlx.mlx, vars.mlx.mlx_win, vars.mlx.img, 0, 0); // 무슨 차이지....
}

int	main(int argc, char *argv[])
{
	t_objs light1 = create_sphere(create_vec(5,8, -1), 3, 
	create_vec(15, 15, 15), -1);

	t_objs surface = create_sphere(create_vec(0, -100.5, -1), 100, 
	//create_vec(1, 1, 1), 0);
	create_vec(0.8, 0.8, 0), 0);
	set_specular(&surface, 0);

	t_objs sphere = create_sphere(create_vec(0,0,-2), 0.5, 
	create_vec(0.7, 0.3, 0.3), 0);
	surface.next = &sphere;
	set_specular(&sphere, 0);

	t_objs metal = create_sphere(create_vec(1,0, -1), 0.5, 
	create_vec(0.8, 0.8, 0.8), 1);
	sphere.next = &metal;
	metal.next = 0;

	t_objs cylinder = create_cylinder(create_vec(0,0,-5), 0.5, 1, 
	create_vec(0,0,-1), create_vec(0.3,0.3,0.7), 1);
	sphere.next = &cylinder;
	cylinder.next = 0;

	t_light light;
	light.object = &light1;
	light.next = 0;
	light.count = 1;
	//light.count = 0 일 때 segfault??
	
	


	/*t_objs light = create_sphere(create_vec(200,480,200), 80, 
	create_vec(15, 15, 15), -1);
	t_objs green = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.12, 0.45, 0.15), 0);
	t_objs red = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.65, 0.05, 0.05), 0);
	t_objs white1 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0); //윗면
	t_objs white2 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.73, 0.73, 0.73), 0); //아랫면
	t_objs white3 = create_rectangle_xy(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0); //뒷면
	t_objs sphere = create_sphere(create_vec(270,330,190), 80, 
	create_vec(0.8, 0.8, 0.8), 2);
	set_refraction(&sphere, 1.5);

	light.next = &green;
	green.next = &red;
	red.next = &white1;
	white1.next = &white2;
	white2.next = &white3;
	white3.next = &sphere;
	sphere.next = 0;*/




	t_objs light1 = create_rectangle_xz(create_vec(213,343,0), create_vec(227,332,0), 554, 
	create_vec(15, 15, 15), -1);
	t_objs green = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.12, 0.45, 0.15), 0);
	t_objs red = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.65, 0.05, 0.05), 0);
	t_objs white1 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0); //윗면
	t_objs white2 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.73, 0.73, 0.73), 0); //아랫면
	t_objs white3 = create_rectangle_xy(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0); //뒷면
	t_objs sphere = create_sphere(create_vec(190,90,360), 90, 
	create_vec(0.8, 0.8, 0.9), 0);
	set_specular(&sphere, 0);
	t_objs sphere2 = create_sphere(create_vec(190,270,360), 90, 
	create_vec(0.8, 0.8, 0.8), 0);
	set_specular(&sphere2, 0.5);
	t_objs sphere3 = create_sphere(create_vec(190,450,360), 90, 
	create_vec(0.8, 0.8, 0.8), 0);
	set_specular(&sphere3, 1);

	t_light light;
	light.object = &light1;
	light.next = 0;
	light.count = 1;

	light1.next = &green;
	green.next = &red;
	red.next = &white1;
	white1.next = &white2;
	white2.next = &white3;
	white3.next = &sphere;
	sphere.next = &sphere2;
	sphere2.next = &sphere3;
	sphere3.next = 0;

	
	//t_objs light2 = create_rectangle_xz(create_vec(4,8,0), create_vec(0,4,0), 
	//8, create_vec(15, 15, 15), -1);
	
	//t_objs light = create_rectangle_xy(create_vec(3,5,0), create_vec(1,3,0), 
	//-5, create_vec(15, 15, 15), -1);

	/*t_objs light1 = create_sphere(create_vec(2, 14, -10), 4, 
	create_vec(25, 0, 0), -1);
	t_objs light2 = create_sphere(create_vec(2, 14, 10), 4, 
	create_vec(0, 0, 25), -1);
	//light.next = &light2;
	//light.next = 0;

	t_light light;
	t_light light_next;
	light.object = &light1;
	light_next.object = &light2;
	light.next = &light_next;
	light_next.next = 0;
	light.count = 2;

	t_objs surface = create_sphere(create_vec(0, -1000, 0), 1000, 
	create_vec(0.4, 0.4, 0.4), 0);

	t_objs sphere = create_sphere(create_vec(4,2,-2), 2, 
	create_vec(0.8, 0.8, 0.8), 2);
	set_refraction(&sphere, 1.5);
	surface.next = &sphere;
	t_objs sphere2 = create_sphere(create_vec(-4,2,2), 2, 
	create_vec(0.7, 0.3, 0.3), 1);
	sphere.next = &sphere2;
	t_objs wall = create_plane(create_vec(0, 150, 0), 
	vec_sub(create_vec(0,5,0), create_vec(26,3,6)), create_vec(0.8, 0.8, 0.8), 0);
	sphere2.next = &wall;
	t_objs cylinder = create_cylinder(create_vec(1.5,0, -6), 1, 4, 
	create_vec(0,1,0), create_vec(0.3,0.3,0.7), 0);
	wall.next = &cylinder;
	cylinder.next = 0;*/


	t_minirt	vars;
	init_rt(&vars);
	vars.is_trace = 0;
	vars.scene.anti = 1;
	vars.scene.ambient.col = create_vec(0, 0, 0);
	vars.is_move = -1;
	vars.scene.changed = 0;
	vars.scene.world = &green;
	vars.scene.light = &light;
	double ratio = (double)WIDTH / (double)HEIGHT;

	//t_camera camera = create_camera(create_vec(-2,2,1), create_vec(0,0,-1), create_vec(0, 1, 0), 70, ratio);
	//t_camera camera = create_camera(create_vec(0,0,0), create_vec(0,0,-1), create_vec(0, 1, 0), 70, ratio);
	t_camera camera = create_camera(create_vec(278,278,-800), create_vec(278,278,0), create_vec(0, 1, 0), 40, ratio);
	//t_camera camera = create_camera(create_vec(26,8,6), create_vec(0,2,0), create_vec(0, 1, 0), 20, ratio);
	set_camera(&camera);

	//srand(time(0));
	vars.scene.camera = camera;
	//ft_mlx_init(&vars);
	path_render(vars);
	mlx_hook(vars.mlx.mlx_win, 2, 0, &keypress, &vars);
	mlx_hook(vars.mlx.mlx_win, 3, 0, &keyrelease, &vars);
	mlx_hook(vars.mlx.mlx_win, 4, 0, &scroll, &vars);
	mlx_loop_hook(vars.mlx.mlx, &key_hook_move, &vars);
	mlx_loop(vars.mlx.mlx);
	return (0);
}
