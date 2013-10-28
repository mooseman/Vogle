#include "vogle.h"

/*
 * rect
 *
 * draw a rectangle given two opposite corners
 *
 */
void
rect(x1, y1, x2, y2)
	float 	x1, y1, x2, y2;
{
	if (!vdevice.initialised)
		verror("rect: vogle not initialised");

	if ((vdevice.attr->a.fill || vdevice.attr->a.hatch) && !vdevice.inpolygon)
		makepoly();		/* want it filled */

	move2(x1, y1);
	draw2(x2, y1);
	draw2(x2, y2);
	draw2(x1, y2);

	if ((vdevice.attr->a.fill || vdevice.attr->a.hatch) && !vdevice.inpolygon)
		closepoly();
	else
		draw2(x1, y1);
}
