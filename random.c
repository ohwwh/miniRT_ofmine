#include "random.h"

double random_double(int anti)
{
    if (anti == 0 || anti == 1)
        return (0);
    return (2 * ((double)rand() / (double)RAND_MAX) - 1);
}
