#ifndef FT_MLX_H
#define FT_MLX_H
#include <stdio.h>
#include "./mlx/mlx.h"
#include "camera.h"
#include "vector.h"
#include "objects.h"
#include "ray.h"

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
	int 	window_height;
	int 	window_width;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_light
{
	t_vec			src;
	double			ratio;
	t_object		*object;
	t_ambient		amb;
	struct s_light	*next;
}	t_light;

typedef struct s_ambient
{
	t_vec	col;
	double	ratio;
	int 	count;
}	t_ambient;

typedef struct s_scene
{
	t_camera	camera;
	//t_light		*light;
	t_object 	*light;
	t_object	*world;
	t_ambient	ambient;
	int anti;
	int changed;
	double light_sample;
}	t_scene;

typedef struct s_minirt {
	t_mlx mlx;
	t_scene scene;
	t_ray ray;
	int is_move;
	int is_trace;
	
} t_minirt;

int 	rgb_to_int(t_color c);
void	put_color(t_mlx *data, int x, int y, int color);
void 	ft_pixel_put(t_minirt *vars, int x, int y, int color);
void	ft_mlx_init(t_minirt *vars);
void	ft_mlx_new(t_minirt *vars, int x, int y, char *name);

#endif