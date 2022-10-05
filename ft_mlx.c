#include "ft_mlx.h"

/*int rgb_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}*/

int rgb_to_int(double t, double r, double g, double b)
{
	return ((int)(255 * t) << 24 | (int)(255 * r) << 16 | (int)(255 * g) << 8 | (int)(255 * b));
}

void ft_pixel_put(t_vars *vars, int x, int y, int color)
{
	mlx_pixel_put(vars->mlx, vars->win, x, y, color);
}

void	ft_mlx_init(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		printf("Error\nmlx_init fail\n");
	vars->win = mlx_new_window(vars->mlx, 640, 400, "menu");
	if (!vars->win)
	{
		printf("Error\nmlx_new_window fail\n");
		exit(0);
	}
}

void	ft_mlx_new(t_vars *vars, int x, int y, char *name)
{
	vars->win = mlx_new_window(vars->mlx, x, y, name);
	if (!vars->win)
	{
		printf("Error\nmlx_new_window fail\n");
		exit(0);
	}
}