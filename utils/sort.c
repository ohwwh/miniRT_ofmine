#include "minirt.h"

void	swap(t_objs **a, t_objs **b)
{
	t_objs	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	quick_sort(t_objs **objs_array, int start, int end)
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
		while (left <= right && objs_array[right]->box->minimum.x >= pivot->box->minimum.x)
			right --;
		while (left <= right && objs_array[left]->box->minimum.x <= pivot->box->minimum.x)
			left ++;
		if (left <= right)
			swap(&objs_array[left], &objs_array[right]);
	}
	swap(&objs_array[start], &objs_array[right]);
	quick_sort(objs_array, start, right - 1);
	quick_sort(objs_array, right + 1, end);
}