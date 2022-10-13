#include "random.h"

double random_double(double min, double max, int anti)
{
    if (anti == 0 || anti == 1)
        return (0);
    return ((max-min) * ((double)rand() / (double)RAND_MAX) + min);
}
