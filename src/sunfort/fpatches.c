#include "vogle.h"

/*
 * patchbasis_
 */
void
patchbasis_(ubasis, vbasis)
        float	*ubasis, *vbasis;
{
	patchbasis(ubasis, vbasis);
}

/*
 * patchprecision_
 */
void
patchprecision_(useg, vseg)
        int     *useg, *vseg;
{
	patchprecision(*useg, *vseg);
}

/* 
 * patchcurves_
 */
void
patchcurves_(nu, nv)
	int	*nu, *nv;
{
	patchcurves(*nu, *nv);
}

/*
 * patch_
 */
void
patch_(geomx, geomy, geomz)
	float	*geomx, *geomy, *geomz;
{
	patch(geomx, geomy, geomz);
}

/*
 * rpatch_
 */
void
rpatch_(geomx, geomy, geomz, geomw)
	float	*geomx, *geomy, *geomz, *geomw;
{
	rpatch(geomx, geomy, geomz, geomw);
}
