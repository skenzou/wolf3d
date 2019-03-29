#include "wolf3d.h"

float	toRadian(float angle)
{
	return (angle * M_PI / 180.0);
}

float	Cos(float angle)
{
	return (cos(toRadian(angle)));
}

float	Sin(float angle)
{
	return (sin(toRadian(angle)));
}