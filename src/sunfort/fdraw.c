#include "vogle.h"

/*
 * draw_
 */
void
draw_(x, y, z)
	float	*x, *y, *z;
{
	draw(*x, *y, *z);
}

/*
 * draw2_
 */
void
draw2_(x, y)
	float	*x, *y;
{
	draw2(*x, *y);
}

/*
 * rdraw_
 */
void
rdraw_(dx, dy, dz)
	float	*dx, *dy, *dz;
{
	rdraw(*dx, *dy, *dz);
}

/*
 * rdraw2_
 */
void
rdraw2_(dx, dy)
	float	*dx, *dy;
{
	rdraw2(*dx, *dy);
}

/*
 * sdraw2_
 */
void
sdraw2_(xs, ys)
	float 	*xs, *ys;
{
	sdraw2(*xs, *ys);
}

/*
 * rsdraw2_
 */
void
rsdraw2_(dxs, dys)
	float	*dxs, *dys;
{
	rsdraw2(*dxs, *dys);
}
