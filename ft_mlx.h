#include "./mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_vars {
	void* mlx;
	void* win;
} t_vars;

int rgb_to_int(double t, double r, double g, double b);
void 	ft_pixel_put(t_vars *vars, int x, int y, int color);
void	ft_mlx_init(t_vars *vars);
void	ft_mlx_new(t_vars *vars, int x, int y, char *name);