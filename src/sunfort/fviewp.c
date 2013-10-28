#include "vogle.h"

/*
 * pushviewport_
 */
pushviewport_()
{
	pushviewport();
}

/*
 * popviewport_
 */
popviewport_()
{
	popviewport();
}

/*
 * viewport_
 */
viewport_(xlow, xhigh, ylow, yhigh)
	float	*xlow, *ylow, *xhigh, *yhigh;
{
	viewport(*xlow, *xhigh, *ylow, *yhigh);
}

/*
 * getviewport_
 */
getviewport_(left, right, bottom, top)
	float	*left, *right, *bottom, *top;
{
	getviewport(left, right, bottom, top);
}

