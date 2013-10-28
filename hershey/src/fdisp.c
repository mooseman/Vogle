#include <stdio.h>
#include "vogle.h"

/*
 *	displays every character in a hershey font at 64 characters
 * per screen. Note: this program reads the binary format as created
 * by h2v.
 */
main(ac, av)
	int	ac;
	char	**av;
{
	char	dev[50];
	int	i, nchars;
	float	x, y;

	if (ac != 2) {
		fprintf(stderr, "fdisp: usage fdisp fontname\n");
		exit(1);
	}

	fprintf(stderr,"Enter device name: ");
	gets(dev);

	vinit(dev);
	color(BLACK);
	clear();

	color(GREEN);

	font(av[1]);

	nchars = numchars();

	textsize(0.2, 0.2);

	x = -0.94;
	y = 0.77;
	for (i = 0; i < nchars; i++) {
		move(x, y);
		drawchar(' ' + i);
		x += 0.25;
		if (x > 0.86) {
			y -= 0.25;
			if (y < -1.1) {
				getkey();
				color(BLACK);
				clear();
				color(GREEN);
				y = 0.77;
			}
			x = -0.94;
		}
	}

	getkey();

	vexit();
}

