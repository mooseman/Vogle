#include "vogle.h"

#define	MIN(x, y)	(float)((x) < (y) ? (x) : (y))

/*
 * getaspect
 *
 *	Gets the aspect ratio of the display/window.
 *	IE. y / x
 */
float
getaspect()
{
	return((float)vdevice.sizeSy / (float)vdevice.sizeSx);
}

/*
 * getdisplaysize
 *
 *	Returns the raw size of the display window in pixel units
 *	as floating point values.
 */
void
getdisplaysize(x, y)
	float	*x, *y;
{
	*x = (float)vdevice.sizeSx;
	*y = (float)vdevice.sizeSy;
}

/*
 * getfactors
 *
 *	returns two x and y scaling factors for use with the
 *	viewport call so as the viewport can be set to the
 *	whole display/window.
 */
void
getfactors(x, y)
	float	*x, *y;
{
	*x = (float)vdevice.sizeSx / (float)vdevice.sizeX;
	*y = (float)vdevice.sizeSy / (float)vdevice.sizeY;
}
