#include "minirt.h"

int hit_aabb(t_aabb *aabb, t_ray *ray, t_hit_record* rec)
{
	double	t0;
	double	t1;
	double	mn;
	double	mx;

	mn = (aabb->minimum.x - ray->origin.x) / ray->dir.x;
	mx = (aabb->maximum.x - ray->origin.x) / ray->dir.x;
	t0 = fmin(mn, mx);
	t1 = fmax(mn, mx);
	rec->tmin = t0;
	rec->tmax = t1;
	if (rec->tmax <= rec->tmin)
		return (0);
	
	mn = (aabb->minimum.y - ray->origin.y) / ray->dir.y;
	mx = (aabb->maximum.y - ray->origin.y) / ray->dir.y;
	t0 = fmin(mn, mx);
	t1 = fmax(mn, mx);
	rec->tmin = fmax(t0, rec->tmin);
	rec->tmax = fmin(t1, rec->tmax);
	if (rec->tmax <= rec->tmin)
		return (0);
	
	mn = (aabb->minimum.z - ray->origin.z) / ray->dir.z;
	mx = (aabb->maximum.z - ray->origin.z) / ray->dir.z;
	t0 = fmin(mn, mx);
	t1 = fmax(mn, mx);
	rec->tmin = fmax(t0, rec->tmin);
	rec->tmax = fmin(t1, rec->tmax);
	if (rec->tmax <= rec->tmin)
		return (0);

	return (1);
}