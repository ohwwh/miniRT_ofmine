#include "random.h"

double random_double()
{
    int temp;
    double ret;

    srand(time(0));
    temp = rand() % 2000;
    if (temp % 2)
        temp *= -1;
    ret = (double)temp / 2000;
    return (ret);
}