#include <stdio.h>

/*
 * C routines to test the Microsoft Fortran interface.
 */

void
vinit(s)
	char *s;
{
	printf("\nC-vinit: %s\n", s);
	fflush(stdout);
}

void
voutput(s)
	char *s;
{
	printf("\nC-voutput: %s\n", s);
	fflush(stdout);
}

void
vnewdev(s)
	char *s;
{
	printf("\nC-vnewdev: %s\n", s);
	fflush(stdout);
}

void
vgetdev(s)
	char *s;
{
	printf("\nC-vgetdev: A_device\n");
	fflush(stdout);
	strcpy(s, "A_device");
}

void
vexit()
{
	printf("\nC-vexit\n");
	fflush(stdout);
}

void
clear()
{
	printf("\nC-clear\n");
	fflush(stdout);
}

void
color(i)
	int	i;
{
	printf("\nC-color: %d\n", i);
	fflush(stdout);
}

void
mapcolor(i, r, g, b)
	int	i, r, g, b;
{
	printf("\nC-mapcolor: %d %d %d %d\n", i, r, g, b);
	fflush(stdout);
}

void
clipping(i)
	int	i;
{
	printf("\nC-clipping: %d\n", i);
	fflush(stdout);
}

int
getkey()
{
	printf("\nC-getkey: returning 11\n");
	fflush(stdout);
	return(11);
}

int
checkkey()
{
	printf("\nC-checkkey: returning 14\n");
	fflush(stdout);
	return(14);
}

int
getdepth()
{
	printf("\nC-getdepth: returning 111\n");
	fflush(stdout);
	return(111);
}

int
locator(x, y)
	float	*x, *y;
{
	printf("\nC-locator: returning 13 as fn val, x = 23.4, y = 44.2\n");
	fflush(stdout);
	*x = 23.4;
	*y = 44.2;
	return (13);
}

int
slocator(x, y)
	float	*x, *y;
{
	printf("\nC-slocator: returning 13 as fn val, x = 23.4, y = 44.2\n");
	fflush(stdout);
	*x = 23.4;
	*y = 44.2;
	return (13);
}

void
viewport(a, b, c, d)
	float	a, b, c, d;
{
	printf("\nC-viewport: %f %f %f %f\n", a, b, c, d);
	fflush(stdout);
}

void
getviewport(a, b, c, d)
	float	*a, *b, *c, *d;
{
	printf("\nC-getviewport: returning 1.0, 2.0, 3.0, 4.0\n");
	fflush(stdout);
	*a = 1.0;
	*b = 2.0;
	*c = 3.0;
	*d = 4.0;
}

void
pushviewport()
{
	printf("\nC-pushviewport\n");
	fflush(stdout);
}

void
popviewport()
{
	printf("\nC-popviewport\n");
	fflush(stdout);
}

void
pushattributes()
{
	printf("\nC-pushattributes\n");
	fflush(stdout);
}

void
popattributes()
{
	printf("\nC-popattributes\n");
	fflush(stdout);
}

void
ortho(a, b, c, d, e, f)
	float	a, b, c, d, e, f;
{
	printf("\nC-ortho: %f %f %f %f %f %f\n", a, b, c, d, e, f);
	fflush(stdout);
}

void
ortho2(a, b, c, d)
	float	a, b, c, d;
{
	printf("\nC-ortho2: %f %f %f %f\n", a, b, c, d);
	fflush(stdout);
}

void
perspective(a, b, c, d)
	float	a, b, c, d;
{
	printf("\nC-perspective: %f %f %f %f\n", a, b, c, d);
	fflush(stdout);
}

void
window(a, b, c, d, e, f)
	float	a, b, c, d, e, f;
{
	printf("\nC-window: %f %f %f %f %f %f\n", a, b, c, d, e, f);
	fflush(stdout);
}

void
pushmatrix()
{
	printf("\nC-pushmatrix\n");
	fflush(stdout);
}

void
popmatrix()
{
	printf("\nC-popmatrix\n");
	fflush(stdout);
}


void
polarview(a, b, c, d)
	float	a, b, c, d;
{
	printf("\nC-polarview: %f %f %f %f\n", a, b, c, d);
	fflush(stdout);
}

void
lookat(a, b, c, d, e, f, g)
	float	a, b, c, d, e, f, g;
{
	printf("\nC-lookat: %f %f %f %f %f %f %f\n", a, b, c, d, e, f, g);
	fflush(stdout);
}

void
move(x, y, z)
	float x, y, z;
{
	printf("\nC-move: %f %f %f\n", x, y, z);
	fflush(stdout);
}

void
rmove(x, y, z)
	float x, y, z;
{
	printf("\nC-rmove: %f %f %f\n", x, y, z);
	fflush(stdout);
}

void
move2(x, y)
	float x, y;
{
	printf("\nC-move2: %f %f\n", x, y);
	fflush(stdout);
}

void
rmove2(x, y)
	float x, y;
{
	printf("\nC-rmove2: %f %f\n", x, y);
	fflush(stdout);
}

void
smove2(x, y)
	float x, y;
{
	printf("\nC-smove2: %f %f\n", x, y);
	fflush(stdout);
}

void
rsmove2(x, y)
	float x, y;
{
	printf("\nC-rsmove2: %f %f\n", x, y);
	fflush(stdout);
}



void
draw(x, y, z)
	float x, y, z;
{
	printf("\nC-draw: %f %f %f\n", x, y, z);
	fflush(stdout);
}

void
rdraw(x, y, z)
	float x, y, z;
{
	printf("\nC-rdraw: %f %f %f\n", x, y, z);
	fflush(stdout);
}

void
draw2(x, y)
	float x, y;
{
	printf("\nC-draw2: %f %f\n", x, y);
	fflush(stdout);
}

void
rdraw2(x, y)
	float x, y;
{
	printf("\nC-rdraw2: %f %f\n", x, y);
	fflush(stdout);
}

void
sdraw2(x, y)
	float x, y;
{
	printf("\nC-sdraw2: %f %f\n", x, y);
	fflush(stdout);
}

void
rsdraw2(x, y)
	float x, y;
{
	printf("\nC-rsdraw2: %f %f\n", x, y);
	fflush(stdout);
}

void
arcprecision(i)
	int	i;
{
	printf("\nC-arcprecision: %d\n", i);
	fflush(stdout);
}

void
circleprecision(i)
	int	i;
{
	printf("\nC-circleprecision: %d\n", i);
	fflush(stdout);
}

void
arc(a, b, c, d, e)
	float	a, b, c, d, e;
{
	printf("\nC-arc: %f %f %f %f %f\n", a, b, c, d, e);
	fflush(stdout);
}

void
sector(a, b, c, d, e)
	float	a, b, c, d, e;
{
	printf("\nC-sector: %f %f %f %f %f\n", a, b, c, d, e);
	fflush(stdout);
}

void
circle(a, b, c)
	float	a, b, c;
{
	printf("\nC-circle: %f %f %f\n", a, b, c);
	fflush(stdout);
}

void
curvebasis(b)
	float b[4][4];
{
	printf("\nC-curvebasis:\n");
	printf("%f %f %f %f\n", b[0][0], b[0][1], b[0][2], b[0][3]);
	printf("%f %f %f %f\n", b[1][0], b[1][1], b[1][2], b[1][3]);
	printf("%f %f %f %f\n", b[2][0], b[2][1], b[2][2], b[2][3]);
	printf("%f %f %f %f\n\n", b[3][0], b[3][1], b[3][2], b[3][3]);
	fflush(stdout);
}

void
curveprecision(i)
	int	i;
{
	printf("\nC-curveprecision: %d\n", i);
	fflush(stdout);
}

void
rcurve(b)
	float b[4][4];
{
	printf("\nC-rcurve:\n");
	printf("%f %f %f %f\n", b[0][0], b[0][1], b[0][2], b[0][3]);
	printf("%f %f %f %f\n", b[1][0], b[1][1], b[1][2], b[1][3]);
	printf("%f %f %f %f\n", b[2][0], b[2][1], b[2][2], b[2][3]);
	printf("%f %f %f %f\n\n", b[3][0], b[3][1], b[3][2], b[3][3]);
	fflush(stdout);
}

void
curve(b)
	float b[4][3];
{
	printf("\nC-curve:\n");
	printf("%f %f %f\n", b[0][0], b[0][1], b[0][2]);
	printf("%f %f %f\n", b[1][0], b[1][1], b[1][2]);
	printf("%f %f %f\n", b[2][0], b[2][1], b[2][2]);
	printf("%f %f %f\n\n", b[3][0], b[3][1], b[3][2]);
	fflush(stdout);
}

void
curven(n, b)
	float b[][3];
{
	int	i;
	
	printf("\nC-curven: %d\n", n);
	fflush(stdout);
	if (n > 6) 
		n = 6;

	for (i = 0; i < n; i++) 
		printf("%f %f %f\n", b[i][0], b[i][1], b[i][2]);

	printf("\n");
	fflush(stdout);
}

void
rect(a, b, c, d)
	float	a, b, c, d;
{
	printf("\nC-rect: %f %f %f %f\n", a, b, c, d);
	fflush(stdout);
}

void
polyfill(i)
	int	i;
{
	printf("\nC-polyfill: %d\n", i);
	fflush(stdout);
}

void
polyhatch(i)
	int	i;
{
	printf("\nC-polyhatch: %d\n", i);
	fflush(stdout);
}

void
hatchang(i)
	float	i;
{
	printf("\nC-hatchang: %f\n", i);
	fflush(stdout);
}

void
hatchpitch(i)
	float	i;
{
	printf("\nC-hatchpitch: %f\n", i);
	fflush(stdout);
}

void
poly2(n , p)
	int	n;
	float	p[][2];
{
	int	i;

	printf("\nC-poly2: %d\n", n);
	fflush(stdout);
	if (n > 6) 
		n = 6;
	
	for (i = 0; i < n; i++)
		printf("%f %f\n", p[i][0], p[i][1]);
	fflush(stdout);

	printf("\n");
	fflush(stdout);
}
	
void
poly(n , p)
	int	n;
	float	p[][3];
{
	int	i;

	printf("\nC-poly: %d\n", n);
	fflush(stdout);
	if (n > 6) 
		n = 6;
	
	for (i = 0; i < n; i++)
		printf("%f %f %f\n", p[i][0], p[i][1], p[i][2]);
	fflush(stdout);

	printf("\n");
	fflush(stdout);
}

void
makepoly()
{
	printf("\nC-makepoly\n");
	fflush(stdout);
}

void
closepoly()
{
	printf("\nC-closepoly\n");
	fflush(stdout);
}

void
font(s)
	char *s;
{
	printf("\nC-font: %s\n", s);
	fflush(stdout);
}

int
numchars()
{
	printf("\nC-numchars: returning 15\n");
	fflush(stdout);
	return(15);
}

void
textsize(a, b)
	float	a, b;
{
	printf("\nC-textsize: %f %f\n", a, b);
	fflush(stdout);
}

void
textang(a)
	float	a;
{
	printf("\nC-textang: %f\n", a);
	fflush(stdout);
}

void
fixedwidth(i)
	int	i;
{
	printf("\nC-fixedwidth: %d\n", i);
	fflush(stdout);
}

void
centertext(i)
	int	i;
{
	printf("\nC-centertext: %d\n", i);
	fflush(stdout);
}

void
getcharsize(c, a, b)
	char	c;
	float *a, *b;
{
	printf("\nC-getcharsize: %c, returning w = 11.3, h = 555.4\n", c);
	fflush(stdout);
	*a = 11.3;
	*b = 555.4;
}

void
getfontsize(a, b)
	float *a, *b;
{
	printf("\nC-getfontsize: returning w = 11.3, h = 555.4\n");
	fflush(stdout);
	*a = 11.3;
	*b = 555.4;
}

void
drawchar(c)
	char	c;
{
	printf("\nC-drawchar: %c\n", c);
	fflush(stdout);
}

void
drawstr(c)
	char	*c;
{
	printf("\nC-drawstr: %s\n", c);
	fflush(stdout);
}

float
strlength(s)
	char	*s;
{
	printf("\nC-strlength: returning (float)strlen(%s)\n", s);
	fflush(stdout);
	return ((float)strlen(s));
}

void
boxtext(x, y, l, h, s)
	float	x, y, l, h;
	char	*s;
{
	printf("\nC-boxtext: %f %f %f %f %s\n", x, y, l, h, s);
	fflush(stdout);
}

void
boxfit(l, h, n)
	float	l, h;
	int	n;
{
	printf("\nC-boxfit: %f %f %d\n",l, h, n);
	fflush(stdout);
}

void
translate(x, y, z)
	float	x, y, z;
{
	printf("\nC-translate: %f %f %f\n", x, y, z);
	fflush(stdout);
}

void
scale(x, y, z)
	float	x, y, z;
{
	printf("\nC-scale: %f %f %f\n", x, y, z);
	fflush(stdout);
}

void
rotate(x, a)
	float	x;
	char	a;
{
	printf("\nC-rotate: %f %c\n", x, a);
	fflush(stdout);
}

void
patchbasis(a, b)
	float	a[4][4], b[4][4];
{
	printf("\nC-patchbasis:\n");
	printf("%f %f %f %f\n", a[0][0], a[0][1], a[0][2], a[0][3]);
	printf("%f %f %f %f\n", a[1][0], a[1][1], a[1][2], a[1][3]);
	printf("%f %f %f %f\n", a[2][0], a[2][1], a[2][2], a[2][3]);
	printf("%f %f %f %f\n\n", a[3][0], a[3][1], a[3][2], a[3][3]);

	printf("%f %f %f %f\n", b[0][0], b[0][1], b[0][2], b[0][3]);
	printf("%f %f %f %f\n", b[1][0], b[1][1], b[1][2], b[1][3]);
	printf("%f %f %f %f\n", b[2][0], b[2][1], b[2][2], b[2][3]);
	printf("%f %f %f %f\n\n", b[3][0], b[3][1], b[3][2], b[3][3]);
	fflush(stdout);
}

void
patchprecision(a, b)
	int	a, b;
{
	printf("\nC-patchprecision: %d %d\n", a, b);
	fflush(stdout);
}

void
patchcurves(a, b)
	int	a, b;
{
	printf("\nC-patchcurves: %d %d\n", a, b);
	fflush(stdout);
}

void
rpatch(a, b, c, d)
	float	a[4][4], b[4][4], c[4][4], d[4][4];
{
	printf("\nC-rpatch:\n");
	printf("%f %f %f %f\n", a[0][0], a[0][1], a[0][2], a[0][3]);
	printf("%f %f %f %f\n", a[1][0], a[1][1], a[1][2], a[1][3]);
	printf("%f %f %f %f\n", a[2][0], a[2][1], a[2][2], a[2][3]);
	printf("%f %f %f %f\n\n", a[3][0], a[3][1], a[3][2], a[3][3]);

	printf("%f %f %f %f\n", b[0][0], b[0][1], b[0][2], b[0][3]);
	printf("%f %f %f %f\n", b[1][0], b[1][1], b[1][2], b[1][3]);
	printf("%f %f %f %f\n", b[2][0], b[2][1], b[2][2], b[2][3]);
	printf("%f %f %f %f\n\n", b[3][0], b[3][1], b[3][2], b[3][3]);

	printf("%f %f %f %f\n", c[0][0], c[0][1], c[0][2], c[0][3]);
	printf("%f %f %f %f\n", c[1][0], c[1][1], c[1][2], c[1][3]);
	printf("%f %f %f %f\n", c[2][0], c[2][1], c[2][2], c[2][3]);
	printf("%f %f %f %f\n\n", c[3][0], c[3][1], c[3][2], c[3][3]);

	printf("%f %f %f %f\n", d[0][0], d[0][1], d[0][2], d[0][3]);
	printf("%f %f %f %f\n", d[1][0], d[1][1], d[1][2], d[1][3]);
	printf("%f %f %f %f\n", d[2][0], d[2][1], d[2][2], d[2][3]);
	printf("%f %f %f %f\n\n", d[3][0], d[3][1], d[3][2], d[3][3]);
	fflush(stdout);
}

void
patch(a, b, c)
	float	a[4][4], b[4][4], c[4][4];
{
	printf("\nC-patch:\n");
	printf("%f %f %f %f\n", a[0][0], a[0][1], a[0][2], a[0][3]);
	printf("%f %f %f %f\n", a[1][0], a[1][1], a[1][2], a[1][3]);
	printf("%f %f %f %f\n", a[2][0], a[2][1], a[2][2], a[2][3]);
	printf("%f %f %f %f\n\n", a[3][0], a[3][1], a[3][2], a[3][3]);

	printf("%f %f %f %f\n", b[0][0], b[0][1], b[0][2], b[0][3]);
	printf("%f %f %f %f\n", b[1][0], b[1][1], b[1][2], b[1][3]);
	printf("%f %f %f %f\n", b[2][0], b[2][1], b[2][2], b[2][3]);
	printf("%f %f %f %f\n\n", b[3][0], b[3][1], b[3][2], b[3][3]);

	printf("%f %f %f %f\n", c[0][0], c[0][1], c[0][2], c[0][3]);
	printf("%f %f %f %f\n", c[1][0], c[1][1], c[1][2], c[1][3]);
	printf("%f %f %f %f\n", c[2][0], c[2][1], c[2][2], c[2][3]);
	printf("%f %f %f %f\n\n", c[3][0], c[3][1], c[3][2], c[3][3]);
	fflush(stdout);
}

void
point(x, y, z)
	float	x, y, z;
{
	printf("\nC-point: %f %f %f\n", x, y, z);
	fflush(stdout);
}

void
point2(x, y)
	float	x, y;
{
	printf("\nC-point2: %f %f\n", x, y);
	fflush(stdout);
}

void
makeobj(n)
	int	n;
{
	printf("\nC-makeobj: %d\n", n);
	fflush(stdout);
}

void
delobj(n)
	int	n;
{
	printf("\nC-delobj: %d\n", n);
	fflush(stdout);
}

void
closeobj()
{
	printf("\nC-closeobj");
	fflush(stdout);
}

int
genobj()
{
	printf("\nC-genobj: returning 77");
	fflush(stdout);
	return (77);
}

int
getopenobj()
{
	printf("\nC-getopenobj: returning 88");
	fflush(stdout);
	return (88);
}

void
callobj(n)
	int	n;
{
	printf("\nC-callobj: %d\n", n);
	fflush(stdout);
}

int
isobj(n)
	int	n;
{
	printf("\nC-isobj: %d, returning 1\n", n);
	fflush(stdout);
	return(1);
}

void
loadobj(n, s)
	int	n;
	char	*s;
{
	printf("\nC-loadobj: %d %s\n", n, s);
	fflush(stdout);
}

void
saveobj(n, s)
	int	n;
	char	*s;
{
	printf("\nC-saveobj: %d %s\n", n, s);
	fflush(stdout);
}

void
getgp(x, y, z)
	float	*x, *y, *z;
{
	printf("\nC-getgp: returning x = 1.0, y = 2.0, z = 3.0\n");
	fflush(stdout);
	*x = 1.0;
	*y = 2.0;
	*z = 3.0;
}

void
sgetgp2(x, y)
	float	*x, *y;
{
	printf("\nC-sgetgp2: returning x = 1.0, y = 2.0\n");
	fflush(stdout);
	*x = 1.0;
	*y = 2.0;
}

void
getgp2(x, y)
	float	*x, *y;
{
	printf("\nC-getgp2: returning x = 1.0, y = 2.0\n");
	fflush(stdout);
	*x = 1.0;
	*y = 2.0;
}

void
loadmatrix(c)
	float	c[4][4];
{
	printf("\nC-loadmatrix:\n");
	printf("%f %f %f %f\n", c[0][0], c[0][1], c[0][2], c[0][3]);
	printf("%f %f %f %f\n", c[1][0], c[1][1], c[1][2], c[1][3]);
	printf("%f %f %f %f\n", c[2][0], c[2][1], c[2][2], c[2][3]);
	printf("%f %f %f %f\n\n", c[3][0], c[3][1], c[3][2], c[3][3]);
	fflush(stdout);
}

void
multmatrix(c)
	float	c[4][4];
{
	printf("\nC-multmatrix:\n");
	printf("%f %f %f %f\n", c[0][0], c[0][1], c[0][2], c[0][3]);
	printf("%f %f %f %f\n", c[1][0], c[1][1], c[1][2], c[1][3]);
	printf("%f %f %f %f\n", c[2][0], c[2][1], c[2][2], c[2][3]);
	printf("%f %f %f %f\n\n", c[3][0], c[3][1], c[3][2], c[3][3]);
	fflush(stdout);
}

void
getmatrix(c)
	float	c[4][4];
{
	printf("\nC-getmatrix:\n");
	fflush(stdout);
	c[0][0] = c[0][1] = c[0][2] = c[0][3] = 1.0;
	c[1][0] = c[1][1] = c[1][2] = c[1][3] = 2.0;
	c[2][0] = c[2][1] = c[2][2] = c[2][3] = 3.0;
	c[3][0] = c[3][1] = c[3][2] = c[3][3] = 4.0;
}

void
yobbarays(n)
	int	n;
{
	printf("\nC-yobbarays: %d\n", n);
	fflush(stdout);
}

int
getstring(bcol, s)
	int	bcol;
	char	*s;
{
	printf("\nC-getstring: bcol = %d setting s to 'Hello there - bonk'\n", bcol);
	fflush(stdout);
	strcpy(s, "Hello there - bonk");
	return (strlen(s));
}

float
getaspect()
{
	printf("\nC-getaspct: returning 0.75\n");
	fflush(stdout);
	return(0.75);
}

void
getfactors(x, y)
	float	*x, *y;
{
	printf("\nC-getfactors: returning 1.2, 1.3\n");
	fflush(stdout);
	*x = 1.2;
	*y = 1.3;
}

void
getdisplaysize(x, y)
	float	*x, *y;
{
	printf("\nC-getdisplaysize: returning 1024, 768\n");
	fflush(stdout);
	*x = 1024;
	*y = 768;
}

int
backbuffer()
{
	printf("\nC-backbuffer: returning 110\n");
	fflush(stdout);
	return (110);
}

void
frontbuffer()
{
	printf("\nC-frontbuffer:\n");
	fflush(stdout);
}

void
swapbuffers()
{
	printf("\nC-swapbuffers:\n");
	fflush(stdout);
}

void
up(a, b, c)
	float	a, b, c;
{
	printf("\nC-up: %f, %f, %f\n", a, b, c);
	fflush(stdout);
}

void
prefsize(a, b)
	int	a, b;
{
	printf("\nC-prefsize: %d, %d\n", a, b);
	fflush(stdout);
}

void
prefposition(a, b)
	int	a, b;
{
	printf("\nC-prefposition: %d, %d\n", a, b);
	fflush(stdout);
}

void
backface(i)
	int	i;
{
	printf("\nC-backface: %d\n", i);
	fflush(stdout);
}

void
backfacedir(i)
	int	i;
{
	printf("\nC-backfacedir: %d\n", i);
	fflush(stdout);
}
