#include "vogle.h"

/*
 * polarview_
 */
polarview_(dist, azim, inc, twist)
	float	*dist, *azim, *inc, *twist;
{
	polarview(*dist, *azim, *inc, *twist);
}

/*
 * up_
 */
up_(x, y, z)
	float	*x, *y, *z;
{
	up(*x, *y, *z);
}

/*
 * lookat_
 */
lookat_(vx, vy, vz, px, py, pz, twist)
	float  *vx, *vy, *vz, *px, *py, *pz, *twist;
{
	lookat(*vx, *vy, *vz, *px, *py, *pz, *twist);
}

/*
 * perspective_
 */
perspective_(fov, aspect, hither, yon)
	float 	*fov, *aspect, *hither, *yon;
{
	perspective(*fov, *aspect, *hither, *yon);
}

/*
 * window_
 */
window_(left, right, bottom, top, hither, yon)
	float 	*left, *right, *bottom, *top, *hither, *yon;
{
	window(*left, *right, *bottom, *top, *hither, *yon);
}

/*
 * ortho_
 */
ortho_(left, right, bottom, top, hither, yon)
	float 	*left, *right, *bottom, *top, *hither, *yon;
{
	ortho(*left, *right, *bottom, *top, *hither, *yon);
}

/*
 * ortho2_
 */
ortho2_(left, right, bottom, top)
	float	*left, *right, *bottom, *top;
{
	ortho2(*left, *right, *bottom, *top);
}
