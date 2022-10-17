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

void print_init(t_minirt vars)
{
	double u;
	double v;
	t_vec dir;
	t_ray ray_tmp;
	t_color color;
	int k = 0;
	for (int j = vars.mlx.window_height - 1; j >= 0; --j)
	{
		if (vars.is_trace == 1)
		{
			printf("\rScanlines remaining: %d", j);
			fflush(stdout);
		}
		for (int i = 0; i < vars.mlx.window_width; ++i)
		{
			//기본 색상을 어떻게 지정할까? 원하는 색의 rgb값 / 256 * anti 
			//물체마다 따로 지정하려면 어떻C게 하나?
			//t_color color = create_vec(0, 0, 0);
			color = create_vec(0, 0, 0);
			for (int s = 0; s < vars.anti; s ++)
			{
				u = ((double)i + random_double(-1,1,vars.anti)) / (vars.mlx.window_width-1);
				v = ((double)j + random_double(-1,1,vars.anti)) / (vars.mlx.window_height-1);
				dir = create_vec(vars.scene.camera.lower_left_corner.x + (u * vars.scene.camera.horizontal.x) + (v * vars.scene.camera.vertical.x) - vars.scene.camera.origin.x,
				vars.scene.camera.lower_left_corner.y + (u * vars.scene.camera.horizontal.y) + (v * vars.scene.camera.vertical.y) - vars.scene.camera.origin.y,
				vars.scene.camera.lower_left_corner.z + (u * vars.scene.camera.horizontal.z) + (v * vars.scene.camera.vertical.z) - vars.scene.camera.origin.z);
				ray_tmp = ray(vars.scene.camera.origin, dir);
				if (i == 286 && j == 210)
					i = i;
				if (vars.is_trace == 1)
					color = vec_sum(color, ray_color(ray_tmp, vars.scene.world, vars.scene.light, MAX_DEPTH));
					//여러 개의 광원이 있을 때는?
					//광원을 어떻게 구분해서 인자로 넣을 건지?
				else
					color = vec_sum(color, ray_color_2(ray_tmp, vars.scene.world, vars.scene.light));
			}
			color = vec_division(color, vars.anti);
			ft_pixel_put(&vars, i, vars.mlx.window_height - 1 - j, rgb_to_int(color));
		}
	}
}

int	main(int argc, char *argv[])
{
	/*t_object light = create_sphere(create_vec(5,8, -1), 2, 
	create_vec(15, 15, 15), -1);

	t_object surface = create_sphere(create_vec(0, -100.5, -1), 100, 
	//create_vec(1, 0.75, 0.8));
	create_vec(0.8, 0.8, 0), 0);
	light.next = &surface;

	t_object sphere = create_sphere(create_vec(0,0,-2), 0.5, 
	create_vec(0.7, 0.3, 0.3), 1);
	surface.next = &sphere;

	t_object metal = create_sphere(create_vec(1,0, -1), 0.5, 
	create_vec(0.8, 0.8, 0.8), 1);
	sphere.next = &metal;
	metal.next = 0;

	t_object cylinder = create_cylinder(create_vec(0,0,-5), 0.5, 1, 
	create_vec(0,0,-1), create_vec(0.3,0.3,0.7), 1);
	sphere.next = &cylinder;
	cylinder.next = 0;*/
	
	


	/*t_object light = create_sphere(create_vec(200,480,200), 80, 
	create_vec(15, 15, 15), -1);
	t_object green = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.12, 0.45, 0.15), 0);
	t_object red = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.65, 0.05, 0.05), 0);
	t_object white1 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0); //윗면
	t_object white2 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.73, 0.73, 0.73), 0); //아랫면
	t_object white3 = create_rectangle_xy(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0); //뒷면
	t_object sphere = create_sphere(create_vec(270,330,190), 80, 
	create_vec(0.8, 0.8, 0.8), 2);
	set_refraction(&sphere, 1.5);

	light.next = &green;
	green.next = &red;
	red.next = &white1;
	white1.next = &white2;
	white2.next = &white3;
	white3.next = &sphere;
	sphere.next = 0;*/




	/*t_object light = create_rectangle_xz(create_vec(213,343,0), create_vec(227,332,0), 554, 
	create_vec(15, 15, 15), -1);
	t_object green = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.12, 0.45, 0.15), 0);
	t_object red = create_rectangle_yz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.65, 0.05, 0.05), 0);
	t_object white1 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0); //윗면
	t_object white2 = create_rectangle_xz(create_vec(0,555,0), create_vec(0,555,0), 0, 
	create_vec(0.73, 0.73, 0.73), 0); //아랫면
	t_object white3 = create_rectangle_xy(create_vec(0,555,0), create_vec(0,555,0), 555, 
	create_vec(0.73, 0.73, 0.73), 0); //뒷면
	t_object sphere = create_sphere(create_vec(190,90,190), -90, 
	create_vec(0.2, 0.4, 0.9), 0);
	set_refraction(&sphere, 0.5);

	light.next = &green;
	green.next = &red;
	red.next = &white1;
	white1.next = &white2;
	white2.next = &white3;
	white3.next = &sphere;
	sphere.next = 0;*/

	
	//t_object light = create_rectangle_xz(create_vec(4,8,0), create_vec(0,4,0), 
	//8, create_vec(15, 15, 15), -1);
	
	//t_object light = create_rectangle_xy(create_vec(3,5,0), create_vec(1,3,0), 
	//-5, create_vec(15, 15, 15), -1);

	t_object light = create_sphere(create_vec(2, 14, -10), 4, 
	create_vec(15, 15, 15), -1);
	//light.next = &light2;
	//light.next = 0;

	t_object surface = create_sphere(create_vec(0, -1000, 0), 1000, 
	create_vec(0.4, 0.4, 0.4), 0);
	light.next = &surface;

	t_object sphere = create_sphere(create_vec(4,2,-2), 2, 
	create_vec(0.8, 0.8, 0.8), 2);
	set_refraction(&sphere, 1.5);
	surface.next = &sphere;
	t_object sphere2 = create_sphere(create_vec(-4,2,2), 2, 
	create_vec(0.7, 0.3, 0.3), 1);
	sphere.next = &sphere2;
	t_object wall = create_plane(create_vec(0, 150, 0), 
	vec_sub(create_vec(0,5,0), create_vec(26,3,6)), create_vec(0.8, 0.8, 0.8), 0);
	sphere2.next = &wall;
	t_object cylinder = create_cylinder(create_vec(1.5,0, -6), 1, 4, 
	create_vec(0,1,0), create_vec(0.3,0.3,0.7), 0);
	wall.next = &cylinder;
	cylinder.next = 0;


	t_minirt	vars;
	init_rt(&vars);
	//init_rt를 한번 하고 나니까 없애도 흰색 화면이 뜲.
	vars.is_trace = 0;
	vars.anti = 1;
	vars.is_move = -1;
	vars.changed = 0;
	vars.scene.world = &light;
	vars.scene.light = &light;
	vars.mlx.window_width = 640;
	vars.mlx.window_height = 320;
	double ratio = (double)vars.mlx.window_width / (double)vars.mlx.window_height;

	//t_camera camera = create_camera(create_vec(-2,2,1), create_vec(0,0,-1), create_vec(0, 1, 0), 70, ratio);
	//t_camera camera = create_camera(create_vec(0,1,1), create_vec(0,0,-1), create_vec(0, 1, 0), 70, ratio);
	//t_camera camera = create_camera(create_vec(278,278,-800), create_vec(278,278,0), create_vec(0, 1, 0), 40, ratio);
	t_camera camera = create_camera(create_vec(26,8,6), create_vec(0,2,0), create_vec(0, 1, 0), 20, ratio);

	//srand(time(0));
	vars.scene.camera = camera;
	//ft_mlx_init(&vars);
	print_init(vars);
	mlx_hook(vars.mlx.mlx_win, 2, 0, &keybind, &vars);
	mlx_hook(vars.mlx.mlx_win, 3, 0, &keyrelease, &vars);
	mlx_hook(vars.mlx.mlx_win, 4, 0, &scroll, &vars);
	//mlx_hook(vars.win,)
	mlx_loop_hook(vars.mlx.mlx, &key_hook_move, &vars);
	mlx_loop(vars.mlx.mlx);
	return (0);
}
