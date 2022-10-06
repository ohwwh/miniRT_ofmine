#include "sphere.h"

double hit_sphere(t_sphere* s, t_ray* r, t_record* rec)
{
	t_vec oc = create_vec(r->org.x - s->center.x
	,r->org.y - s->center.y
	,r->org.z - s->center.z);
	double sqrtd;
	double root;
	double a = vdot((r->dir), (r->dir));
	double b = vdot(oc,  (r->dir));
	double c = vdot(oc, oc) - s->rad * s->rad;
	double discriminant = b * b - a * c;
	if (discriminant < 0)
			return (-1.0);
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / a;
	if (root < rec->t_min || rec->t_max < root)
34  {
35      root = (-b + sqrtd) / a;
36      if (root < rec->t_min || rec->t_max < root)
37          return (0);
38  }
	return (1);
}

t_sphere create_sphere(t_point c, double r)
{
	t_sphere ret;
	ret.center = c;
	ret.rad = r;
	return (ret);
}

