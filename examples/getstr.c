#include "vogle.h"
#include <stdio.h>

/*
 * Test the getting of strings in graphics mode.
 */

main(argc, argv)
	int	argc;
	char	**argv;
{
	char	device[10], *p;
	float	cw, ch;
	int	i, n;
	char	buf[10][128];

	fprintf(stderr,"Enter output device: ");
	gets(device);

	vinit(device);

	if (argc > 1)
		font(argv[1]);

	clipping(0);

	window(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	lookat(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0);

	textsize(0.1, 0.25);


	rotate(30.0, 'x');
	rotate(30.0, 'z');
	rotate(60.0, 'y');

	color(BLACK);
	clear();
	color(YELLOW);

	rect(-0.5, -0.5, 0.5, 0.5);
	move2(-0.5, 0.0);

	color(GREEN);

	n = 0;
	while ((i = getstring(BLACK, buf[n]) && n < 10))
		n++;

	vexit();

	for (i = 0; i < n; i++)
		printf("Line %d was: %s\n", i + 1, buf[i]);

}
