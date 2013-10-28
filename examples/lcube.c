
#include <stdio.h>
#include <vogle.h>

#define	CUBE_SIZE	200.0
#define	TRANS		20.0

main()
{
        char    device[10], *p;
	float	x, y, tdir = TRANS;
	int	but, nplanes;
	int	i, n;
	char	buf[10][128];

	fprintf(stderr,"Enter output device: ");
	gets(device);

	prefposition(50, 50);

	vinit(device);

	window(-800.0, 800.0, -800.0, 800.0, -800.0, 800.0);
	lookat(0.0, 0.0, 1500.0, 0.0, 0.0, 0.0, 0.0);


	makeobj(1);
		makepoly();
			rect(-CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
		closepoly();
	closeobj();

	if ((nplanes = getdepth()) == 1)
		makecubes(0);

	makecubes(1);

	backface(1);
		
	if (backbuffer() < 0) {
		vexit();
		fprintf(stderr, "lcube: device doesn't support double buffering.\n"); 
		exit(0); 
	}        

	while((but = slocator(&x, &y)) != 44) {
		pushmatrix();
			rotate(100.0 * x, 'y');
			rotate(100.0 * y, 'x');
			color(BLACK);
			clear();
			callobj(3);
			if (nplanes == 1)
				callobj(2);
		popmatrix();
		swapbuffers();

		switch (but = checkkey()) {
		case 'x':
			translate(tdir, 0.0, 0.0);
			break;
		case 'y':
			translate(0.0, tdir, 0.0);
			break;
		case 'z':
			translate(0.0, 0.0, tdir);
			break;
		case '-':
			tdir = -tdir;
			break;
		case '+':
			tdir = TRANS;
			break;
		case 27: /* ESC */
		case 'q':
			vexit();
			exit(0);
		default:
			;
		}
	}

	vexit();
}

makecubes(fill)
	int	fill;
{
	makeobj(fill + 2);
		polyfill(fill);
		if (!fill)
			color(BLACK);

		pushmatrix();
			translate(0.0, 0.0, CUBE_SIZE);
			if (fill)
				color(RED);
			callobj(1);
		popmatrix();

		pushmatrix();
			translate(CUBE_SIZE, 0.0, 0.0);
			rotate(90.0, 'y');
			if (fill)
				color(GREEN);
			callobj(1);
		popmatrix();

		pushmatrix();
			translate(0.0, 0.0, -CUBE_SIZE);
			rotate(180.0, 'y');
			if (fill)
				color(BLUE);
			callobj(1);
		popmatrix();

		pushmatrix();
			translate(-CUBE_SIZE, 0.0, 0.0);
			rotate(-90.0, 'y');
			if (fill)
				color(CYAN);
			callobj(1);
		popmatrix();

		pushmatrix();
			translate(0.0, CUBE_SIZE, 0.0);
			rotate(-90.0, 'x');
			if (fill)
				color(MAGENTA);
			callobj(1);
		popmatrix();

		pushmatrix();
			translate(0.0, -CUBE_SIZE, 0.0);
			rotate(90.0, 'x');
			if (fill)
				color(YELLOW);
			callobj(1);
		popmatrix();

	closeobj();
}
