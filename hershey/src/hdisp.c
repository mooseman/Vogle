#include <stdio.h>
#include "vogle.h"

extern int	getcharacter();

#define	XCOORD(x)	((x) - 'R')
#define	YCOORD(y)	('R' - (y))	/* invert as in tv coords */

/*
 * newpage
 *
 *	draw up a new page with title, boxes, etc..
 */
newpage(fname, pageno)
	char	*fname;
	int	pageno;
{
	char	str[100];

	centertext(0);

	textsize(0.07, 0.07);

	move2(-0.91, 0.9);
	drawstr("Hershey Character File: ");
	drawstr(fname);

	move2(0.45, 0.9);
	sprintf(str, "Page No: %d", pageno);
	drawstr(str);

	textsize(0.03, 0.03);

	centertext(1);
}

/*
 * display the hershey data set in the input file.
 */
main(ac, av)
	int	ac;
	char	**av;
{
	FILE	*fp;
	int	charno, numpairs, page;
	char    c, device[20], buf[1000], *p, str[100];
	float	x, y, ox, oy;

	if (ac < 2) {
		fprintf(stderr, "hdisp: usage hdisp datafile\n");
		exit(1);
	}

	if ((fp = fopen(av[1], "r")) == NULL) {
		fprintf(stderr, "hdisp: unable to open file %s\n", av[1]);
		exit(1);
	}

	fprintf(stderr,"Enter device name: ");
	gets(device);

	vinit(device);

	color(BLACK);
	clear();

	ox = -0.8;
	oy = 0.75;

	page = 1;

	color(WHITE);

	newpage(av[1], page);

	while (getcharacter(fp, &charno, &numpairs, buf)) {

		if (buf[2] != 0) {
			p = &buf[2];		/* skip the width bytes */

			x = XCOORD(*p++) / 280.0;
			y = YCOORD(*p++) / 280.0;
			move2(ox + x, oy + y);

			while (*p != 0) {
				if (*p == ' ') {
					p += 2;
					x = XCOORD(*p++) / 280.0;
					y = YCOORD(*p++) / 280.0;
					move2(ox + x, oy + y);
				} else {
					x = XCOORD(*p++) / 280.0;
					y = YCOORD(*p++) / 280.0;
					draw2(ox + x, oy + y);
				}
			}
		}

		move2(ox, oy - 0.11);
		sprintf(str, "(%d)", charno);
		drawstr(str);

		ox += 0.22;
		if (ox > 0.9) {
			oy -= 0.22;
			ox = -0.8;
		}
		if (oy < -0.9) {
			oy = 0.75;
			getkey();

			color(BLACK);
			clear();

			color(WHITE);

			newpage(av[1], ++page);
		}
	}

	getkey();

	vexit();
}
