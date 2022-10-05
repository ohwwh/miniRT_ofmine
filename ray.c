#include "ray.h"

t_ray ray(point3 org, t_vec dir)
{
	t_ray ret;
	ret.org = org;
	ret.dir = dir;
	return (ret);
}

point3 ray_end(t_ray* ray, double t)
{
	point3 ret;
	
	ret.x = ray->org.x + t * ray->dir.x;
	ret.y = ray->org.y + t * ray->dir.y;
	ret.z = ray->org.z + t * ray->dir.z;
	return (ret);
}