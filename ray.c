#include "ray.h"

t_ray ray(t_point org, t_vec dir)
{
	t_ray ret;
	ret.org = org;
	ret.dir = dir;
	return (ret);
}

t_point ray_end(t_ray* ray, double t)
{
	t_point ret;
	
	ret.x = ray->org.x + t * ray->dir.x;
	ret.y = ray->org.y + t * ray->dir.y;
	ret.z = ray->org.z + t * ray->dir.z;
	return (ret);
}