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
#define MAX_DEPTH 50

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

/*t_color ray_color(t_ray r, void* world[], t_record *rec, int depth)
{
	double t;
	t_vec n;
	int i = 0;

	if (depth <= 0)
        return (create_vec(0,0,0));
	while (i < 2)
	{
		if (hit_sphere((t_sphere *)world[i], &r, rec))
		{
			t_vec target = vec_sum(vec_sum(rec->p, rec->normal), rand_sphere());
			return vec_scalar_mul(ray_color(ray(rec->p, vec_sub(target, rec->p)), world, rec, depth - 1), 0.5);
		}
		i ++;
	}
	while (i < 2)
	{
		hit_sphere((t_sphere *)world[i], &r, rec);
		i ++;
	}
	if (rec->t > 0)
	{
		t_vec target = vec_sum(vec_sum(rec->p, rec->normal), rand_sphere());
		return vec_scalar_mul(ray_color(ray(rec->p, vec_sub(target, rec->p)), world, rec, depth - 1), 0.5);
	}
	t = 0.5 * (unit_vec((r.dir)).y + 1.0);
	return (create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)));
}*/

/*t_color ray_color(t_ray r, void* world[], int depth)
{
	double t;
	t_vec n;
	int i = 0;
	t_record rec;
	rec.t = 0.0;
	rec.t_min = 0.001;
	rec.t_max = INFINITY;
	double bias = 1e-6;

	if (depth <= 0)
        return (create_vec(0,0,0));
	while (i < 2)
	{
		if (hit_sphere((t_sphere *)world[i], &r, &rec))
		{
			t_vec target = vec_sum(vec_sum(rec.p, vec_scalar_mul(rec.normal, bias)), rand_sphere());
			return vec_scalar_mul(ray_color(ray(rec.p, vec_sub(target, rec.p)), world, depth - 1), 0.5);
		}
		i ++;
	}
	while (i < 2)
	{
		hit_sphere((t_sphere *)world[i], &r, &rec);
		i ++;
	}
	if (rec.t > 0)
	{
		t_vec target = vec_sum(vec_sum(rec.p, vec_scalar_mul(rec.normal, bias)), rand_sphere());
		return vec_scalar_mul(ray_color(ray(rec.p, vec_sub(target, rec.p)), world,depth - 1), 0.5);
	}
	t = 0.5 * (unit_vec((r.dir)).y + 1.0);
	return (create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)));
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
	while (i < 2)
	{
		if (hit_sphere((t_sphere *)world[i], &r, &rec))
		{
			t_vec target = vec_sum(vec_sum(rec.p, rec.normal), rand_sphere());
			return vec_scalar_mul(ray_color(ray(rec.p, vec_sub(target, rec.p)), world, depth - 1), 0.5);
		}
		i ++;
	}
	/*while (i < 2)
	{
		hit_sphere((t_sphere *)world[i], &r, &rec);
		i ++;
	}
	if (rec.t > 0)
	{
		t_vec target = vec_sum(vec_sum(rec.p, rec.normal), rand_sphere());
		return vec_scalar_mul(ray_color(ray(rec.p, vec_sub(target, rec.p)), world,depth - 1), 0.5);
	}*/
	t = 0.5 * (unit_vec((r.dir)).y + 1.0);
	return (create_vec((1.0 - t) + (0.5 * t), (1.0 - t) + (0.7 * t), (1.0 - t) + (1.0 * t)));
}

int	main(int argc, char *argv[])
{
	t_sphere sphere = create_sphere(create_vec(0,0,-1), 0.5);
	t_sphere surface = create_sphere(create_vec(0, -1000, 0), 990);
	void *world[10];
	world[9] = 0;
	world[0] = (void *)(&sphere);
	world[1] = (void *)(&surface);
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
			/*t_record rec;
			rec.t = 0.0;
			rec.t_min = 0;
			rec.t_max = INFINITY;*/
			if (i == 320 && j == 200)
				printf("break\n");
			ft_pixel_put(&vars, i, window_height - 1 - j, rgb_to_int(ray_color(ray_tmp, world, MAX_DEPTH)));
		}
	}
	mlx_loop(vars.mlx);
	return (0);
}
