#ifndef RAY_H
#define RAY_H
#include "vector.h"

typedef struct s_ray {
	t_point org;
	t_vec dir;
} t_ray;

typedef struct s_record {
	t_point p;
	t_vec normal;
	double t_max;
	double t_min;
	double t;
	int front_face;
} t_record;

t_ray 	ray(t_point org, t_vec dir);
t_point 	ray_end(t_ray* ray, double t);

#endif