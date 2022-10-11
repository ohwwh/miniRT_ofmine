#include "camera.h"

double degrees_to_radians(double degrees)
{
	double pi = 3.1415926535897932385;

	return (degrees * pi / 180.0);
}

t_camera create_camera(t_point lookfrom, t_point lookat, t_vec vup, double vfov, double aspect_ratio)
{
	t_camera ret;

	double theta = degrees_to_radians(vfov);
	double h = tan(theta/2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	t_vec w = unit_vec(vec_sub(lookfrom, lookat));
	t_vec u = unit_vec(vcross(vup, w));
	t_vec v = vcross(w, u);

	ret.origin = lookfrom;
	/*ret.horizontal = create_vec(viewport_width,0.0,0.0);
	ret.vertical = create_vec(0.0,viewport_height,0.0);
	ret.lower_left_corner = create_vec(ret.origin.x + (- ret.horizontal.x / 2) + (-ret.vertical.x / 2) + (0)
		,ret.origin.y + (- ret.horizontal.y / 2) + (-ret.vertical.y / 2) + (0) 
		,ret.origin.z + (- ret.horizontal.z / 2) + (-ret.vertical.z / 2) + (-focal_length));
	//(orgin) - (horizontal / 2) - (vertical / 2) - vector(0,0,focal_length)*/
	ret.horizontal = vec_scalar_mul(u, viewport_width);
	ret.vertical = vec_scalar_mul(v, viewport_height);
	ret.lower_left_corner = create_vec(ret.origin.x + (-ret.horizontal.x / 2) + (-ret.vertical.x / 2) + (-w.x)
		,ret.origin.y + (- ret.horizontal.y / 2) + (-ret.vertical.y / 2) + (-w.y) 
		,ret.origin.z + (- ret.horizontal.z / 2) + (-ret.vertical.z / 2) + (-w.z));
	//(orgin) - (horizontal / 2) - (vertical / 2) - w
	
	return (ret);
}