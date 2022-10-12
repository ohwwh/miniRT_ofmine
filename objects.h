#ifndef OBJECTS_H
#define OBJECTS_H
#include "ray.h"
#include "vector.h"

typedef struct s_object {
	int				type;
	t_vec			center;
	t_vec			dir;
	double 			radius;
	double 			height;
	t_vec			color;
	t_vec			norm;
	struct s_objs	*next;
    int mat;
} t_object;

int hit_sphere(t_object* s, t_ray* r, t_record* rec);
t_object create_sphere(t_point c, double r, t_color color, int mat);

#endif