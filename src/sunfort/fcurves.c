#include "vogle.h"

/*
 * curvebasis_
 */
void
curvebasis_(basis)
	float	basis[4][4];
{
	curvebasis(basis);
}

/*
 * curveprecision_
 */
void
curveprecision_(nsegments)
	int	*nsegments;
{
	curveprecision(*nsegments);
}

/*
 * rcurve_
 */
void
rcurve_(geom)
	float	geom[4][4];
{
	rcurve(geom);
}

/*
 * curve_
 */
void
curve_(geom)
	float	geom[4][3];
{
	curve(geom);
}

/*
 * curven_
 */
void
curven_(n, geom)
	int	*n;
	float	geom[][3];
{
	curven(*n, geom);
}
