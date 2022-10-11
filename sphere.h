#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "ray.h"
#include "ft_mlx.h"

typedef struct s_sphere {
    t_point center;
    double rad;
    t_color color;
    int mat;
} t_sphere;

int hit_sphere(t_sphere* s, int i, t_ray* r, t_record* rec);
t_sphere create_sphere(t_point c, double r, t_color color, int mat);

#endif