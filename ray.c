#include "ray.h"
#define EPS 0.0001
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


int front_face(t_ray *r, t_record* rec)
{
	if (vdot(r->dir, rec->normal) > 0.0)
	{
		rec->normal = vec_scalar_mul(rec->normal, -1);
		return (0);
	}
	return (1);
}

int find_hitpoint(t_ray* ray, t_object *objs, t_record* rec)
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
        else if (tmp->type == 1)
        {
           //hit_plane(saved, ray, tmp);
        }
        else if (tmp->type == 2)
        {
            hit_cylinder(tmp, ray, rec);
	        //saved = hit_caps(saved, ray, tmp);
        }
        tmp = tmp->next;
    }
    return (1);
}

int hit_sphere(t_object* s, t_ray* r, t_record* rec)
{
	t_vec oc = create_vec(r->origin.x - s->center.x
	,r->origin.y - s->center.y
	,r->origin.z - s->center.z);
	double sqrtd;
	double root;
	double a = vdot((r->dir), (r->dir));
	double b = vdot(oc, (r->dir));
	double c = vdot(oc, oc) - s->radius * s->radius;
	double discriminant = b * b - a * c;
	if (discriminant < 0)
			return (0);
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / a;
	if (root < rec->t_min || rec->t_max < root)
	{
		root = (-b + sqrtd) / a;
		if (root < rec->t_min || rec->t_max < root)
			return (0);
	}
	rec->t = root;
	rec->p = ray_end(r, root);
	rec->t_max = root;
	rec->normal = vec_division(vec_sub(rec->p, s->center), s->radius);
	rec->color = s->color;
	rec->mat = s->mat;
	front_face(r, rec);
	return (1);
}

int hit_cylinder(t_object *cy, t_ray *ray, t_record *rec)
{   
    t_record hr;
	double	m;
	t_vec	oc;
    double  D; // 판별식
    t_vec   normalized;
    double  a;
    double  b;
    double  c;
    double  t1;
    double  t2;
    double  h1, h2;
	double root;

	// hr.t 구하기 //
    normalized = unit_vec(cy->dir);
	oc = vec_sub(ray->origin, cy->center);
	a = vdot(ray->dir, ray->dir) - (vdot(ray->dir, normalized)
			* vdot(ray->dir, normalized));
	b = 2 * (vdot(ray->dir, oc) - (vdot(ray->dir, normalized)
				* vdot(oc, normalized)));
	c = vdot(oc, oc)
		- (vdot(oc, normalized) * vdot(oc, normalized))
		- (cy->radius) * (cy->radius);
	D = b * b - 4 * a * c;
	/*if (D < EPS)
		return (0);*/
	if (1)
    {
        t1 = (-b + sqrt(D)) / (2 * a);
	    t2 = (-b - sqrt(D)) / (2 * a);
		/*if (t1 < EPS)
			return (0);*/
		if (1)
		{
	    	h1 = vdot(ray->dir, normalized) * t1 + vdot(oc, normalized);
	    	h2 = vdot(ray->dir, normalized) * t2 + vdot(oc, normalized);
			if (h2 <= cy->height)
				hr.t = t2;
			else if (h1 <= cy->height)
				hr.t = t1;
			else
				return (0);
		}
    }
	root = t2;
	if (root < rec->t_min || rec->t_max < root)
	{
		root = t1;
		if (root < rec->t_min || rec->t_max < root)
			return (0);
	}
	rec->t = root;
	rec->t_max = root;
	rec->mat = cy->mat;
	if (1)
	{
		rec->color = cy->color;
		rec->p = vec_sum(ray->origin, vec_scalar_mul(ray->dir, rec->t));
		oc = unit_vec(cy->dir);
		m = vdot(ray->dir, vec_scalar_mul(oc, root))
			+ vdot(vec_sub(ray->origin, cy->center), oc);
		rec->normal = unit_vec(vec_sub(vec_sub(rec->p, cy->center),
			vec_scalar_mul(oc, m)));
	}
    return (1);
}