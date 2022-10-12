#include "ray.h"

t_ray ray(t_point origin, t_vec dir)
{
	t_ray ret;
	ret.origin = origin;
	ret.dir = dir;
	return (ret);
}

t_point ray_end(t_ray* ray, double t)
{
	t_point ret;
	
	ret.x = ray->origin.x + t * ray->dir.x;
	ret.y = ray->origin.y + t * ray->dir.y;
	ret.z = ray->origin.z + t * ray->dir.z;
	return (ret);
}

t_vec reflect(t_vec v, t_vec n)
{
	return (vec_sub(v, vec_scalar_mul(n, 2*vdot(v, n))));
}

int find_hitpoint(t_ray *ray, t_object *objs, t_record* rec)
{
    t_object *tmp;
    t_record saved;
    
    tmp = objs;
    saved.t = -1.0;
    while (tmp)
    {
        if (tmp->type == 3)
        {
            hit_sphere(tmp, ray, rec);
        }
        else if (tmp->type == 2)
        {
           //hit_plane(saved, ray, tmp);
        }
        else if (tmp->type == 1)
        {
            //saved = hit_cylinder(saved, ray, tmp);
	        //saved = hit_caps(saved, ray, tmp);
        }
        tmp = tmp->next;
    }
    return (1);
}