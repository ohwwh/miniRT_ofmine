#include "minirt.h"

void	swap(t_objs **a, t_objs **b)
{
	t_objs	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	quick_sort(t_objs **objs_array, int start, int end, int axis)
{
	t_objs	*pivot;
	int		left;
	int		right;

	if (start >= end)
		return ;
	pivot = objs_array[start];
	left = start + 1;
	right = end;
	while (left <= right)
	{
		if (axis == 0)
		{
			while (left <= right && objs_array[right]->box->minimum.x >= pivot->box->minimum.x)
				right --;
			while (left <= right && objs_array[left]->box->minimum.x <= pivot->box->minimum.x)
				left ++;
		}
		else if (axis == 1)
		{
			while (left <= right && objs_array[right]->box->minimum.y >= pivot->box->minimum.y)
				right --;
			while (left <= right && objs_array[left]->box->minimum.y <= pivot->box->minimum.y)
				left ++;
		}
		else
		{
			while (left <= right && objs_array[right]->box->minimum.z >= pivot->box->minimum.z)
				right --;
			while (left <= right && objs_array[left]->box->minimum.z <= pivot->box->minimum.z)
				left ++;
		}
		if (left <= right)
			swap(&objs_array[left], &objs_array[right]);
	}
	swap(&objs_array[start], &objs_array[right]);
	quick_sort(objs_array, start, right - 1, axis);
	quick_sort(objs_array, right + 1, end, axis);
}