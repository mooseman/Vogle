#include <stdio.h>
#include "vogle.h"


#define		CUBE		1
#define		TOPLEFT		2
#define		TOPRIGHT	3
#define		BOTTOMLEFT	4
#define		BOTTOMRIGHT	5

/*
 * Demonstrate just how much you can put in an object
 */
main()
{
	char device[20];

	fprintf(stderr,"Enter device name: ");
	gets(device);
	vinit(device);
	pushviewport();

	textsize(0.5, 0.9);
	font("futura.m");

	color(BLACK);
	clear();

	makecube();

	/*
	 * set up an object which draws in the top left of the screen.
	 */
	makeobj(TOPLEFT);
		viewport(-1.0, 0.0, 0.0, 1.0);
		ortho2(-5.0, 5.0, -5.0, 5.0);

		color(RED);

		rect(-5.0, -5.0, 5.0, 5.0);

		perspective(40.0, 1.0, 0.1, 1000.0);
		lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0);

		callobj(CUBE);

		color(GREEN);

		move2(-4.5, -4.5);
		drawstr("perspective/lookat");
	closeobj();

	/*
	 * now set up one which draws in the top right of the screen
	 */
	makeobj(TOPRIGHT);
		viewport(0.0, 1.0, 0.0, 1.0);
		ortho2(-5.0, 5.0, -5.0, 5.0);

		color(GREEN);

		rect(-5.0, -5.0, 5.0, 5.0);

		window(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
		lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0);

		callobj(CUBE);

		color(RED);

		move2(-4.5, -4.5);
		drawstr("window/lookat");
	closeobj();

	/*
	 * try the bottom left
	 */
	makeobj(BOTTOMLEFT);
		viewport(-1.0, 0.0, -1.0, 0.0);
		ortho2(-5.0, 5.0, -5.0, 5.0);

		color(MAGENTA);

		rect(-5.0, -5.0, 5.0, 5.0);

		perspective(40.0, 1.0, 0.1, 1000.0);
		polarview(15.0, 30.0, 30.0, 30.0);

		callobj(CUBE);

		color(YELLOW);

		move2(-4.5, -4.5);
		drawstr("perspective/polarview");
	closeobj();

	/*
	 * and the bottom right
	 */
	makeobj(BOTTOMRIGHT);
		viewport(0.0, 1.0, -1.0, 0.0);
		ortho2(-5.0, 5.0, -5.0, 5.0);

		color(CYAN);

		rect(-5.0, -5.0, 5.0, 5.0);

		window(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
		polarview(8.0, -18.0, -3.0, 18.0);

		callobj(CUBE);

		color(BLUE);

		move2(-4.5, -4.5);
		drawstr("window/polarview");
	closeobj();

	/*
	 * now draw them
	 */
	callobj(TOPLEFT);
	callobj(TOPRIGHT);
	callobj(BOTTOMLEFT);
	callobj(BOTTOMRIGHT);

	getkey();

	vexit();
}

/*
 * makecube
 *
 *	set up a cube
 */
makecube()
{

	makeobj(CUBE);

		/*
		 * The border around the cube
		 */
		rect(-5.0, -5.0, 10.0, 10.0);

		/*
		 * Make the cube from 4 squares
		 */
		pushmatrix();
			side();
			rotate(90.0, 'x');
			side();
			rotate(90.0, 'x');
			side();
			rotate(90.0, 'x');
			side();
		popmatrix();

	closeobj();
}

/*
 * side
 *
 *	define a face for the cube
 */
side()
{
	pushmatrix();
		translate(0.0, 0.0, 1.0);
		rect(-1.0, -1.0, 1.0, 1.0);
	popmatrix();
}

