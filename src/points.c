#include "vogle.h"

/*
 * point
 *
 * plot a point in x, y, z.
 *
 */
void
point(x, y, z)
	float 	x, y, z;
{

	if(!vdevice.initialised)
		verror("point: vogle not initialised");

	move(x, y, z);  
	draw(x, y, z);	
}

/*
 * point
 *
 * plot a point in x, y.
 *
 */
void
point2(x, y)
	float	x, y;
{
	point(x, y, 0.0);
}

/*
 * spoint
 *
 * plot a point in screen coords.
 *
 */
void
spoint2(xs, ys)
	float	xs, ys;
{
	if (!vdevice.initialised)
		verror("spoint2: vogle not initialised");

	(*vdevice.dev.Vdraw)(vdevice.cpVx = (xs + 0.5) * (vdevice.maxVx - vdevice.minVx), vdevice.cpVy = (ys + 0.5) * (vdevice.maxVy - vdevice.minVy));
}
