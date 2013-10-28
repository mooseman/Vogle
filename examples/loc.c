#include <stdio.h>
#include "vogle.h"

/*
 * a routine to demonstrate using locator.
 */
main()
{
	char	dev[50], name[50];
	int	i, bt, curpnt, act, nchars;
	float	x, y, sx, sy;

	fprintf(stderr,"Enter device name: ");
	gets(dev);

	vinit(dev);

	color(BLACK);
	clear();

	color(BLUE);

	/*
	 * draw some axes
	 */
	move2(0.0, 1.0);
	draw2(0.0, -1.0);

	move2(1.0, 0.0);
	draw2(-1.0, 0.0);

	color(GREEN);

	act = 0;
	curpnt = 0;
	/*
	 * locator returns whether a mouse button has been
	 * pressed or not. In a device such as the tektronix
	 * where you have to wait for a keypress to get the
	 * position of the crosshairs locator returns 0
	 * automatically on every second call. A return value
	 * of 2 indicates the second mouse button has been pressed.
	 * A return value of 1 indicates the first mouse button has
	 * been pressed. We wait for the locator to return zero so
	 * that we know the mouse button has been released.
	 */
	while((bt = locator(&x, &y)) != 2) {
		if (bt == -1) {
			vexit();
			printf("No locator device found\n");
			exit(0);
		} else if (bt == 0) {
			act = 1;
		} else if (act) {
			act = 0;
			if (bt == 1) {
				if (curpnt) {
					move2(sx, sy);
					draw2(x, y);
					curpnt = 0;
				} else
					curpnt = 1;
				sx = x;
				sy = y;
			}
		}
	}

	vexit();

}
