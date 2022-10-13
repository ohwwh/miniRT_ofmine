#include "objects.h"

t_object create_sphere(t_point c, double r, t_color color, int mat)
{
	t_object ret;

    ret.type = 3;
	ret.center = c;
	ret.radius = r;
	ret.color = color;
	ret.mat = mat;
	return (ret);
}

t_object create_cylinder(t_point c, double r, double h, t_vec dir, t_color color, int mat)
{
	t_object ret;

	ret.type = 2;
	ret.center = c;
	ret.radius = r;
	ret.height = h;
	ret.dir = dir;
	ret.color = color;
	ret.mat = mat;
	return (ret);
}

t_object create_plane(t_point c, t_vec dir, t_color color, int mat)
{
	t_object ret;

	ret.type = 1;
	ret.center = c;
	ret.dir = dir;
	ret.color = color;
	ret.mat = mat;
	return (ret);
}