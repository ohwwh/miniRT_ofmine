#include "random.h"

double random_double()
{
    int temp;
    double ret;

    temp = (rand() % 20000) - 10000;
    ret = (double)temp / (double)10000;
    return (ret);
}