#include "vogle.h"

/*
 * scale
 * 
 * Set up a scale matrix and premultiply it and 
 * the top matrix on the stack.
 *
 */
void
scale(x, y, z)
	float 	x, y, z;
{
	Matrix	smat;

	if (!vdevice.initialised)
		verror("scale: vogle not initialised");

	identmatrix(smat);

	smat[0][0] = x;
	smat[1][1] = y;
	smat[2][2] = z;

	multmatrix(smat);
}
