#include "vogle.h"

static int	nsegs = 15;		/* number of segs in a curve */
static Matrix	basismatrix;
static Matrix	e;			/* The curve precision matrix */

void 	drcurve();

/*
 * curvebasis
 *
 *	sets the basis type of curves.
 *
 */
void
curvebasis(basis)
	Matrix	basis;
{
	copymatrix(basismatrix, basis);
}

/*
 * curveprecision
 *
 *	sets the number of line segments that make up a curve segment.
 *
 */
void
curveprecision(nsegments)
	int		nsegments;
{
	float	n2, n3;

	if (nsegments > 0)
		nsegs = nsegments;
	else
		verror("curveprecision: number of segments <= 0");

	/*
	 * Set up the difference matrix.
	 */
	identmatrix(e);
	n2 = (float)(nsegs * nsegs);
	n3 = (float)(nsegs * n2);

	e[0][0] = e[2][2] = e[3][3] = 0.0;
	e[1][0] = 1.0 / n3;
	e[1][1] = 1.0 / n2;
	e[2][0] = e[3][0] = 6.0 / n3;
	e[2][1] = 2.0 / n2;
	e[1][2] = 1.0 / (float)nsegs;
	e[0][3] = 1.0;
}

/*
 * rcurve
 *
 *	draws a rational curve
 *
 */
void
rcurve(geom)
	Matrix	geom;
{
	Matrix	d, tmp;
	float	*m, xlast, ylast, zlast;
	Token	*tok;
	int	i;
	
	if (!vdevice.initialised)
		verror("rcurve: vogle not initialised");


	mult4x4(d, basismatrix, geom);

	/*
	 * Find the last point on the curve....
	 */
	xlast = d[0][0] + d[1][0] + d[2][0] + d[3][0];
	ylast = d[0][1] + d[1][1] + d[2][1] + d[3][1];
	zlast = d[0][2] + d[1][2] + d[2][2] + d[3][2];

	/*
	 * Mult. by the precision matrix....
	 */
	mult4x4(tmp, e, d);

	if (vdevice.inobject) {
		tok = newtokens(21);

		tok[0].i = RCURVE;
		(++tok)->i = nsegs;
		(++tok)->f = xlast;
		(++tok)->f = ylast;
		(++tok)->f = zlast;
		m = (float *)tmp;
		for (i = 0; i < 16; i++)
			(++tok)->f = *m++;

		return;
	}

	/*
	 * Multiply by the current transformation matrix.
	 */
	mult4x4(d, tmp, vdevice.transmat->m);

	/*
	 * Draw the curve.....
	 */
	drcurve(nsegs, d);
	/*
	 * Set the current world position to the last point (This
	 * is the untransformed one)
	 */
	vdevice.cpW[V_X] = xlast;
	vdevice.cpW[V_Y] = ylast;
	vdevice.cpW[V_Z] = zlast;
}

/*
 * curve
 *
 *	draws a curve
 *
 */
void
curve(geom)
	float	geom[4][3];
{
	Matrix	tmp;
	int	i, j;

	if (!vdevice.initialised)
		verror("curve: vogle not initialised");

	/*
	 * Fill in the w column for rcurve
	 */
	for (i = 0; i < 4; i++) {
		tmp[i][3] = 1.0;
		for (j = 0; j < 3; j++) 
			tmp[i][j] = geom[i][j];
	}

	rcurve(tmp);
}

/*
 *  drcurve
 *
 *	Iterate a forward difference matrix to draw a curve.
 *	Also bypasses the normal multiplication by the current
 *      transformation matrix (ie. goes straight to clip).
 */
void
drcurve(n, r)
	int	n;
	Matrix	r;
{
	int	it, vx, vy;

	vdevice.cpVvalid = 0;		/* we start loop with a "move" */
	if (vdevice.clipoff) {
		vdevice.cpVx = WtoVx(r[0]);		
		vdevice.cpVy = WtoVy(r[0]);		
	}

	for (it = 0; it < n; it++) {
		vdevice.cpWtrans[V_X] = r[0][V_X];
		vdevice.cpWtrans[V_Y] = r[0][V_Y];
		vdevice.cpWtrans[V_Z] = r[0][V_Z];
		vdevice.cpWtrans[V_W] = r[0][V_W];

		/* These loops now unwound ....
		 * for (i = 0; i < 4; i++)
		 *	for (j = 0; j < 3; j++)
		 *		r[j][i] += r[j+1][i];
		 */

		r[0][0] += r[1][0];
		r[1][0] += r[2][0];
		r[2][0] += r[3][0];

		r[0][1] += r[1][1];
		r[1][1] += r[2][1];
		r[2][1] += r[3][1];

		r[0][2] += r[1][2];
		r[1][2] += r[2][2];
		r[2][2] += r[3][2];

		r[0][3] += r[1][3];
		r[1][3] += r[2][3];
		r[2][3] += r[3][3];

		if (vdevice.clipoff) {	
			vx = WtoVx(r[0]);		/* just draw it */
			vy = WtoVy(r[0]);
		 
			(*vdevice.dev.Vdraw)(vx, vy);

			vdevice.cpVx = vx;
			vdevice.cpVy = vy;

			vdevice.cpVvalid = 0;
		} else {
			if (vdevice.cpVvalid)
				quickclip(vdevice.cpWtrans, r[0]);
			else
				clip(vdevice.cpWtrans, r[0]);
		}
	}

	vdevice.cpWtrans[V_X] = r[0][V_X];
	vdevice.cpWtrans[V_Y] = r[0][V_Y];
	vdevice.cpWtrans[V_Z] = r[0][V_Z];
	vdevice.cpWtrans[V_W] = r[0][V_W];

	/*
	 * must set current world position here - clip or quickclip will have
	 * set valid to the approriate value.
	 */
}

/*
 * curven
 *
 *	draws a series of curve segments.
 *
 */
void
curven(n, geom)
	float	geom[][3];
	int	n;
{
	int	i;

	if (!vdevice.initialised)
		verror("curven: vogle not initialised");

	if (n < 4)
		verror("curven: not enough points in geometry matrix");

	for (i = 0; i <= n - 4; i++)
		curve(&geom[i][0]);
}

