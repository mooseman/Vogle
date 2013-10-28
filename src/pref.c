
#include "vogle.h"

static	int	px = -1, py = -1, pxs = -1, pys = -1;

/*
 * prefposition
 *
 *	Specify a prefered position for a window that is
 *	under control of a window manager.
 *	Position is the location of the upper left corner.
 *	Should be called before vinit.
 */
void
prefposition(x, y)
	int	x, y;
{
	if (x < 0)
		verror("prefposition: bad x value");

	if (y < 0)
		verror("prefposition: bad y value");

	px = x;
	py = y;
}

/*
 * prefsize
 *
 *	Specify the prefered size for a window under control of
 *	a window manager.
 *	Should be called before vinit.
 */
void
prefsize(x, y)
	int	x, y;
{
	if (x < 0)
		verror("prefsize: bad x value");

	if (y < 0)
		verror("prefsize: bad y value");

	pxs = x;
	pys = y;
}

/*
 * getprefposandsize
 *
 *	Returns the prefered position and size of a window under
 *	control of a window manager. (-1 for unset parameters)
 */
void
getprefposandsize(x, y, xs, ys)
	int	*x, *y, *xs, *ys;
{
	*x = px;
	*y = py;
	*xs = pxs;
	*ys = pys;
}

