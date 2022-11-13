#include "minirt.h"

t_aabb	*make_aabb(t_objs *objs)
{
	t_aabb	*ret;

	ret = (t_aabb *)malloc(sizeof(t_aabb));
	if (objs->type == SP)
	{
		t_point	radius = create_vec(objs->radius, objs->radius, objs->radius);

		ret->minimum = vec_sub(objs->center, radius);
		ret->maximum = vec_sum(objs->center, radius);
	}
	else if (objs->type == CY)
	{
		t_vec 	a = objs->center;
		t_vec 	b = vec_sum(a, vec_scalar_mul(objs->dir, objs->height));
		t_vec	radius = create_vec(objs->radius, objs->radius, objs->radius);

		ret->minimum = vec_sub(vmin(a, b), radius);
		ret->maximum = vec_sum(vmax(a, b), radius);
	}
	else if (objs->type == RCXY)
	{
		ret->minimum = create_vec(objs->center.x
							, objs->center.y
							, objs->radius - 0.0001);
		ret->maximum = create_vec(objs->dir.x
							, objs->dir.y
							, objs->radius + 0.0001);				
	}
	else if (objs->type == RCYZ)
	{
		ret->minimum = create_vec(objs->radius - 0.0001
							, objs->center.x
							, objs->center.y);
		ret->maximum = create_vec(objs->radius + 0.0001
							, objs->dir.x
							, objs->dir.y);				
	}
	else if (objs->type == RCXZ)
	{
		ret->minimum = create_vec(objs->center.x
							, objs->radius - 0.0001
							, objs->center.y);
		ret->maximum = create_vec(objs->dir.x
							, objs->radius + 0.0001
							, objs->dir.y);				
	}
	else
	{
		free(ret);
		ret = 0;
	}
	return (ret);
}

t_aabb	*make_surrounding_aabb(t_aabb *a, t_aabb *b)
{
	t_point	small;
	t_point	big;
	t_aabb	*ret;

	ret = (t_aabb *)malloc(sizeof(t_aabb));

	small.x = fmin(a->minimum.x, b->minimum.x);
	small.y = fmin(a->minimum.y, b->minimum.y);
	small.z = fmin(a->minimum.z, b->minimum.z);

	big.x = fmin(a->maximum.x, b->maximum.x);
	big.y = fmin(a->maximum.y, b->maximum.y);
	big.z = fmin(a->maximum.z, b->maximum.z);

	ret->minimum = small;
	ret->maximum = big;
	return (ret);
}