#include <stdio.h>
#include "vogle.h"

/*
 *	An array of points for a polygon
 */
static float	parray[][3] = {
	{-8.0, -8.0, 0.0},
	{-5.0, -8.0, 0.0},
	{-5.0, -5.0, 0.0},
	{-8.0, -5.0, 0.0}
};

/*
 * drawpoly
 *
 *	draw some polygons
 */
drawpoly()
{
	color(YELLOW);

	/*
	 * Draw a polygon using poly, parray is our array of
	 * points and 4 is the number of points in it.
	 */
	poly(4, parray);

	color(GREEN);

	/*
	 * Draw a 5 sided figure by using move, draw and closepoly.
	 */
	makepoly();
		move(0.0, 0.0, 0.0);
		draw(3.0, 0.0, 0.0);
		draw(3.0, 4.0, 0.0);
		draw(-1.0, 5.0, 0.0);
		draw(-2.0, 2.0, 0.0);
	closepoly();

	color(MAGENTA);

	/*
	 * draw a sector representing a 1/4 circle
	 */
	sector(1.5, -7.0, 3.0, 0.0, 90.0);

	getkey();
}

/*
 * Using polygons, hatching, and filling.
 */
main()
{
	char device[10];

	fprintf(stderr,"Enter output device: ");
	gets(device);

	vinit(device);

	color(BLACK);		/* clear to bleck */
	clear();

	/*
	 * world coordinates are now in the range -10 to 10
	 * in x, y, and z. Note that positive z is towards us.
	 */
	ortho(-10.0, 10.0, -10.0, 10.0, 10.0, -10.0);

	color(YELLOW);

	/*
	 * write out the string "Polygon from poly()" in the
	 * starting at (-8.0, -4.0) and scaled to be 4.0 units long,
	 * 0.5 units high.
	 */
	boxtext(-8.0, -4.0, 4.0, 0.5, "Polygon from poly()");

	color(GREEN);

	/*
	 * write out a scaled string starting at (0.0, 6.0)
	 */
	boxtext(0.0, 6.0, 4.0, 0.5, "Polygon from move()/ draw()");

	color(MAGENTA);

	/*
	 * write out a scaled string starting at (0.0, 6.0)
	 */
	boxtext(3.5, -3.5, 1.9, 0.5, "Sector");

	drawpoly();		/* draw some polygons */

	/*
	 * turn on polygon hatching
	 */
	polyhatch(1);
	hatchang(45.0);
	hatchpitch(0.3);

	/*
	 *  Rotate 20 degrees around x and 30 around y
	 */
	rotate(20.0, 'x');
	rotate(30.0, 'y');

	drawpoly();		/* draw some polygons wth hatching */

	/*
	 * turn on polygon filling - this automatically turns off hatching
	 */
	polyfill(1);

	/*
	 *  Do another set of rotations.
	 */
	rotate(20.0, 'x');
	rotate(30.0, 'y');

	drawpoly();		/* draw some polygons with filling */

	vexit();
}
