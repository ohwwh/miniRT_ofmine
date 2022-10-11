#include "random.h"

double random_double()
{
    /*int temp;
    double ret;

    temp = (rand() % 20000) - 10000;
    ret = (double)temp / (double)10000;
    return (ret);*/
    if (ANTI == 0 || ANTI == 1)
        return (0);
    return (2 * ((double)rand() / (double)RAND_MAX) - 1);
}
