#include "minirt.h"

t_objs  **make_objs_array(t_objs *objs, t_light *light, int num)
{
    t_objs  **ret;
    t_objs  *tmp;
    t_light *tmp_light;
    int        i;

    if (!num)
        return (0);
    i = 0;
    tmp = objs;
    ret = (t_objs **)malloc(sizeof(t_objs *) * num);
    while (tmp)
    {
        if (tmp->type == PL || tmp->type == RCXY
            || tmp->type == RCYZ || tmp->type == RCXZ)
        {
            tmp = tmp->next;
            continue ;
        }
        ret[i] = tmp;
        tmp->idx = i;
        tmp->box = make_aabb(tmp);
        tmp = tmp->next;
        i ++;
    }
    /*tmp_light = light;
    while (tmp_light)
    {
        ret[i] = &(tmp_light->object);
        tmp_light->object.idx = i;
        tmp_light->object.box = make_aabb(&(tmp_light->object));
        tmp_light = tmp_light->next;
        i ++;
    }*/
    return (ret);
}

t_bvh_node  *make_bvh(t_objs **objs_array, int start, int end)
{
    t_objs  *tmp;
    t_bvh_node *node;
    int     mid;
    int     span;

    if (!objs_array)
        return (0);
    span = end - start;
    node = (t_bvh_node *)malloc(sizeof(t_bvh_node));
    if (span == 0)
    {
        node->box = (objs_array[start])->box;
        //printf("%d\n", objs_array[start]->idx);
        node->left = 0;
        node->right = 0;

        return (node);
    }
    //quick_sort(objs_array, start, end, (rand() % 3));
    quick_sort(objs_array, start, end, 0);
    mid = start + span / 2;
    node->left = make_bvh(objs_array, start, mid);
    node->right = make_bvh(objs_array, mid + 1, end);
    node->box = make_surrounding_aabb(node->left->box, node->right->box);

    return (node);
}

t_objs  *make_none_bvh(t_objs *objs)
{
    t_objs  *tmp;
    t_objs  *non_objs;
    t_objs  *ret;

    ret = 0;
    non_objs = 0;
    tmp = objs;
    while (tmp)
    {
        if (tmp->type == PL || tmp->type == RCXY
            || tmp->type == RCYZ || tmp->type == RCXZ)
        {
            if (non_objs)
                non_objs->next = tmp;
            else
                ret = tmp;
            non_objs = tmp;
        }
        tmp = tmp->next;
    }
    if (non_objs)
        non_objs->next = 0;
    return (ret);
}

void    free_bvh(t_bvh_node *root)
{
    if (!root)
        return ;
    free_bvh(root->left);
    free_bvh(root->right);
    free(root->box);
    free(root);
}