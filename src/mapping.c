#include "vogle.h"

static	float	Vcx, Vcy, Vsx, Vsy;
static	Matrix	msave;

/*
 * VtoWxy
 *
 * Return the world x and y values corresponding to the input
 * screen x and y values.
 */
void
VtoWxy(xs, ys, xw, yw)
	float	xs, ys;
	float	*xw, *yw;
{
	float	a1, a2, b1, b2, c1, c2, A, B;

	A = (xs - Vcx) / Vsx;
	B = (ys - Vcy) / Vsy;

	a1 = msave[0][0] - msave[0][3] * A;
	a2 = msave[0][1] - msave[0][3] * B;

	b1 = msave[1][0] - msave[1][3] * A;
	b2 = msave[1][1] - msave[1][3] * B;

	c1 = msave[3][3] * A - msave[3][0];
	c2 = msave[3][3] * B - msave[3][1];

	*xw = (b1 * c2 - c1 * b2) / (a2 * b1 - b2 * a1);
	*yw = (a1 * c2 - c1 * a2) / (a1 * b2 - b1 * a2);
}

/*
 * _mapmsave
 *
 * saves the current transformation matrix as loaded by "loadmatrix" and
 * before and other transformations (ie rotation and scaling) are
 * concatenated with it.
 */
void
_mapmsave(m)
	Matrix	m;
{
	copymatrix(msave, m);
}

/*
 * calcW2Vcoeffs
 *
 *	Calculate the linear coeffs defining the mapping of world
 *	space to actual device space
 */
void
CalcW2Vcoeffs()
{
	Vcx = (float)(vdevice.maxVx + vdevice.minVx) * 0.5;
	Vcy = (float)(vdevice.maxVy + vdevice.minVy) * 0.5;

	Vsx = (float)(vdevice.maxVx - vdevice.minVx) * 0.5;
	Vsy = (float)(vdevice.maxVy - vdevice.minVy) * 0.5;
}

/*
 * WtoVx
 *
 * return the Screen X coordinate corresponding to world point 'p' 
 * (does the perspective division as well)
 */
int
WtoVx(p)
	float	p[];
{
	return((int)(p[0] * Vsx / p[3] + Vcx + 0.5));
}

/*
 * WtoVy
 *
 * return the Screen Y coordinate corresponding to world point 'p' 
 * (does the perspective division as well)
 */
int
WtoVy(p)
	float	p[];
{
	return((int)(p[1] * Vsy / p[3] + Vcy + 0.5));
}


