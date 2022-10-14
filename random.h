#ifndef RANDOM_H
#define RANDOM_H
#include <math.h>
#include <stdlib.h>
#include "vector.h"

typedef struct s_onb {
	t_vec axis[3];
} t_onb;

double random_double(double min, double max, int anti);
t_vec random_cosine_direction();
t_onb create_onb(t_vec n);
t_vec local(t_onb *onb, t_vec *a);

#endif