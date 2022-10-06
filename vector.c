#include "vector.h"

t_vec vector(const double x, const double y, const double z)
{
	t_vec ret;
	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec unit(const t_vec* v)
{
	const double l = length(v);
	t_vec ret;
	ret.x = v->x / l;
	ret.y = v->y / l;
	ret.z = v->z / l;
	return (ret);
}

t_vec plus(const t_vec* v1, const t_vec* v2)
{
	t_vec ret;
	ret.x = v1->x + v2->x;
	ret.y = v1->y + v2->y;
	ret.z = v1->z + v2->z;
	return (ret);
}

t_vec minus(const t_vec* v1, const t_vec* v2)
{
	t_vec ret;
	ret.x = v1->x - v2->x;
	ret.y = v1->y - v2->y;
	ret.z = v1->z - v2->z;
	return (ret);
}

t_vec multiply(t_vec* v1, double t)
{
	t_vec ret;
	ret.x = v1->x * t;
	ret.y = v1->y * t;
	ret.z = v1->z * t;
	return (ret);
}

double length(const t_vec* v)
{
	return (sqrt((v->x) * (v->x) + (v->y) * (v->y) + (v->z) * (v->z)));
}

double dot(const t_vec* v1, const t_vec* v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

t_vec cross(const t_vec* v1, const t_vec* v2)
{
	t_vec ret;

	ret.x = v1->y * v2->z + v1->z * v2->y;
	ret.y = v1->z * v2->x + v1->x * v2->z;
	ret.z = v1->x * v2->y + v1->y * v2->x;
	return (ret);
}
