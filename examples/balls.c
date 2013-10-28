#include <stdio.h>
#include "vogle.h"

#ifdef	TC
#define	poly	_poly
#endif 

#include <math.h>

#ifdef TC
#undef	poly
#define	poly	poly
#endif

#define RADIUS 10.0
#define	SPHERE	1

/*
 * makesphere
 *
 *	make a sphere object
 */
makesphere()
{
	float	i, r, z, a;

	makeobj(SPHERE);

		/*
		 * create the latitudinal rings
		 */
		for (i = 0; i < 180; i += 20) {
			pushmatrix();
				rotate(i, 'y');
				circle(0.0, 0.0, RADIUS);
			popmatrix();
		}
		
		/*
		 * create the longitudinal rings
		 */
		pushmatrix();
			rotate(90.0, 'x');
			for (a = -90.0; a < 90.0; a += 20.0) {
				r = RADIUS * cos((double)a * PI / 180.0);
				z = RADIUS * sin((double)a * PI / 180.0);
				pushmatrix();
					translate(0.0, 0.0, -z);
					circle(0.0, 0.0, r);
				popmatrix();	
			}
		popmatrix();

	closeobj();
}

/*
 * a demonstration of objects
 */
main()
{
	char	dev[20];

	fprintf(stderr,"Enter device: ");
	gets(dev);

	vinit(dev);

	/*
	 * set up our viewing transformation
	 */
	perspective(90.0, 1.0, 0.001, 500.0);
	lookat(13.0, 13.0, 8.0, 0.0, 0.0, 0.0, 0.0);

	color(BLACK);
	clear();

	/*
	 * Call a routine to make the sphere object
	 */
	makesphere();

	/*
	 * Now draw the sphere object scaled down. We use the pushmatrix
	 * and the popmatrix to preserve the transformation matrix so
	 * that only this sphere is drawn scaled.
	 */
	color(CYAN);

	pushmatrix();
		scale(0.5, 0.5, 0.5);
		callobj(SPHERE);
	popmatrix();

	/*
	 * now we draw the same sphere translated, with a different
	 * scale and color.
	 */

	color(WHITE);

	pushmatrix();
		translate(0.0, -1.4 * RADIUS, 1.4 * RADIUS);
		scale(0.3, 0.3, 0.3);
		callobj(SPHERE);
	popmatrix();

	/*
	 * and maybe a few more times....
	 */


	color(RED);

	pushmatrix();
		translate(0.0, RADIUS, 0.7 * RADIUS);
		scale(0.2, 0.2, 0.2);
		callobj(SPHERE);
	popmatrix();

	color(GREEN);

	pushmatrix();
		translate(0.0, 1.5 * RADIUS, -RADIUS);
		scale(0.15, 0.15, 0.15);
		callobj(SPHERE);
	popmatrix();

	color(YELLOW);

	pushmatrix();
		translate(0.0, -RADIUS, -RADIUS);
		scale(0.12, 0.12, 0.12);
		callobj(SPHERE);
	popmatrix();

	color(BLUE);

	pushmatrix();
		translate(0.0, -2.0*RADIUS, -RADIUS);
		scale(0.3, 0.3, 0.3);
		callobj(SPHERE);
	popmatrix();

	getkey();

	vexit();
}
