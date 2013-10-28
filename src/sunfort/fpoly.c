#include "vogle.h"

/*
 * polyfill_
 */
void
polyfill_(onoff)
	int	*onoff;
{
	polyfill(*onoff);
}

/*
 * hatchang_
 */
void
hatchang_(ang)
	float	*ang;
{
	hatchang(*ang);
}

/*
 * hatchpitch_
 */
void
hatchpitch_(pitch)
	float	*pitch;
{
	hatchpitch(*pitch);
}

/*
 * polyhatch_
 */
void
polyhatch_(onoff)
	int	*onoff;
{
	polyhatch(*onoff);
}

/*
 * poly2_
 */
void
poly2_(n, parray)
	int	*n;
	float	parray[][2];
{
	poly2(*n, parray);
}

/*
 * poly_
 */
void
poly_(n, parray)
	int	*n;
	float	parray[][3];
{
	poly(*n, parray);
}

/*
 * makepoly_
 */
void
makepoly_()
{
	makepoly();
}

/*
 * closepoly_
 */
void
closepoly_()
{
	closepoly();
}

/*
 * backface_
 */
void
backface_(onoff)
	int	*onoff;
{
	backface(*onoff);
}

/*
 * backfacedir_
 */
void
backfacedir_(clockwise)
	int	*clockwise;
{
	backfacedir(*clockwise);
}
