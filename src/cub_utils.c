#include <cub3d.h>
#include <math.h>

float	deg_to_rad(float angle)
{
	return (angle * M_PI / 180.0);
}

t_vec	vec_rotate(t_vec vec, float angle)
{
	t_vec	vec2;
	float	rad_angle;

	rad_angle = deg_to_rad(angle);
	vec2.x = (cos(rad_angle) * vec.x) - (sin(rad_angle) * vec.y);
	vec2.y = (sin(rad_angle) * vec.x) + (cos(rad_angle) * vec.y);
	return (vec2);
}

t_vec	normalize_vec(t_vec vec)
{
	float	a;
	float	b;
	float	c;

	a = vec.x * vec.x;
	b = vec.y * vec.y;
	c = sqrt(a + b);
	vec.x = vec.x / c;
	vec.y = vec.y / c;
	return (vec);
}
