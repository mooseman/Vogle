#include <stdio.h>
#include "vogle.h"


#define		GEOM		1
#define		TOPLEFT		2
#define		TOPRIGHT	3
#define		BOTTOMLEFT	4
#define		BOTTOMRIGHT	5
#define		MIN(x, y)	((x) < (y) ? (x) : (y))
#define		MAX(x, y)	((x) > (y) ? (x) : (y))

typedef struct v {
	float	x, y, z;
} vertex;

static	char	title[128] = "G'day there mate";

FILE 	*fp;


/*
 * Demonstrate just how much you can put in an object
 * this program will read geometry files in the off format.
 */
main(argc, argv)
	int	argc;
	char	**argv;
{
	int	i, backface_on = 0, direction = 0;

	if (argc < 2) {
		fprintf(stderr,"Usage: %s [-b] [-a] filename\n", argv[0]);
		exit(1);
	}

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-b") == 0)
			backface_on = 1;
		if (strcmp(argv[i], "-a") == 0)
			direction = 1;
	}
		
	vinit(0);

	backface(backface_on);
	backfacedir(direction);

	font("times.r");
	textsize(0.3, 0.6);

	if (argc >= 2) {
		if ((fp = fopen(argv[2], "r")) == (FILE *)NULL) {
			vexit();
			fprintf(stderr, "Couldn't open %s for reading\n", argv[2]);
			exit(1);
		}
		makeobject();
	} else 
		makecube();

	color(BLACK);
	clear();

	/*
	 * set up an object which draws in the top left of the screen.
	 */
	makeobj(TOPLEFT);
		viewport(-1.0, 0.0, 0.0, 1.0);
		ortho2(-5.0, 5.0, -5.0, 5.0);

		color(RED);

		rect(-5.0, -5.0, 5.0, 5.0);
		move2(-4.8, -4.8);
		color(WHITE);
		drawstr(title);

		perspective(50.0, 1.0, 0.1, 1000.0);
		lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0);

		color(RED);
		callobj(GEOM);

	closeobj();

	/*
	 * now set up one which draws in the top right of the screen
	 */
	makeobj(TOPRIGHT);
		viewport(0.0, 1.0, 0.0, 1.0);
		ortho2(-5.0, 5.0, -5.0, 5.0);

		color(GREEN);

		rect(-5.0, -5.0, 5.0, 5.0);
		move2(-4.8, -4.8);
		color(WHITE);
		drawstr(title);

		window(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
		lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 90.0);

		color(GREEN);
		callobj(GEOM);

		color(RED);

	closeobj();

	/*
	 * try the bottom left
	 */
	makeobj(BOTTOMLEFT);
		viewport(-1.0, 0.0, -1.0, 0.0);
		ortho2(-5.0, 5.0, -5.0, 5.0);

		color(MAGENTA);

		rect(-5.0, -5.0, 5.0, 5.0);
		move2(-4.8, -4.8);
		color(WHITE);
		drawstr(title);

		perspective(40.0, 1.0, 0.1, 1000.0);
		polarview(15.0, 30.0, 30.0, 30.0);

		color(MAGENTA);
		callobj(GEOM);

		color(YELLOW);

	closeobj();

	/*
	 * and the bottom right
	 */
	makeobj(BOTTOMRIGHT);
		viewport(0.0, 1.0, -1.0, 0.0);
		ortho2(-5.0, 5.0, -5.0, 5.0);

		color(CYAN);

		rect(-5.0, -5.0, 5.0, 5.0);
		move2(-4.8, -4.8);
		color(WHITE);
		drawstr(title);

		window(-6.0, 6.0, -6.0, 6.0, -6.0, 6.0);
		polarview(18.0, -38.0, -19.0, 18.0);

		color(CYAN);
		callobj(GEOM);

		color(BLUE);

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
 * makeobject
 *
 *	read in and set up set up the object
 */
makeobject()
{
	float		fmax, fmin;
	int		i, j, verts, connections, edges, npoints, pointno;
	vertex		*vlist;

	makeobj(GEOM);

		if (fscanf(fp, "%d %d %d\n", &verts, &connections, &edges) != 3)
			read_err("nverts npoly nedges");

		vlist = (vertex *)malloc(sizeof(vertex) * verts);

		fmax = -1.0e20;
		fmin = 1.0e20;

		for (i = 0; i != verts; i++) {
			if (fscanf(fp, "%f %f %f\n", &vlist[i].x, &vlist[i].y, &vlist[i].z) != 3)
				read_err("coodinate information");

			fmin = MIN(fmin, vlist[i].x);
			fmin = MIN(fmin, vlist[i].y);
			fmin = MIN(fmin, vlist[i].z);

			fmax = MAX(fmax, vlist[i].x);
			fmax = MAX(fmax, vlist[i].y);
			fmax = MAX(fmax, vlist[i].z);
		}

		/* 
		 * Scale the object.
		 */
		fmax = fmax - fmin;
		scale(6.0 / fmax, 6.0 / fmax, 6.0 / fmax);

		for (i = 0; i != connections; i++) {
			if (fscanf(fp, "%d", &npoints) != 1)
				read_err("connectivity 1");

			makepoly();
				if (fscanf(fp, "%d", &pointno) != 1)
					read_err("connectivity 2");

				pointno--;
				move(vlist[pointno].x, vlist[pointno].y, vlist[pointno].z);
				for (j = 1; j != npoints; j++) {
					if (fscanf(fp, "%d", &pointno) != 1)
						read_err("connectivity 3");

					pointno--;
					draw(vlist[pointno].x, vlist[pointno].y, vlist[pointno].z);
				}
			closepoly();
		}

	closeobj();
}

/*
 * makecube
 *
 *	set up a cube
 */
makecube()
{

	makeobj(GEOM);

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

		move2(-4.5, -4.5);
		drawstr(title);
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


read_err(s)
	char *s;
{
	vexit();
	fprintf(stderr,"Error reading input file near %s\n", s);
	exit(1);
}
