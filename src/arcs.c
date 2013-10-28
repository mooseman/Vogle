#include "vogle.h"

#ifdef	TC

extern	double	cos();
extern	double	sin();

#else 

#include <math.h>

#endif

static int	nsegs = 32;

/*
 * arcprecision
 *
 *	sets the number of segments in an arc or circle.
 *	- obsolete function.
 */
void
arcprecision(noseg)
	int	noseg;
{
	nsegs = noseg;
}

/*
 * circleprecision
 *
 *	sets the number of segments in an arc or circle.
 */
void
circleprecision(noseg)
	int	noseg;
{
	nsegs = noseg;
}

/*
 * arc
 *
 * draw an arc at a given location.  Precision of arc (# line segments)
 * is calculated from the value given to circleprecision.
 *
 */
void
arc(x, y, radius, startang, endang)
	float	x, y, radius;
	float	startang, endang;
{
	Token	*t;
	float	cx, cy, dx, dy;
	float	deltang, cosine, sine, angle;
	int	i, numsegs;

	if (!vdevice.initialised)
		verror("arc: vogle not initialised");

	angle = startang * D2R;
	numsegs = (endang - startang) / 360.0 * nsegs + 0.5;
	deltang = (endang - startang) * D2R / numsegs;
	cosine = cos((double)deltang);
	sine = sin((double)deltang);

	if (vdevice.inobject) {
		t = newtokens(8);
		t[0].i = ARC;
		t[1].f = x;
		t[2].f = y;
		t[3].f = radius * cos((double)angle);
		t[4].f = radius * sin((double)angle);
		t[5].f = cosine;
		t[6].f = sine;
		t[7].i = numsegs;
		return;
	}

	/* calculates initial point on arc */

	cx = x + radius * cos((double)angle);
	cy = y + radius * sin((double)angle);
	move2(cx, cy);

	for (i = 0; i < numsegs; i++)  {
		dx = cx - x; 
		dy = cy - y;
		cx = x + dx * cosine - dy * sine;
		cy = y + dx * sine + dy * cosine;
		draw2(cx, cy);
	}
}

/*
 * sector
 *
 *	draw a sector in a given location. The number of line segments in the
 * arc of the segment is the same as in arc.
 */
void
sector(x, y, radius, startang, endang)
	float	x, y, radius;
	float	startang, endang;
{
	Token	*t;
	float	cx, cy, dx, dy;
	float	deltang, cosine, sine, angle;
	int	i, numsegs, inpoly;

	if (!vdevice.initialised)
		verror("segment: vogle not initialised");

	angle = startang * D2R;
	numsegs = (endang - startang) / 360.0 * nsegs + 0.5;
	deltang = (endang - startang) * D2R / numsegs;
	cosine = cos((double)deltang);
	sine = sin((double)deltang);

	if (vdevice.inobject) {
		t = newtokens(8);
		t[0].i = SECTOR;
		t[1].f = x;
		t[2].f = y;
		t[3].f = radius * cos((double)angle);
		t[4].f = radius * sin((double)angle);
		t[5].f = cosine;
		t[6].f = sine;
		t[7].i = numsegs;
		return;
	}

	inpoly = vdevice.inpolygon;

	if ((vdevice.attr->a.fill || vdevice.attr->a.hatch) && !inpoly)
		makepoly();		/* want it filled */

	move2(x, y);
			/* calculates initial point on arc */

	cx = x + radius * cos((double)angle);
	cy = y + radius * sin((double)angle);

	draw2(cx, cy);

	for (i = 0; i < numsegs; i++)  {
		dx = cx - x; 
		dy = cy - y;
		cx = x + dx * cosine - dy * sine;
		cy = y + dx * sine + dy * cosine;
		draw2(cx, cy);
	}

	if ((vdevice.attr->a.fill || vdevice.attr->a.hatch) && !inpoly)
		closepoly();
	else
		draw2(x, y);
}

/*
 * circle
 *
 * Draw a circle of given radius at given world coordinates. The number of
 * segments in the circle is the same as that of an arc.
 *
 */
void
circle(x, y, radius)
	float	x, y, radius;
{
	Token	*t;
	float	cx, cy, dx, dy;
	float	angle, cosine, sine;
	int	i, inpoly;

	if (!vdevice.initialised)
		verror("circle: vogle not initialised");

	angle = 2.0 * PI / nsegs;
	cosine = cos((double)angle);
	sine = sin((double)angle);

	if (vdevice.inobject) {
		t = newtokens(7);
		t[0].i = CIRCLE;
		t[1].f = x;
		t[2].f = y;
		t[3].f = radius;
		t[4].f = cosine;
		t[5].f = sine;
		t[6].i = nsegs;
		return;
	}

	cx = x + radius;
	cy = y;

	inpoly = vdevice.inpolygon;

	if ((vdevice.attr->a.fill || vdevice.attr->a.hatch) && !inpoly)
		makepoly();		/* want it filled */

	move2(cx, cy);
	for (i = 0; i < nsegs - 1; i++) {
		dx = cx - x; 
		dy = cy - y;
		cx = x + dx * cosine - dy * sine;
		cy = y + dx * sine + dy * cosine;
		draw2(cx, cy);
	}

	if ((vdevice.attr->a.fill || vdevice.attr->a.hatch) && !inpoly)
		closepoly();
	else
		draw2(x + radius, y);
}
