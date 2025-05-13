#include "../../inc/functions.h"

float	get_fov_scale(void)
{
	float fov_rad;
	fov_rad = (float)FOV * PI_const / 180.0;
	return tanf(fov_rad / 2.0f);
}

int	rgb_to_color(t_rgb *color)
{
	return (color->red << 16) | (color->green << 8) | (color->blue);
}
