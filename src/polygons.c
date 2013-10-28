#include	"vogle.h"

#ifdef	TC	/* Arseholes have poly defined in math.h */

extern	double	cos();
extern	double	sin();

#else 

#include <math.h>

#endif

#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define MIN(x, y)	((x) < (y) ? (x) : (y))
#define ABS(x)		((x) < 0 ? -(x) : (x))

static	float	F[6][4], S[6][4], I[4], p[MAXVERTS][4], newp[MAXVERTS][3];
static	int	nout, first[6], np;
static	int	ip1[MAXVERTS], ip2[MAXVERTS];

/*
 *  Orientation of backfacing polygons(in screen coords)
 */
static	int	clockwise = 1;

void	polyoutline();

/*
 * polyfill
 *
 *	set the polygon fill flag. This will always turn off hatching.
 */
void
polyfill(onoff)
	int	onoff;
{
	Token	*tok;

	if (vdevice.inobject) {
		tok = newtokens(2);
		tok[0].i = POLYFILL;
		tok[1].i = onoff;

		return;
	}

	vdevice.attr->a.fill = onoff;
	vdevice.attr->a.hatch = 0;
}

/*
 * polyhatch
 *
 *	set the polygon hatch flag. This will always turn off fill.
 */
void
polyhatch(onoff)
	int	onoff;
{
	Token	*tok;

	if (vdevice.inobject) {
		tok = newtokens(2);
		tok[0].i = POLYHATCH;
		tok[1].i = onoff;

		return;
	}

	vdevice.attr->a.hatch = onoff;
	vdevice.attr->a.fill = 0;
}

/*
 * hatchang
 *
 *	set the hatch angle
 */
void
hatchang(a)
	float	a;
{
	Token	*tok;

	if (!vdevice.initialised)
		verror("hatchang: vogle not initialised");

	if (vdevice.inobject) {
		tok = newtokens(3);

		tok[0].i = HATCHANG;
		tok[1].f = cos((double)(a*D2R));
		tok[2].f = sin((double)(a*D2R));
		return;
	}

	vdevice.attr->a.hatchcos = cos((double)(a*D2R));
	vdevice.attr->a.hatchsin = sin((double)(a*D2R));
}

/*
 * hatchpitch
 *
 *	set the hatch pitch
 */
void
hatchpitch(a)
	float	a;
{
	Token	*tok;

	if (!vdevice.initialised)
		verror("hatchpitch: vogle not initialised");

	if (vdevice.inobject) {
		tok = newtokens(2);

		tok[0].i = HATCHPITCH;
		tok[1].f = a;
		return;
	}

	vdevice.attr->a.hatchpitch = a;
}

/*
 * hatch
 *
 *	hatch the polygon defined by the n points in the array p.
 */
static void
hatch(n, p)
	int	n;
	float	p[][3];
{
	float yl, xint, y1, y2, x1, x2, tmp, ymax = -1.0e30, ymin = 1.0e30;
	float	xi[128];
	float	s, c, pitch;
	int	i, j, sorted;

	c = vdevice.attr->a.hatchcos;
	s = vdevice.attr->a.hatchsin;
	pitch = vdevice.attr->a.hatchpitch;

	/*
	 * Rotate by the x-hatch angle...
	 */
	
	for (i = 0; i < n; i++) {
		tmp = p[i][0];
		p[i][0] = p[i][0] * c - p[i][1] * s;
		p[i][1] = tmp * s + p[i][1] * c;
		ymax = MAX(ymax, p[i][1]);
		ymin = MIN(ymin, p[i][1]);
	}

	/*
	 * For each y value, get a list of X intersections...
	 */
	yl = ymax - pitch;
	while (yl > ymin) {
		j = 0;
		for (i = 0; i < n-1; i++) 
			if (yintersect(yl, p[i][0], p[i][1], p[i+1][0], p[i+1][1], &xint)) 
				xi[j++] = xint;
		/*
 		 * Last one.
		 */
		if (yintersect(yl, p[n-1][0], p[n-1][1], p[0][0], p[0][1], &xint))
			xi[j++] = xint;
		/*
   		 * Sort the X intersections...
		 */
		sorted = 0;
		while (!sorted) {
			sorted = 1;
			for (i = 0; i < j-1; i++) 
				if (xi[i] > xi[i+1]) {
					tmp = xi[i];
					xi[i] = xi[i+1];
					xi[i+1] = tmp;
					sorted = 0;
				}
		}

		/*
		 *  Draw the lines (Rotated back)...
		 */
		for (i = 0; i < j-1; i += 2) {
			y1 = yl * c - xi[i] * s;
			y2 = yl * c - xi[i+1] * s;
			x1 = xi[i] * c + yl * s;
			x2 = xi[i+1] * c + yl * s;
			move2(x1, y1);
			draw2(x2, y2);
		}
		yl -= pitch;
	}
	for (i = 0; i < n; i++) {
		tmp = p[i][0];
		p[i][0] = tmp*c + p[i][1]*s;
		p[i][1] = p[i][1]*c - tmp*s;
	}
	move2(p[0][0], p[0][1]);
	for (i = 1; i < n; i++) 
		draw2(p[i][0], p[i][1]);

	draw2(p[0][0], p[0][1]);
}

static
yintersect(y, x1, y1, x2, y2, xint)
	float	y, x1, y1, x2, y2, *xint;
{
	float	t, a;

	a = y2 - y1;
	if (ABS(a) >= 0.00001) {
		t = (y - y1) / a;
		if (t >= 0.0 && t <= 1.0) {
			*xint = x1 + t*(x2 - x1);
			return (1);
		}
	}
	return (0);
}

/*
 * backfacedir
 *
 *	Set which direction backfacing polygons are defined to be.
 *	1 = clockwise (in screen coords) 0 = anticlockwise.
 */
void
backfacedir(cdir)
	int	cdir;
{
	clockwise = cdir;
}

/*
 * backface
 *
 *	Turns on culling of backfacing polygons. A polygon is
 * backfacing if it's orientation in *screen* coords is clockwise.
 */
void
backface(onoff)
	int	onoff;
{
	vdevice.attr->a.backface = onoff;
}

/*
 * dopoly
 *
 *	do a transformed polygon with n edges using fill or hatch
 */
static void
dopoly(n)
	int	n;
{
	int	i, x1, x2, y1, y2;
	char	buf[100];

	if (n > MAXVERTS) {
		sprintf(buf, "dopoly: can't hatch or fill a polygon with more than %d vertices", MAXVERTS);
		verror(buf);
	}

	if (!vdevice.clipoff) {
		polyclip(n);
	} else {
		nout = n;
		for (i = 0; i < n; i++) {
			ip1[i] = WtoVx(p[i]);
			ip2[i] = WtoVy(p[i]);
		}
	}


	if (vdevice.attr->a.backface && checkbacki())
		return;

	if (vdevice.attr->a.fill) {
		if (nout > 2) {
			(*vdevice.dev.Vfill)(nout, ip1, ip2);
		}
	} else {
		vdevice.cpVx = ip1[0];
		vdevice.cpVy = ip2[0];
		vdevice.cpVvalid = 0;
		polyoutline(nout, ip1, ip2);
	}
}

/*
 * polyoutline
 *
 *	draws a polygon outline from already transformed points.
 */
static void
polyoutline(n, ipx, ipy)
	int	n;
	int	ipx[], ipy[];
{
	int	i;

	if (n > 2) {
		for (i = 1; i < n; i++) {
			(*vdevice.dev.Vdraw)(ipx[i], ipy[i]);

			vdevice.cpVx = ipx[i];
			vdevice.cpVy = ipy[i];
		}
		(*vdevice.dev.Vdraw)(ipx[0], ipy[0]);

		vdevice.cpVx = ipx[0];
		vdevice.cpVy = ipy[0];
	}
}

/*
 * polyobj
 *
 *	construct a polygon from a object token list.
 */
void
polyobj(n, dp)
	int	n;
	Token	dp[];
{
	int	i, j, x1, x2, y1, y2;
	float	vect[4], result[4];
	Token	*tok;
	
	if (vdevice.attr->a.hatch)
		hatch(n, dp);

	for (i = 0, j = 0; i < n; i++, j += 3) {
		vect[V_X] = dp[j + V_X].f;
		vect[V_Y] = dp[j + V_Y].f;
		vect[V_Z] = dp[j + V_Z].f;
		vect[V_W] = 1;
		multvector(result, vect, vdevice.transmat->m);
		p[i][V_X] = result[V_X];
		p[i][V_Y] = result[V_Y];
		p[i][V_Z] = result[V_Z];
		p[i][V_W] = result[V_W];
	}

	dopoly(n);

	vdevice.cpW[V_X] = dp[V_X].f;
	vdevice.cpW[V_Y] = dp[V_Y].f;
	vdevice.cpW[V_Z] = dp[V_Z].f;
}

/*
 * poly2
 *
 *	construct a polygon from a (x, y) array of points provided by the user.
 */
void
poly2(n, dp)
	int	n;
	float	dp[][2];
{
	int	i;
	float	np[MAXVERTS][3];

	if (!vdevice.initialised)
		verror("poly: vogle not initialised");

	for (i = 0; i < n; i++) {
		np[i][V_X] = dp[i][V_X];
		np[i][V_Y] = dp[i][V_Y];
		np[i][V_Z] = 0.0;
	}

	poly(n, np);
}

/*
 * poly
 *
 *	construct a polygon from an array of points provided by the user.
 */
void
poly(n, dp)
	int	n;
	float	dp[][3];
{
	int	i, j, x1, x2, y1, y2;
	Vector	vect, result;
	Token	*tok;
	
	if (!vdevice.initialised)
		verror("poly: vogle not initialised");

	if (vdevice.inobject) {
		tok = newtokens(2 + 3 * n);
		tok[0].i = POLY;
		tok[1].i = n;
		for (i = 0, j = 2; i < n; i++, j += 3) {
			tok[j + V_X].f = dp[i][V_X];
			tok[j + V_Y].f = dp[i][V_Y];
			tok[j + V_Z].f = dp[i][V_Z];
		}
		return;
	}

	if (vdevice.attr->a.hatch)
		hatch(n, dp);

	for (i = 0; i < n; i++) {
		vect[V_X] = dp[i][V_X];
		vect[V_Y] = dp[i][V_Y];
		vect[V_Z] = dp[i][V_Z];
		vect[V_W] = 1;
		multvector(result, vect, vdevice.transmat->m);
		p[i][V_X] = result[V_X];
		p[i][V_Y] = result[V_Y];
		p[i][V_Z] = result[V_Z];
		p[i][V_W] = result[V_W];
	}

	dopoly(n);

	vdevice.cpW[V_X] = dp[0][V_X];
	vdevice.cpW[V_Y] = dp[0][V_Y];
	vdevice.cpW[V_Z] = dp[0][V_Z];
}

/*
 * pmove
 *
 *	set the start position of a polygon
 */
void
pmove(x, y, z)
	float	x, y, z;
{
	np = 0;
	p[np][V_X] = x;
	p[np][V_Y] = y;
	p[np][V_Z] = z;
	p[np][V_W] = 1.0;
}

/*
 * pdraw
 *
 *	add another vertex to the polygon array
 */
void
pdraw(x, y, z)
	float	x, y, z;
{
	char	buf[100];

	np++;

	if (np >= MAXVERTS) {
		sprintf(buf, "pdraw: can't draw a polygon with more than %d vertices", MAXVERTS);
		verror(buf);
	}

	p[np][V_X] = x;
	p[np][V_Y] = y;
	p[np][V_Z] = z;
	p[np][V_W] = 1.0;
}

/*
 * makepoly
 *
 *	set up a polygon which will be constructed by a series of
 * move draws.
 */
void
makepoly()
{
	vdevice.inpolygon = 1;
	vdevice.pmove = pmove;
	vdevice.pdraw = pdraw;
	np = 0;
	p[np][V_X] = vdevice.cpW[V_X];
	p[np][V_Y] = vdevice.cpW[V_Y];
	p[np][V_Z] = vdevice.cpW[V_Z];
	p[np][V_W] = 1.0;
	
}

/*
 * closepoly
 *
 *	draw the polygon started by the above.
 */
void
closepoly()
{
	float	lstx, lsty, lstz;
	Vector	result, vect;
	int	i, j, x1, x2, y1, y2;
	Token	*tok;

	if (!vdevice.initialised)
		verror("closepoly: vogle not initialised");

	vdevice.inpolygon = 0;

	if (vdevice.inobject) {
		tok = newtokens(2 + 3 * (np + 1));
		tok[0].i = POLY;
		tok[1].i = np + 1;
		for (i = 0, j = 2; i <= np; i++, j += 3) {
			tok[j + V_X].f = p[i][V_X];
			tok[j + V_Y].f = p[i][V_Y];
			tok[j + V_Z].f = p[i][V_Z];
		}

		return;
	}

	lstx = p[np][V_X];
	lsty = p[np][V_Y];
	lstz = p[np][V_Z];

	np++;

	if (vdevice.attr->a.hatch) {
		for (i = 0; i < np; i++) {
			newp[i][0] = p[i][0];
			newp[i][1] = p[i][1];
			newp[i][2] = p[i][2];
		}
		hatch(np, newp);
	}

	for (i = 0; i < np; i++) {
		multvector(result, p[i], vdevice.transmat->m);
		p[i][V_X] = result[V_X];
		p[i][V_Y] = result[V_Y];
		p[i][V_Z] = result[V_Z];
		p[i][V_W] = result[V_W];
	}

	dopoly(np);

	vdevice.cpW[V_X] = lstx;
	vdevice.cpW[V_Y] = lsty;
	vdevice.cpW[V_Z] = lstz;
}

/*
 * checkbacki
 *
 *	Checks if a transformed polygon is backfacing or not.
 */
static	int
checkbacki()
{

#ifdef	PC	/*	Only has 16 bit ints */
#define	BACKFACE(z)	(clockwise ? ((z) <= 0L) : ((z) > 0L))
	long	z;
#else
#define	BACKFACE(z)	(clockwise ? ((z) <= 0) : ((z) > 0))
	int	z;
#endif

	int	x1, x2, y1, y2;

	x1 = ip1[1] - ip1[0];
	x2 = ip1[2] - ip1[1];
	y1 = ip2[1] - ip2[0];
	y2 = ip2[2] - ip2[1];

#ifdef	PC
	z = (long)x1 * (long)y2 - (long)y1 * (long)x2;
#else
	z = x1 * y2 - y1 * x2;
#endif

	return(BACKFACE(z));
}

/*
 * The following routines are an implementation of the Sutherland - Hodgman
 * polygon clipper, as described in "Reentrant Polygon Clipping"
 * Communications of the ACM Jan 1974, Vol 17 No. 1.
 */
static
polyclip(n)
	register	int	n;
{
	int	i;

	nout = 0;
	for (i = 0; i < 6; i++)
		first[i] = 1;

	for (i = 0; i < n; i++) 
		shclip(p[i], 0);

	shclose(0);
}

static
shclip(p, side)
	float	p[4];
	int	side;
{
	float	P[4];

	if (side == 6) {
		ip1[nout] = WtoVx(p);
		ip2[nout++] = WtoVy(p);
	} else {
		copyvector(P, p);
		if (first[side]) {
			first[side] = 0;
			copyvector(F[side], P);
		} else if (intersect(side, I, P)) {
			shclip(I, side + 1);
		}
		copyvector(S[side], P);
		if (visible(side)) 
			shclip(S[side], side + 1);
	}
}

static
shclose(side)
	int	side;
{
	if (side < 6) {
		if (intersect(side, I, F[side]))
			shclip(I, side + 1);

		shclose(side + 1);

		first[side] = 1;
	}
}

static
intersect(side, I, p)
	int	side;
	register	Vector	I, p;
{
	register	float	wc1, wc2, a;

	switch (side) {
	case 0:		/* x - left */
		wc1 = p[3] + p[0];
		wc2 = S[side][3] + S[side][0];
		break;
	case 1:		/* x - right */
		wc1 = p[3] - p[0];
		wc2 = S[side][3] - S[side][0];
		break;
	case 2:		/* y - bottom */
		wc1 = p[3] + p[1];
		wc2 = S[side][3] + S[side][1];
		break;
	case 3:		/* y - top */
		wc1 = p[3] - p[1];
		wc2 = S[side][3] - S[side][1];
		break;
	case 4:		/* z - near */
		wc1 = p[3] + p[2];
		wc2 = S[side][3] + S[side][2];
		break;
	case 5:		/* z - far */
		wc1 = p[3] - p[2];
		wc2 = S[side][3] - S[side][2];
		break;
	default:
		verror("intersect: ridiculous side value");
	}

	if (wc1 * wc2 < 0.0) {	/* Both are opposite in sign - crosses */
		a = wc1 / (wc1 - wc2);
		if (a < 0.0 || a > 1.0) {
			return(0);
		} else {
			I[0] = p[0] + a * (S[side][0] - p[0]);
			I[1] = p[1] + a * (S[side][1] - p[1]);
			I[2] = p[2] + a * (S[side][2] - p[2]);
			I[3] = p[3] + a * (S[side][3] - p[3]);
			return(1);
		}
	}
	return(0);
}

static
visible(side)
	int	side;
{
	float	wc;

	switch (side) {
	case 0:		/* x - left */
		wc = S[side][3] + S[side][0];
		break;
	case 1:		/* x - right */
		wc = S[side][3] - S[side][0];
		break;
	case 2:		/* y - bottom */
		wc = S[side][3] + S[side][1];
		break;
	case 3:		/* y - top */
		wc = S[side][3] - S[side][1];
		break;
	case 4:		/* z - near */
		wc = S[side][3] + S[side][2];
		break;
	case 5:		/* z - far */
		wc = S[side][3] - S[side][2];
		break;
	default:
		verror("visible: ridiculous side value");
	}

	return(wc >= 0.0);
}
