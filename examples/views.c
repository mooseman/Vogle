#include <stdio.h>
#include "vogle.h"

/*
 *	Shows various combinations of viewing and
 *	projection transformations.
 */
main()
{
	char device[20];

	fprintf(stderr,"Enter device name: ");
	gets(device);
	vinit(device);

	color(BLACK);
	clear();

	/*
	 * we want to draw just within the boundaries of the screen
	 */
	viewport(-0.9, 0.9, -0.9, 0.9);


	ortho2(-5.0, 5.0, -5.0, 5.0);	/* set the world size */

	color(RED);
	rect(-5.0, -5.0, 5.0, 5.0);	/* draw a boundary frame */

	/*
	 * set up a perspective projection with a field of view of
	 * 40.0 degrees, aspect ratio of 1.0, near clipping plane 0.1,
	 * and the far clipping plane at 1000.0.
	 */
	perspective(40.0, 1.0, 0.1, 1000.0);

	/*
	 * we want the drawing to be done with our eye point at (5.0, 8.0, 5.0)
	 * looking towards (0.0, 0.0, 0.0). The last parameter gives a twist
	 * in degrees around the line of sight, in this case zero.
	 */
	lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0);

	drawtetra();

	move2(-4.5, -4.5);
	textsize(0.6, 0.9);		/* set the text size */
	drawstr("perspective/lookat");

	getkey();

	/*
	 * window can also be used to give a perspective projection. Its
	 * arguments are 6 clipping planes, left, right, bottom, top, near,
	 * and far.
	 */
	window(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	/*
	 * as window replaces the current transformation matrix we must
	 * specify our viewpoint again.
	 */
	lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0);

	color(BLACK);
	clear();

	color(GREEN);
	rect(-5.0, -5.0, 5.0, 5.0);

	drawtetra();

	move2(-4.5,-4.5);
	textsize(0.6, 0.9);		/* set the text size */
	drawstr("window/lookat");

	getkey();

	/*
	 * set up our original perspective projection again.
	 */
	perspective(40.0, 1.0, 0.1, 1000.0);
	/*
	 * polarview also specifies our viewpoint, but, unlike lookat, in polar
	 * coordinates. Its arguments are the distance from the world origin, an
	 * azimuthal angle in the x-y plane measured from the y axis, an 
	 * incidence angle in the y-z plane measured from the z axis, and a
	 * twist around the line of sight.
	 */
	polarview(15.0, 30.0, 30.0, 30.0);

	color(BLACK);
	clear();

	color(MAGENTA);
	rect(-5.0, -5.0, 5.0, 5.0);

	drawtetra();

	move2(-4.5,-4.5);
	textsize(0.6, 0.9);		/* set the text size */
	drawstr("perspective/polarview");

	getkey();

	/*
	 * once more with window for comparison
	 */
	window(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
	polarview(6.0, 20.0, -30.0, 70.0);

	color(BLACK);
	clear();

	color(YELLOW);
	rect(-5.0, -5.0, 5.0, 5.0);

	drawtetra();

	move2(-4.5,-4.5);
	textsize(0.6, 0.9);		/* set the text size */
	drawstr("window/polarview");

	getkey();

	vexit();
}

/*
 * drawtetra
 *
 *	generate a tetraedron as a series of move draws
 */
drawtetra()
{
	
	move(-0.5,  0.866, -0.5);
	draw(-0.5, -0.866, -0.5);
	draw( 1.0,  0.0,   -0.5);
	draw(-0.5,  0.866, -0.5);
	draw( 0.0,  0.0,    1.5);
	draw(-0.5, -0.866, -0.5);
	move( 1.0,  0.0,   -0.5);
	draw( 0.0,  0.0,    1.5);
	
	/* 
	 * Label the vertices.
	 */
	color(WHITE);
	textsize(0.3, 0.5);		/* set the text size */
	move(-0.5,  0.866, -0.5);
	drawchar('a');
	move(-0.5, -0.866, -0.5);
	drawchar('b');
	move( 1.0,  0.0,   -0.5);
	drawchar('c');
	move( 0.0,  0.0,    1.5);
	drawchar('d');
}
