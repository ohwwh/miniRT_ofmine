#include "sphere.h"

int front_face(t_ray *r, t_record* rec)
{
	if (vdot(r->dir, rec->normal) > 0.0)
	{
		rec->normal = vec_scalar_mul(rec->normal, -1);
		return (0);
	}
	return (1);
}

int hit_sphere(t_sphere* s, t_ray* r, t_record* rec)
{
	t_vec oc = create_vec(r->org.x - s->center.x
	,r->org.y - s->center.y
	,r->org.z - s->center.z);
	double sqrtd;
	double root;
	double a = vdot((r->dir), (r->dir));
	double b = vdot(oc, (r->dir));
	double c = vdot(oc, oc) - s->rad * s->rad;
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
	rec->normal = vec_division(vec_sub(rec->p, s->center), s->rad);
	front_face(r, rec);
	//rec->normal = unit_vec(vec_sub(rec->p, s->center));
	return (1);
}

t_sphere create_sphere(t_point c, double r)
{
	t_sphere ret;
	ret.center = c;
	ret.rad = r;
	return (ret);
}

