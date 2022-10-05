#include "vector.h"

typedef struct s_ray {
	point3 org;
	t_vec dir;
} t_ray;

t_ray 	ray(point3 org, t_vec dir);
point3 	ray_end(t_ray* ray, double t);