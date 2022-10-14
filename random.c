#include "random.h"

double random_double(double min, double max, int anti)
{
    if (anti == 0 || anti == 1)
        return (0);
    return ((max-min) * ((double)rand() / (double)RAND_MAX) + min);
}


t_vec random_cosine_direction()
{
    double pi = 3.1415926535897932385;
    double r1 = random_double(0, 1, 7);
    double r2 = random_double(0, 1, 7);
    double z = sqrt(1 - r2);

    double phi = 2 * pi * r1;
    double x = cos(phi) * sqrt(r2);
    double y = sin(phi) * sqrt(r2);

    return (create_vec(x, y, z));
}

t_onb create_onb(t_vec n)
{
    t_onb ret;
    t_vec a;

    ret.axis[2] = unit_vec(n);
    if (fabs(ret.axis[2].x) > 0.9)
        a = create_vec(0, 1, 0);
    else
        a = create_vec(1, 0, 0);
    ret.axis[1] = unit_vec(vcross(ret.axis[2], a));
    ret.axis[0] = vcross(ret.axis[2], ret.axis[1]);
}

t_vec local(t_onb *onb, t_vec *a)
{
    return (
        vec_sum(
            vec_scalar_mul(onb->axis[0], a->x),
            vec_sum(
                vec_scalar_mul(onb->axis[1], a->y),
                vec_scalar_mul(onb->axis[2], a->z)
            )
        )
    );
}

t_vec cosine_pdf(t_onb uvw);
