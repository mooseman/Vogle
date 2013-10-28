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

#define RADIUS	10.0
#define	SPHERE	1

/*
 * most of the things in this program have been done before but it has
 * a certain novelty value.
 */
main()
{
	char	dev[20];
	int	i;
	float	r, z, a;

	fprintf(stderr,"Enter device: ");
	gets(dev);

	vinit(dev);
	vdevice.clipoff = 1;

	font("futura.m");

	perspective(80.0, 1.0, 0.001, 50.0);
	lookat(13.0, 13.0, 8.0, 0.0, 0.0, 0.0, 0.0);

	color(BLACK);
	clear();

	makesphere();

	/*
	 * draw the main one in cyan
	 */
	color(CYAN);

	callobj(SPHERE);

	/*
	 * draw a smaller one outside the main one in white
	 */
	color(WHITE);

	pushmatrix();
		translate(0.0, -1.4 * RADIUS, 1.4 * RADIUS);
		scale(0.3, 0.3, 0.3);
		callobj(SPHERE);
	popmatrix();

	/*
	 * scale the text
	 */
	boxfit(2.0 * PI * RADIUS, 0.25 * RADIUS, 31);

	/*
	 * now write the text in rings around the main sphere
	 */

	color(GREEN);
	showroundtext("Around the world in eighty days ");

	color(BLUE);
	/*
	 * note: that software text is rotated here as
	 * anything else would be whether you use textang
	 * or rotate depends on what you are trying to do.
	 * Experience is the best teacher here.
	 */
	rotate(90.0, 'x');
	showroundtext("Around the world in eighty days ");

	color(RED);
	rotate(90.0, 'z');
	showroundtext("Around the world in eighty days ");

	getkey();

	vexit();
}

/*
 * showroundtext
 *
 *	draw string str wrapped around a circle in 3d
 */
showroundtext(str)
	char	*str;
{
	float	i, inc;

	inc = 360.0 / (float)strlen(str);

	for (i = 0; i < 360.0; i += inc) {
		pushmatrix();
			/*
			 * find the spot on the edge of the sphere
			 * by making it (0, 0, 0) in world coordinates
			 */
			rotate(i, 'y');
			translate(0.0, 0.0, RADIUS);

			move(0.0, 0.0, 0.0);

			drawchar(*str++);
		popmatrix();
	}
}

/*
 * makesphere
 *
 *	create the sphere object
 */
makesphere()
{
	float	i, r, z, a;

	makeobj(SPHERE);

		for (i = 0; i < 180; i += 20) {
			pushmatrix();
				rotate(i, 'y');
				circle(0.0, 0.0, RADIUS);
			popmatrix();
		}
		
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
