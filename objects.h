#ifndef OBJECTS_H
#define OBJECTS_H
#include "vector.h"

typedef struct s_object {
	int				type;
	t_vec			center;
	t_vec			dir;
	double 			radius;
	double 			height;
	t_vec			color;
	t_vec			norm;
	struct s_object	*next;
    int mat;
} t_object;

t_object create_sphere(t_point c, double r, t_color color, int mat);
t_object create_cylinder(t_point c, double r, double h, t_vec dir, t_color color, int mat);

#endif