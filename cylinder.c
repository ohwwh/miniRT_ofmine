#include "cylinder.h"
# define EPS 0.0001

/*int hit_caps(t_record rec, t_ray *ray, t_cylinder *cy)
{
	t_cylinder top_cap;
	t_record hr;

	top_cap.cen.x = cy->dir.x;
	top_cap.cen.y = cy->dir.y;
	top_cap.cen.z = cy->dir.z;

	top_cap.cen = unit_vec(top_cap.cen);

	top_cap.cen.x = cy->p.y * top_cap.cen.x + cy->cen.x;
	top_cap.cen.y = cy->p.y * top_cap.cen.y + cy->cen.y;
	top_cap.cen.z = cy->p.y * top_cap.cen.z + cy->cen.z;
	
	top_cap.dir.x = cy->dir.x;
	top_cap.dir.y = cy->dir.y;
	top_cap.dir.z = cy->dir.z;

	top_cap.color.x = cy->color.x;
	top_cap.color.y = cy->color.y;
	top_cap.color.z = cy->color.z;

	hr = hit_plane(rec, ray, &top_cap);
	if (powf(hr.p.x - top_cap.cen.x, 2.) + powf(hr.p.y - top_cap.cen.y, 2.) + powf(hr.p.z - top_cap.cen.z, 2.) <= powf(cy->p.x / 2, 2.))
		rec = hr;
	hr = hit_plane(rec, ray, cy);
	if (powf(hr.p.x - cy->cen.x, 2.) + powf(hr.p.y - cy->cen.y, 2.) + powf(hr.p.z - cy->cen.z, 2.) <= powf(cy->p.x / 2, 2.))
		rec = hr;
	return (rec);
}*/

int hit_cylinder(t_cylinder *cy, int i, t_ray *ray, t_record *rec)
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
	oc = vec_sub(ray->org, cy->center);
	a = vdot(ray->dir, ray->dir) - (vdot(ray->dir, normalized)
			* vdot(ray->dir, normalized));
	b = 2 * (vdot(ray->dir, oc) - (vdot(ray->dir, normalized)
				* vdot(oc, normalized)));
	c = vdot(oc, oc)
		- (vdot(oc, normalized) * vdot(oc, normalized))
		- (cy->p.x / 2) * (cy->p.x / 2);
	D = b * b - 4 * a * c;
	if (D < EPS)
		return (0);
	else
    {
        t1 = (-b + sqrt(D)) / (2 * a);
	    t2 = (-b - sqrt(D)) / (2 * a);
	    if (t1 < EPS)
		    return (0);
		else
		{
	    	h1 = vdot(ray->dir, normalized) * t1 + vdot(oc, normalized);
	    	h2 = vdot(ray->dir, normalized) * t2 + vdot(oc, normalized);
	    	if (h2 >= EPS && h2 <= cy->p.y)
		    	hr.t = t2;
	    	else if (h1 >= EPS && h1 <= cy->p.y)
		    	hr.t = t1;
	    	else
            	return (0);
		}
    }
	root = t1;
	if (root < rec->t_min || rec->t_max < root)
	{
		root = t2;
		if (root < rec->t_min || rec->t_max < root)
			return (0);
	}
	rec->t = root;
	rec->p = ray_end(ray, root);
	rec->t_max = root;
	rec->normal = vec_division(vec_sub(rec->p, cy->center), cy->p.x);
	rec->idx = i;
	rec->mat = cy->mat;

	if (((rec.t > hr.t || rec.t == -1) && hr.t > EPS))
	{
		hr.color = cy->color;
		hr.p = vec_sum(ray->origin, vec_scalar_mul(ray->dir, hr.t));
		oc = unit_vec(cy->dir);
		m = vdot(ray->dir, vec_scalar_mul(oc, hr.t))
			+ vdot(vec_sub(ray->origin, cy->cen), oc);
		hr.normal = unit_vec(vec_sub(vec_sub(hr.p, cy->cen),
					vec_scalar_mul(oc, m)));
		rec = hr;
	}
    return (rec);
}