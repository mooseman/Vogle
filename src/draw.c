#include "vogle.h"

/*
 * draw
 *
 * draw a line form the logical graphics position to the
 * the world coordinates x, y, z.
 *
 */
void
draw(x, y, z)
	float		x, y, z;
{
	Token	*tok;
	int	vx, vy;
	Vector	res;


	if (!vdevice.initialised)
		verror("draw: vogle not initialised");

	if (vdevice.inpolygon) {
		(*vdevice.pdraw)(x, y, z);

		vdevice.cpW[V_X] = x;
		vdevice.cpW[V_Y] = y;
		vdevice.cpW[V_Z] = z;

		vdevice.cpVvalid = 0;

		return;
	}

	if (vdevice.inobject) {
		tok = newtokens(4);

		tok[0].i = DRAW;
		tok[1].f = x;
		tok[2].f = y;
		tok[3].f = z;

		vdevice.cpW[V_X] = x;
		vdevice.cpW[V_Y] = y;
		vdevice.cpW[V_Z] = z;

		vdevice.cpVvalid = 0;

		return;
	}

	if (!vdevice.cpVvalid)
		multvector(vdevice.cpWtrans, vdevice.cpW, vdevice.transmat->m);

	vdevice.cpW[V_X] = x;
	vdevice.cpW[V_Y] = y;
	vdevice.cpW[V_Z] = z;
	multvector(res, vdevice.cpW, vdevice.transmat->m);

	if (vdevice.clipoff) {	
		vx = WtoVx(res);		/* just draw it */
		vy = WtoVy(res);
	 
		(*vdevice.dev.Vdraw)(vx, vy);

		vdevice.cpVx = vx;
		vdevice.cpVy = vy;

		vdevice.cpVvalid = 0;
	} else {
		if (vdevice.cpVvalid)
			quickclip(vdevice.cpWtrans, res);
		else
			clip(vdevice.cpWtrans, res);
	}

	vdevice.cpWtrans[V_X] = res[V_X];
	vdevice.cpWtrans[V_Y] = res[V_Y];
	vdevice.cpWtrans[V_Z] = res[V_Z];
	vdevice.cpWtrans[V_W] = res[V_W];
}


/*
 * draw2
 *
 * draw a line from the logical graphics position  to the
 * the world coordinates x, y.
 *
 */
void
draw2(x, y)
	float		x, y;
{
	if (!vdevice.initialised)
		verror("draw2: vogle not initialised");

	draw(x, y, 0.0);
}

/*
 * rdraw
 *
 * 3D relative draw from the logical graphics position by dx, dy, dz.
 *
 */
void
rdraw(dx, dy, dz)
	float		dx, dy, dz;
{
	if (!vdevice.initialised) 
		verror("rdraw: vogle not initialised");

	draw((vdevice.cpW[V_X] + dx), (vdevice.cpW[V_Y] + dy), (vdevice.cpW[V_Z] + dz));
}

/*
 * rdraw2
 *
 * 2D relative draw from the logical graphics position by dx, dy.
 *
 */
void
rdraw2(dx, dy)
	float		dx, dy;
{
	if (!vdevice.initialised) 
		verror("rdraw2: vogle not initialised");

	draw((vdevice.cpW[V_X] + dx), (vdevice.cpW[V_Y] + dy), 0.0);
}

/*
 * sdraw2
 *
 * Draw directly in proportion to screen coordinates.
 */
void
sdraw2(xs, ys)
	float 	xs, ys;
{
	int	nx, ny;

	if (!vdevice.initialised) 
		verror("sdraw2: vogle not initialised");

	nx = (xs / 2 + 0.5) * (vdevice.maxVx - vdevice.minVx);
	ny = (0.5 - ys / 2) * (vdevice.maxVy - vdevice.minVy);

	(*vdevice.dev.Vdraw)(nx, ny);

	vdevice.cpVx = nx;
	vdevice.cpVy = ny;
}

/*
 * rsdraw2
 *
 * Relative draw as a fraction of screen size.
 */
void
rsdraw2(dxs, dys)
	float	dxs, dys;
{
	int	ndx, ndy;

	if (!vdevice.initialised) 
		verror("rsdraw2: vogle not initialised");

	ndx = dxs * (vdevice.maxVx - vdevice.minVx) / 2;
	ndy = dys * (vdevice.maxVy - vdevice.minVy) / 2;

	(*vdevice.dev.Vdraw)(vdevice.cpVx + ndx, vdevice.cpVy + ndy);

	vdevice.cpVx += ndx;
	vdevice.cpVy += ndy;
}

