#include "vogle.h"

/*
 * translate_
 */
translate_(x, y, z)
	float 	*x, *y, *z;
{
	translate(*x, *y, *z);
}

/*
 * scale_
 * 
 * Set up a scale matrix and premultiply it and 
 * the top matrix on the stack. Had to be specified here as some looney
 * has a routine called scale in the fotran i/o library. tsk, tsk.
 *
 */
void
scale_(x, y, z)
	float 	*x, *y, *z;
{
	Matrix	smat;

	if (!vdevice.initialised)
		verror("scale: vogle not initialised");

	identmatrix(smat);

	smat[0][0] = *x;
	smat[1][1] = *y;
	smat[2][2] = *z;

	multmatrix(smat);
}


/*
 * rotate_
 */
rotate_(r, axis)
	float	*r;
	char	*axis;
{
	rotate(*r, *axis);
}

