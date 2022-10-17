#ifndef MINIRT_H
#define MINIRT_H

#define WIDTH 640
#define HEIGHT 320

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "camera.h"
#include "vector.h"
#include "random.h"
#include "libohw/includes/libft.h"
#include "./mlx/mlx.h"
#define MAX_DEPTH 50
//#define ANTI 100

typedef struct s_ray {
	t_point origin;
	t_vec dir;
} t_ray;

typedef struct s_record {
	t_point p;
	t_vec normal;
	t_color color;
	double t_max;
	double t_min;
	double t;
	int front_face;
	int idx;
	int mat;
	int type;
	double refraction;
	double specular;
	double u;
	double v;
} t_record;

typedef struct s_ambient
{
	t_vec	col;
	double	ratio;
	int 	count;
}	t_ambient;

typedef struct s_object {
	int				type;
	t_point			center;
	t_vec			dir;
	double 			radius;
	double 			height;
	t_color			color;
	t_vec			norm;
	struct s_object	*next;
    int mat;
	double refraction;
	double specular;
} t_object;

typedef struct s_light
{
	t_vec			src;
	double			ratio;
	t_object		*object;
	t_ambient		ambient;
	struct s_light	*next;
}	t_light;

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


typedef struct s_scene
{
	t_camera	camera;
	t_light		*light;
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

void print_init(t_minirt vars);


int 	rgb_to_int(t_color c);
void	put_color(t_mlx *data, int x, int y, int color);
void 	ft_pixel_put(t_minirt *vars, int x, int y, int color);
void	ft_mlx_init(t_minirt *vars);
void	ft_mlx_new(t_minirt *vars, int x, int y, char *name);


int front_face(t_ray *r, t_record* rec);
int find_hitpoint(t_ray* ray, t_object *objs, t_light *light, t_record* rec);
int hit_sphere(t_object* s, t_ray* r, t_record* rec);
int hit_cylinder(t_object *cy, t_ray *ray, t_record *rec);
int hit_caps(t_object *cy, t_ray *ray, t_record *rec);
int hit_plane(t_object *pl, t_ray *ray, t_record* rec);
int hit_rectangle_xy(t_object *rect, t_ray *ray, t_record* rec);
int hit_rectangle_yz(t_object *rect, t_ray *ray, t_record* rec);
int hit_rectangle_xz(t_object *rect, t_ray *ray, t_record* rec);



void set_refraction(t_object* obj, double ref);
double get_light_size(t_object object);
t_object create_sphere(t_point c, double r, t_color color, int mat);
t_object create_cylinder(t_point c, double r, double h, t_vec dir, t_color color, int mat);
t_object create_plane(t_point c, t_vec dir, t_color color, int mat);
t_object create_rectangle_xy(t_vec x, t_vec y, double k, t_color color, int mat);
t_object create_rectangle_yz(t_vec y, t_vec z, double k, t_color color, int mat);
t_object create_rectangle_xz(t_vec x, t_vec z, double k, t_color color, int mat);


t_ray 	ray(t_point org, t_vec dir);
t_point 	ray_end(t_ray* ray, double t);
t_vec reflect(t_vec v, t_vec n);
t_color ray_color_2(t_ray r, t_object* world, t_light* light);
t_color ray_color(t_ray r, t_object* world, t_light* light, int depth);


int	keybind(int keycode, t_minirt* vars);
int	keyrelease(int keycode, t_minirt* vars);
int scroll(int mousecode, int x, int y, t_minirt* vars);
int key_hook_move(t_minirt* vars);
void key_press_w(t_minirt* vars);
void key_press_a(t_minirt* vars);
void key_press_s(t_minirt* vars);
void key_press_d(t_minirt* vars);
void key_press_up(t_minirt* vars);
void key_press_left(t_minirt* vars);
void key_press_down(t_minirt* vars);
void key_press_right(t_minirt* vars);

#endif