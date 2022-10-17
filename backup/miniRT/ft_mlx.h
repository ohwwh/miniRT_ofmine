#ifndef FT_MLX_H
#define FT_MLX_H
#include <stdio.h>
#include "./mlx/mlx.h"
#include "camera.h"
#include "vector.h"
#include "objects.h"

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
}	t_scene;

typedef struct s_minirt {
	//void* mlx;
	//void* win;
	t_mlx mlx;
	t_scene scene;
	int is_move;
	int is_trace;
	//int window_height;
	//int window_width;
	//t_camera camera;
	//t_object* world;
	//t_object* light;
	int anti;
	int changed;
	
} t_minirt;

int 	rgb_to_int(t_color c);
void 	ft_pixel_put(t_minirt *vars, int x, int y, int color);
void	ft_mlx_init(t_minirt *vars);
void	ft_mlx_new(t_minirt *vars, int x, int y, char *name);

#endif