#ifndef FT_MLX_H
#define FT_MLX_H
#include "./mlx/mlx.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_vars {
	void* mlx;
	void* win;
} t_vars;

int 	rgb_to_int(t_color c);
void 	ft_pixel_put(t_vars *vars, int x, int y, int color);
void	ft_mlx_init(t_vars *vars);
void	ft_mlx_new(t_vars *vars, int x, int y, char *name);

#endif