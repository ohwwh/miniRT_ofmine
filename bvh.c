#include "minirt.h"

t_aabb* make_bvh(t_objs *start, t_objs *end, int size)
{
    t_objs  *tmp;

    sort(start, end);
    tmp  = start;
}