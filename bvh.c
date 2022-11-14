#include "minirt.h"

t_objs  **make_objs_array(t_objs *objs, t_light *light, int num)
{
    t_objs  **ret;
    t_objs  *tmp;
    t_light *tmp_light;
    int        i;

    i = 0;
    tmp = objs;
    ret = (t_objs **)malloc(sizeof(t_objs *) * num);
    while (tmp)
    {
        if (tmp->type == PL)
            continue ;
        ret[i] = tmp;
        tmp->box = make_aabb(tmp);
        tmp = tmp->next;
        i ++;
    }
    tmp_light = light;
    while (tmp_light)
    {
        ret[i] = &(tmp_light->object);
        tmp_light->object.box = make_aabb(&(tmp_light->object));
        tmp_light = tmp_light->next;
        i ++;
    }
    return (ret);
}

t_bvh_node  *make_bvh(t_objs **objs_array, int start, int end)
{
    t_objs  *tmp;
    t_bvh_node *node;
    int     mid;
    int     span;

    span = end - start;
    node = (t_bvh_node *)malloc(sizeof(t_bvh_node));
    if (span == 0)
    {
        node->box = (objs_array[start])->box;
        node->left = 0;
        node->right = 0;

        return (node);
    }
    quick_sort(objs_array, start, end);
    mid = start + span / 2;
    node->left = make_bvh(objs_array, start, mid);
    node->right = make_bvh(objs_array, mid + 1, end);
    node->box = make_surrounding_aabb(node->left->box, node->right->box);

    return (node);
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