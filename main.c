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
#include "libohw/includes/libft.h"

t_vec rand_sphere()
{
	t_vec ret;

	while (1)
	{
		ret = create_vec(random_double(),random_double(),random_double());
		if (vec_len(ret) >= 1.0)
			continue ;
		return (ret);
	}
}

t_color ray_color(t_ray* ray, void* world[], t_record *rec)
{
	double t;
	t_vec n;
	int i = 0;

	while (i < 2)
	{
		t = hit_sphere((t_sphere *)world[0], ray);
		if (t > 0.0) //object 구조체를 인자로 받는 hit_object 함수로 wrapping 할 것
		{
			if (i == 0)
			{
				n = unit_vec(vec_sub(ray_end(ray, t), ((t_sphere *)world[i])->center));
				printf("%lf\n", n.x);
				return (vec_scalar_mul(create_vec(n.x + 1, n.y + 1, n.z + 1), 0.5));
			}
			else
			{
				return (create_vec(0.5, 0.75, 0.27));
			}
		}
		i ++;
	}
	t = 0.5 * (unit_vec((ray->dir)).y + 1.0);
	return (create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)));
	/*if (t > 0.0) //object 구조체를 인자로 받는 hit_object 함수로 wrapping 할 것
	{
		n = unit_vec(vec_sub(ray_end(ray, t), center));
		return (vec_scalar_mul(create_vec(n.x + 1, n.y + 1, n.z + 1), 0.5));
	}
	t = hit_sphere(&center, 990, ray);
	if (t > 0.0) //object 구조체를 인자로 받는 hit_object 함수로 wrapping 할 것
		return (create_vec(0.5, 0.75, 0.27));
	t = 0.5 * (unit_vec((ray->dir)).y + 1.0);
	return (create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)));*/
}

int	main(int argc, char *argv[])
{
	t_sphere sphere = create_sphere(create_vec(0,0,-1), 0.5);
	t_sphere surface = create_sphere(create_vec(0, -1000, 0), 990);
	void *world[10];
	world[9] = (void *)(&sphere);
	world[0] = (void *)(&surface);
	t_vars	vars;
	//double ratio = 16.0 / 10.0;
	int window_width = 640;
	int window_height = 400;
	double ratio = (double)640 / (double)400;

	double viewport_height = 2.0;
	double viewport_width = ratio * viewport_height;
	double focal_length = 1.0;

	t_point origin = create_vec(0, 0, 0);
	t_vec horizontal = create_vec(viewport_width, 0, 0);
	t_vec vertical = create_vec(0, viewport_height, 0);
	t_vec lower_left_corner = create_vec(origin.x + (- horizontal.x / 2) + (-vertical.x / 2) + (0)
		,origin.y + (- horizontal.y / 2) + (-vertical.y / 2) + (0) 
		,origin.z + (- horizontal.z / 2) + (-vertical.z / 2) + (-focal_length));
	//(orgin) - (horizontal / 2) - (vertical / 2) - vector(0,0,focal_length)
	
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
			dir = create_vec(lower_left_corner.x + (u * horizontal.x) + (v * vertical.x) - origin.x,
			lower_left_corner.y + (u * horizontal.y) + (v * vertical.y) - origin.y,
			lower_left_corner.z + (u * horizontal.z) + (v * vertical.z) - origin.z);
			ray_tmp = ray(origin, dir);
			t_record rec;
			rec.t_min = 0;
			rec.t_max = INFINITY;
			ft_pixel_put(&vars, i, window_height - 1 - j, rgb_to_int(ray_color(&ray_tmp, world, &rec)));
		}
	}
	mlx_loop(vars.mlx);
	return (0);
}
