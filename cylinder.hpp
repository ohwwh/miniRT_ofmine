#ifndef CYLINDER_H
#define CYLINDER_H
#include "ray.h"

typedef struct s_object {
	int				type;
	t_vec			center;
	t_vec			dir;
	double 			radius;
	double 			height;
	t_vec			color;
	t_vec			norm;
	struct s_objs	*next;
} t_object;

t_cylinder create_cylinder(int type, t_point cen, t_color color, t_vec dir, t_vec p, int mat);
int hit_cylinder(t_cylinder *cy, int idx, t_ray *ray, t_record *rec);

#endif