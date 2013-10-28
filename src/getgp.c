#include "vogle.h"

/*
 * getgp
 *
 *	return the current (x, y, z) graphics position
 */
void
getgp(x, y, z)
	float	*x, *y, *z;
{
	*x = vdevice.cpW[V_X];
	*y = vdevice.cpW[V_Y];
	*z = vdevice.cpW[V_Z];
}

/*
 * getgp2
 *
 *	return the current (x, y) graphics position
 */
void
getgp2(x, y)
	float	*x, *y;
{
	*x = vdevice.cpW[V_X];
	*y = vdevice.cpW[V_Y];
}

/*
 * sgetgp2
 *
 *	return the current (x, y) graphics position in screen coordinates
 */
void
sgetgp2(x, y)
	float	*x, *y;
{
	float	sx, sy;

	sx = vdevice.maxVx - vdevice.minVx;
	sy = vdevice.maxVy - vdevice.minVy;

	multvector(vdevice.cpWtrans, vdevice.cpW, vdevice.transmat->m);
	*x = 2.0 * WtoVx(vdevice.cpWtrans) / sx - 1.0;
	*y = 2.0 * WtoVy(vdevice.cpWtrans) / sy - 1.0;
}
