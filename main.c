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

int get_color_from_ray_tmp(t_ray* ray)
{
	const double t = 0.5 * (unit(&(ray->dir)).y + 1.0);
	const double r = (1.0 - t) + (0.5 * t);
	const double g = (1.0 - t) + (0.7 * t);
	const double b = (1.0 - t) + (1.0 * t);
	return (rgb_to_int(0, r, g, b));
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	//double ratio = 16.0 / 10.0;
	int window_width = 640;
	int window_height = 400;
	double ratio = (double)640 / (double)400;

	double viewport_height = 2.0;
	double viewport_width = ratio * viewport_height;
	double focal_length = 1.0;

	point3 origin = vector(0, 0, 0);
	t_vec horizontal = vector(viewport_width, 0, 0);
	t_vec vertical = vector(0, viewport_height, 0);
	t_vec lower_left_corner = vector(origin.x + (- horizontal.x / 2) + (-vertical.x / 2) + (0)
		,origin.y + (- horizontal.y / 2) + (-vertical.y / 2) + (0) 
		,origin.z + (- horizontal.z / 2) + (-vertical.z / 2) + (-focal_length));
	
	printf("%lf, %lf, %lf\n", lower_left_corner.x, lower_left_corner.y, lower_left_corner.z);
	
	ft_mlx_init(&vars);
	double u;
	double v;
	t_vec dir;
	t_ray ray_tmp;
	for (int j = window_height - 1; j >= 0; --j)
	{
		for (int i = 0; i < window_width; ++i)
		{
			u = ((double)i) / (window_width-1);
			v = ((double)j) / (window_height-1);
			dir = vector(lower_left_corner.x + (u * horizontal.x) + (v * vertical.x) - origin.x,
			lower_left_corner.y + (u * horizontal.y) + (v * vertical.y) - origin.y,
			lower_left_corner.z + (u * horizontal.z) + (v * vertical.z) - origin.z);
			ray_tmp = ray(origin, dir);
			ft_pixel_put(&vars, i, j, get_color_from_ray_tmp(&ray_tmp));
			//ft_pixel_put(&vars, i, j, rgb_to_int(0, 0.5, 0.7, 1.0));
		}
	}
	mlx_loop(vars.mlx);
	return (0);
}
