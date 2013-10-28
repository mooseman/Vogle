#include <stdio.h>
#include "vogle.h"

/*
 * drawgrid
 *
 *	draw a grid in the middle of the screen
 */
drawgrid()
{
	float	x;
	int	i;

	color(GREEN);

	rect(0.1, 0.4, 0.9, 0.6);

	x = 0.2;
	for (i = 0; i < 8; i++) {
		move2(x, 0.4);
		draw2(x, 0.6);
		x += 0.1;
	}
	move2(0.1, 0.5);
	draw2(0.9, 0.5);

	color(YELLOW);
}

/*
 * demonstrate some more features of text
 */
main(argc, argv)
	int	argc;
	char	**argv;
{
	char	dev[20];
	int	i;
	float	x;
	
	fprintf(stderr, "Enter device: ");
	gets(dev);

	vinit(dev);

	if (argc == 2)
		font(argv[1]);

	ortho2(0.0, 1.0, 0.0, 1.0);

	drawgrid();

	/*
	 * show some scaled text on the grid (In the bottom part)
	 */
	boxtext(0.1, 0.4, 0.8, 0.1, "{This is Some text] | $");

	getkey();

	color(BLACK);
	clear();

	drawgrid();

	/*
	 * centertext causes text to be centered around the current graphics
	 * position this is especially usefull if you want your text to come
	 * out centered on a line, or a character to be centered on a point
	 * in a graph. A non-zero argument turns centertext on.
	 *
	 * show a string centered on the center line
	 */
	centertext(1);

	boxtext(0.5, 0.5, 0.8, 0.1, "{This is Some Centered text] | $");

	/*
	 * turn centertext off. We use an argument with the value zero.
	 */
	centertext(0);

	getkey();

	color(BLACK);
	clear();

	/*
	 * rotate the grid so that it is the same angle as the text after
	 * textang for text ang.
	 */
	pushmatrix();
		translate(0.5, 0.5, 0.0);
		rotate(90.0, 'z');
		translate(-0.5, -0.5, 0.0);

		drawgrid();
	popmatrix();

	/*
	 * turn on centered text again
	 */
	centertext(1);

	/*
	 * set the angle to 90.
	 */
	textang(90.0);

	/*
	 * draw the string
	 */
	boxtext(0.5, 0.5, 0.8, 0.1, "{This is Some Rotated Centered text] | $");

	/*
	 * turn off center text
	 */
	centertext(0);

	/*
	 * set text angle back to 90
	 */
	textang(0.0);

	getkey();

	color(BLACK);
	clear();

	drawgrid();

	/*
	 * as all the software fonts are proportionally spaced we use
	 * the fixedwidth call to make each character take the same amount
	 * of horizontal space. As with centertext this is done by passing
	 * fixedwidth a non-zero argument.
	 */
	fixedwidth(1);

	boxtext(0.1, 0.5, 0.8, 0.1, "{This is Some Fixedwidth text] | $");

	getkey();

	color(BLACK);
	clear();

	drawgrid();

	/*
	 * now try centered and fixewidth at the same time
	 */
	centertext(1);

	move2(0.5, 0.5);
	drawstr("{This is Some Cent.Fixedwidth text] | $");

	centertext(0);
	
	getkey();
	color(BLACK);
	clear();

	drawgrid();

	/*
	 * scale the text so tha a character is the size of a box in
	 * the grid.
	 */
	boxfit(0.8, 0.1, 8);

	/*
	 * draw the two strings fixedwidth (it is still turned on)
	 */
	move2(0.1, 0.4);
	drawstr("ABCDefgh");

	move2(0.1, 0.5);
	drawstr("IJKLmnop");

	getkey();

	vexit();
}
