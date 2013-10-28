#include "vogle.h"

/*
 * move_
 */
void
move_(x, y, z)
	float 	*x, *y, *z;
{
	move(*x, *y, *z);
}


/*
 * move2_
 */
void
move2_(x, y)
	float	*x, *y;
{
	move2(*x, *y);
}

/*
 * rmove_
 */
void
rmove_(dx, dy, dz)
	float	*dx, *dy, *dz;
{
	rmove(*dx, *dy, *dz);
}

/*
 * rmove2_
 */
void
rmove2_(dx, dy)
	float	*dx, *dy;
{
	rmove2(*dx, *dy);
}

/*
 * smove2_
 */
void
smove2_(xs, ys)
	float 	*xs, *ys;
{
	smove2(*xs, *ys);
}

/*
 * rsmove2_
 */
void
rsmove2_(dxs, dys)
	float	*dxs, *dys;
{
	rsmove2(*dxs, *dys);
}

