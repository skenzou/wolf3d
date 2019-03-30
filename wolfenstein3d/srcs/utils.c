#include "wolf3d.h"

float	toRadian(float angle)
{
	return (angle * M_PI / 180.0);
}

float	tCos(float angle)
{
	return (cos(toRadian(angle)));
}

float	tSin(float angle)
{
	return (sin(toRadian(angle)));
}
float	tTan(float angle)
{
	return (tan(toRadian(angle)));
}
