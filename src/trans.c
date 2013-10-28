#include "vogle.h"

#ifdef	TC

extern	double	cos();
extern	double	sin();

#else 

#include <math.h>

#endif

/*
 * translate
 * 
 * Set up a translation matrix and premultiply it and 
 * the top matrix on the stack.
 *
 */
void
translate(x, y, z)
	float 	x, y, z;
{
	Matrix		tmat;

	if (!vdevice.initialised) 
		verror("translate: vogle not initialised");

	identmatrix(tmat);

	tmat[3][0] = x;
	tmat[3][1] = y;
	tmat[3][2] = z;

	multmatrix(tmat);
}

/*
 * rotate
 * 
 * Set up a rotate matrix and premultiply it with 
 * the top matrix on the stack.
 *
 */
void
rotate(r, axis)
	float	r;
	char	axis;
{
	char		str[2];
	Matrix		rmat;
	float		costheta, sintheta;

	if (!vdevice.initialised)
		verror("rotate: vogle not initialised");

	identmatrix(rmat);

	costheta = cos((double)(D2R * r));
	sintheta = sin((double)(D2R * r));

	switch(axis) {
	case 'x':
	case 'X':
		rmat[1][1] = costheta;
		rmat[1][2] = sintheta;
		rmat[2][1] = -sintheta;
		rmat[2][2] = costheta;
		break;
	case 'y':
	case 'Y':
		rmat[0][0] = costheta;
		rmat[0][2] = -sintheta;
		rmat[2][0] = sintheta;
		rmat[2][2] = costheta;
		break;
	case 'z':
	case 'Z':
		rmat[0][0] = costheta;
		rmat[0][1] = sintheta;
		rmat[1][0] = -sintheta;
		rmat[1][1] = costheta;
		break;
	default:
		verror("rotate: illegal axis of rotation");
	}

	multmatrix(rmat);
}
