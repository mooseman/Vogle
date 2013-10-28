#include "vogle.h"

/*
 * Demonstrate how to use non-square viewports, the associated
 * distortion caused and how to fix it.
 */
main()
{
	float	xfact, yfact;
	char	buf[120];

	vinit("");
	color(BLACK);
	clear();

	/* 
	 * Make the viewport the same size as the screen/window.
 	 */
	getfactors(&xfact, &yfact);
	viewport(-1.0, xfact, -1.0, yfact);

	/*
	 * Draw a square. (Looks like a rectangle, if the viewport
	 * wasn't "accidentally" square)
	 */
	color(1);
	rect(-0.5, -0.5, 0.5, 0.5);

	/* 
	 * Tell them what it is.
	 */
	move2(-1.0, 0.9);
	sprintf(buf,"Distorted square (viewport(-1, %7.3f, -1, %7.3f))",
	xfact, yfact);
	drawstr(buf);
	getkey();


	/*
	 * Fix up the distortion (The actual formula to fix
	 * the distortion is (viewport.xmax * (1 + xfact) / 2.0),
	 * and similar for the y axis.
	 */
	ortho2(-1.0, xfact, -1.0, yfact);

	/*
	 * Draw another square (Really is square this time)
	 */
	color(3);
	rect(-0.5, -0.5, 0.5, 0.5);

	/* 
	 * Tell them what it is.
	 */
	move2(-1.0, -0.9);
	sprintf(buf,"Fixed up square with ortho2(-1, %7.3f, -1, %7.3f)", 
	xfact, yfact);
	drawstr(buf);
	getkey();

	/*
	 * Do it with world coords going from 0 - 5, 0 - 5.
	 * Reset square viewport.
	 */
	color(0);
	clear();

	viewport(-1.0, 1.0, -1.0, 1.0);
	ortho2(0.0, 5.0, 0.0, 5.0);
	textsize(0.1, 0.1);

	/*
	 * Square from 1 to 3. (Really is square)
	 */
	color(2);
	rect(1.0, 1.0, 3.0, 3.0);

	move2(0.0, 4.5);
	drawstr("Square from 0 - 3, 0 - 3");

	getkey();

	/*
	 * Distort it with a non-square viewport.
	 */
	viewport(-1.0, xfact, -1.0, yfact);

	color(4);
	rect(1.0, 1.0, 3.0, 3.0);

	move2(0.0, 0.5);
	drawstr("Distorted square from 0 - 3, 0 - 3");

	getkey();

	/*
	 * Fix the distortion.
	 */
	ortho2(0.0, 5.0 * (1.0 + xfact) / 2.0, 0.0, 5.0 * (1.0 + yfact) / 2.0);
	
	color(5);
	rect(1.0, 1.0, 3.0, 3.0);

	move2(0.0, 2.5);
	drawstr("Fixed up  square from 0 - 3, 0 - 3");

	getkey();

	vexit();
}
