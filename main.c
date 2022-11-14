/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:28:58 by hako              #+#    #+#             */
/*   Updated: 2022/11/14 14:32:09 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_minirt	data;
	int			fd;

	if (check_file(ac, av))
		err_handler("wrong argument");
	fd = open(av[1], O_RDONLY);
	init_rt(&data);
	parse(&data.scene, fd);
	set_init_distance(&data);
	create_light_object(&data.scene);
	t_objs **objs_array = make_objs_array(data.scene.objs, data.scene.light, data.scene.objs_num);
	//test_print(data.scene.objs_num, objs_array);
	t_bvh_node *bvh = make_bvh(objs_array, 0, data.scene.objs_num - 1);
	data.scene.bvh = bvh;
	//test_print(data.scene.objs_num, objs_array);
	free(objs_array);
	set_camera(&data.scene.camera);
	raw_render(&data);
	mlx_hook(data.mlx.mlx_win, 2, 0, &keypress, &data);
	mlx_hook(data.mlx.mlx_win, 3, 0, &keyrelease, &data);
	mlx_hook(data.mlx.mlx_win, 4, 0, &scroll, &data);
	mlx_hook(data.mlx.mlx_win, 17, 0L, ft_close, &data);
	mlx_loop_hook(data.mlx.mlx, &key_hook_move, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
