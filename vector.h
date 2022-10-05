#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct s_vec {
	double x;
	double y;
	double z;
} t_vec;

typedef t_vec point3;

t_vec vector(const double x, const double y, const double z);
t_vec unit(const t_vec* v);
t_vec plus(const t_vec* v1, const t_vec* v2);
t_vec minus(const t_vec* v1, const t_vec* v2);
t_vec multiply(t_vec* v1, double t);
double length(const t_vec* v);
double dot(const t_vec* v1, const t_vec* v2);
t_vec cross(const t_vec* v1, const t_vec* v2);

#endif