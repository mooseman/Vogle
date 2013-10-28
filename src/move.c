#include "vogle.h"

/*
 * move
 *
 * Move the logical graphics position to the world coordinates x, y, z.
 *
 */
void
move(x, y, z)
	float 	x, y, z;
{
	Token	*p;
	Vector	vect, result;

	if (!vdevice.initialised) 
		verror("move: vogle not initialised");

	vdevice.cpW[V_X] = x;
	vdevice.cpW[V_Y] = y;
	vdevice.cpW[V_Z] = z;

	vdevice.cpVvalid = 0;

	if (vdevice.inpolygon) {
		(*vdevice.pmove)(x, y, z);
		return;
	}

	if (vdevice.inobject) {
		p = newtokens(4);

		p[0].i = MOVE;
		p[1].f = x;
		p[2].f = y;
		p[3].f = z;

		return;
	}

	if (vdevice.clipoff) {		/* update device coords as well */
		multvector(vdevice.cpWtrans, vdevice.cpW, vdevice.transmat->m);
		vdevice.cpVx = WtoVx(vdevice.cpWtrans);
		vdevice.cpVy = WtoVy(vdevice.cpWtrans);
	}
}

/*
 * move2
 *
 * Move the logical graphics position to the world coords x, y, 0.0
 * (I.e. a 2D move is defined as a 3D move with the Z-coord set to zero)
 *
 */
void
move2(x, y)
	float	x, y;
{
	if (!vdevice.initialised) 
		verror("move2: vogle not initialised");

	move(x, y, 0.0);
}

/*
 * rmove
 *
 * move the logical graphics position from the current world 
 * coordinates by dx, dy, dz 
 *
 */
void
rmove(dx, dy, dz)
	float	dx, dy, dz;
{
	if (!vdevice.initialised) 
		verror("rmove: vogle not initialised");

	move((vdevice.cpW[V_X] + dx), (vdevice.cpW[V_Y] + dy), (vdevice.cpW[V_Z] + dz));
}

/*
 * rmove2
 *
 * Move Relative in 2D.
 *
 */
void
rmove2(dx, dy)
	float	dx, dy;
{
	if (!vdevice.initialised) 
		verror("rmove2: vogle not initialised");

	move((vdevice.cpW[V_X] + dx), (vdevice.cpW[V_Y] + dy), 0.0);
}

/*
 * smove2
 *
 * Move directly as a fraction of the screen size.
 */
void
smove2(xs, ys)
	float 	xs, ys;
{
	if (!vdevice.initialised) 
		verror("smove2: vogle not initialised");

	vdevice.cpVx = (xs / 2 + 0.5) * (vdevice.maxVx - vdevice.minVx);
	vdevice.cpVy = (0.5 - ys / 2) * (vdevice.maxVy - vdevice.minVy);
}

/*
 * rsmove2
 *
 * Relative move as a fraction of the screen size.
 */
void
rsmove2(dxs, dys)
	float	dxs, dys;
{
	if (!vdevice.initialised) 
		verror("rsmove2: vogle not initialised");

	vdevice.cpVx += dxs / 2 * (vdevice.maxVx - vdevice.minVx);
	vdevice.cpVy += dys / 2 * (vdevice.maxVy - vdevice.minVy);
}
