#include "vogle.h"

/*
 * point_
 */
void
point_(x, y, z)
	double 	*x, *y, *z;
{
	point(*x, *y, *z);
}

/*
 * point2_
 */
void
point2_(x, y)
	double	*x, *y;
{
	point(*x, *y, 0.0);
}

