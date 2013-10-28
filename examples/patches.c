
#include <stdio.h>
#include "vogle.h"

/*
 *	Draws patches of various bases
 */

/*
 * patch basis types
 */

Matrix	bezier = {
	{-1.0,	3.0,	-3.0,	1.0},
	{3.0,	-6.0,	3.0,	0.0},
	{-3.0,	3.0,	0.0,	0.0},
	{1.0,	0.0,	0.0,	0.0} 
};

Matrix	cardinal = { /* Or catmull-rom */
	{-0.5,	1.5,	-1.5,	0.5},
	{1.0,	-2.5,	2.0,	-0.5},
	{-0.5,	0.0,	0.5,	0.0},
	{0.0,	1.0,	0.0,	0.0}
};

Matrix	bspline = {
	{-1.0 / 6.0,	3.0 / 6.0,	-3.0 / 6.0,	1.0 / 6.0},
	{3.0 / 6.0,	-6.0 / 6.0,	3.0 / 6.0,	0.0},
	{-3.0 / 6.0,	0.0,		3.0 / 6.0,	0.0},
	{1.0 / 6.0,	4.0 / 6.0,	1.0 / 6.0,	0.0}    
};

Matrix	power = {
	{1.0, 0.0, 0.0, 0.0},
	{0.0, 1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0, 1.0}
};

float *basis[] = {	(float *)bezier,
			(float *)cardinal,
			(float *)bspline,
			(float *)power
		};

Matrix	x1 = {
	{0.0,   0.2588,   0.5,   0.7071},
	{0.0,   0.51764,  1.0,   1.4142},
	{0.0,   0.51764,  1.0,   1.4142},
	{0.0,   0.2588,   0.5,   0.7071}
};

Matrix	y1 = {
	{1.0,   0.966,   0.866,  0.7071},
	{2.0,   1.9318,  1.732,  1.4142},
	{2.0,   1.9318,  1.732,  1.4142},
	{1.0,   0.966,   0.866,  0.7071}
};

Matrix	z1 = {
	{1.0,   1.0,     1.0,    1.0},
	{1.0,   1.0,     1.0,    1.0},
	{0.0,   0.0,     0.0,    0.0},
	{0.0,   0.0,     0.0,    0.0}
};

Matrix	x2 = {
	{0.7071, 0.8660, 0.9660, 1.0},
	{1.4142, 1.7320, 1.932,  2.0},
	{1.4142, 1.7320, 1.932,  2.0},
	{0.7071, 0.8660, 0.9660, 1.0}
};

Matrix	y2 = {
	{0.7071, 0.5,    0.2588, 0.0},
	{1.4142, 1.0,    0.5176, 0.0},
	{1.4142, 1.0,    0.5176, 0.0},
	{0.7071, 0.5,    0.2588, 0.0}
};

Matrix	z2 = {
	{1.0,   1.0,     1.0,    1.0},
	{1.0,   1.0,     1.0,    1.0},
	{0.0,   0.0,     0.0,    0.0},
	{0.0,   0.0,     0.0,    0.0}
};

char *labels[] = {
		"Bezier Patch(es)",
		"Cardinal Patch(es)",
		"B-Spline Patch(es)",
		"'Power' Patch(es)"
		};

/*
 * demonstrate patches
 */

main()
{
	char	dev[20];
	int	i;

	fprintf(stderr,"Enter device: ");
	gets(dev);

	vinit(dev);

	color(BLACK);
	clear();

	/*
	 * Set up two viewports (They actually overlap)
	 */

	viewport(-1.0, 0.3, -1.0, 0.3);
	ortho(-2.0, 5.0, -2.0, 5.0, -2.0, 5.0);
	lookat(0.0, 0.0, 0.0, -3.0, 2.0, -4.0, 0.0);
	/*
	 * Save it 
	 */
	pushviewport();
	pushmatrix();

	viewport(-0.3, 1.0, -0.3, 1.0);
	ortho(-2.0, 5.0, -2.0, 5.0, -2.0, 5.0);
	lookat(0.0, 0.0, 0.0, 3.0, 2.0, -4.0, 0.0);

	textsize(0.4, 0.4);

	/*
	 * patchcurves provides a number of curves in the t and u
	 * directions. patchprecision gives the minimum number of line
	 * segments making up the curves in the t and u directions. The
	 * actual number of linesegments in t or u is equal to the closest
	 * integer multiple of the number of curves, > nsegs, in t or u,
	 * greater than or equal to the number set by patchprecision in u or
	 * t. eg. curves in t will be made up of 21 line segments so that we
	 * can match up the 7 curves in u; curves in u will have 24 as 4 by 5
	 * gives 20.
	 */
	patchcurves(4, 7);
	patchprecision(20, 20);

	for (i = 0; i < 4; i++) {

		axes();


		/*
		 * patchbasis sets the basis matrices for the t and u
		 * functions
		 * 
		 */
		patchbasis(basis[i], basis[i]);

		/* 
		 * Draw with viewport 2
		 */
		move(0.0, 4.0, 0.0);
		drawstr(labels[i]);

		/*
		 * now draw the patches according to the geometry matrices in
		 * x1, y1, and z1, x2, y2, z2.
		 */
		drawhull(x1, y1, z1);
		patch(x1, y1, z1);

		drawhull(x2, y2, z2);
		patch(x2, y2, z2);

		getkey();

		/*
		 * Now with viewport 1
		 */
		popviewport();
		popmatrix();

		axes();

		move(0.0, 4.0, 0.0);
		drawstr(labels[i]);

		/*
		 * now draw the patches according to the geometry matrices in
		 * x1, y1, and z1, x2, y2, z2.
		 */
		drawhull(x1, y1, z1);
		patch(x1, y1, z1);

		drawhull(x2, y2, z2);
		patch(x2, y2, z2);

		getkey();

		/*
		 * Save viewport 1 again and reset to viewport 2
		 */
		pushviewport();
		pushmatrix();

		viewport(-0.3, 1.0, -0.3, 1.0);
		ortho(-1.5, 5.0, -1.5, 5.0, -1.5, 5.0);
		lookat(0.0, 0.0, 0.0, 3.0, 2.0, -4.0, 0.0);

		color(BLACK);
		clear();
	}

	vexit();
}

/*
 * drawhull
 *
 *	draw the hull for x, y, and z.
 */
drawhull(x, y, z)
	Matrix	x, y, z;
{
	int	i, j;
	char	buf[2];

	color(MAGENTA);	

	for (i = 0; i < 4; i++) {
		move(x[i][0], y[i][0], z[i][0]);
		for (j = 1; j < 4; j++)
			draw(x[i][j], y[i][j], z[i][j]);
	}

	for (i = 0; i < 4; i++) {
		move(x[0][i], y[0][i], z[0][i]);
		for (j = 1; j < 4; j++) 
			draw(x[j][i], y[j][i], z[j][i]);
	}

	/* 
 	 * Set color for The patch
	 */
	color(GREEN);
}

/*
 * axes
 *
 *	draw the axes
 */

axes()
{
	color(YELLOW);
	move(0.0, 0.0, 0.0);
	draw(4.0, 0.0, 0.0);

	move(0.0, 0.0, 0.0);
	draw(0.0, 4.0, 0.0);

	move(0.0, 0.0, 0.0);
	draw(0.0, 0.0, 4.0);
}
