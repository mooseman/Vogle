#include "vogle.h"

/*
 * circleprecision_
 */
void
circleprecision_(prec)
	int	*prec;
{
	circleprecision(*prec);
}

/*
 * arcprecision_
 */
void
arcprecision_(prec)
	int	*prec;
{
	circleprecision(*prec);
}

/*
 * arc_
 */
void
arc_(x, y, radius, startang, endang)
	float	*x, *y, *radius;
	float	*startang, *endang;
{
	arc(*x, *y, *radius, *startang, *endang);
}

/*
 * sector_
 */
void
sector_(x, y, radius, startang, endang)
	float	*x, *y, *radius;
	float	*startang, *endang;
{
	sector(*x, *y, *radius, *startang, *endang);
}

/*
 * circle_
 */
void
circle_(x, y, radius)
	float	*x, *y, *radius;
{
	circle(*x, *y, *radius);
}

