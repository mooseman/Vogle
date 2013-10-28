
#include <stdio.h>
#include "vogle.h"

#undef GREY_LINES	/* Or #define GREY_LINES */

extern FILE	*_voutfile();

static int	ps_first_time = 1, drawn = 0,
		curcol = 0,			/* black */
		pslstx = -1, pslsty = -1;	/* last (x, y) drawn */

/*
 * gray scale map for our standard colours
 */
static float	graymap[8] = {
			0.0,
			0.30,
			0.59,
			0.89,
			0.11,
			0.41,
			0.70,
			0.99
};

static FILE	*fp;

/*
 * noop
 *
 *	do nothing but return -1
 */
static int
noop()
{
	return(-1);
}

/*
 * PS_init
 *
 *	set up the postcript environment. Returns 1 on success.
 */
static
PS_init()
{
	fp = _voutfile();

	if (!ps_first_time)
		return(1);

	fputs("%!\n", fp);
	fprintf(fp, "72 300 div dup scale\n90 rotate\n400 -2200 translate\n");

	vdevice.sizeSy = 1890; 
	vdevice.sizeSx = 2634; 
	vdevice.sizeX = vdevice.sizeY = 1890; 

	PS_common_init();

	return (1);
}

/*
 * PSP_init
 *
 *	set up the postscript (Portrait) environment. Returns 1 on success.
 */
static
PSP_init()
{
	fp = _voutfile();

	if (!ps_first_time)
		return(1);

	fputs("%!\n", fp);
	fprintf(fp, "72 300 div dup scale\n300 400 translate\n");

	vdevice.sizeSy = 2634; 
	vdevice.sizeSx = 1890; 
	vdevice.sizeX = vdevice.sizeY = 1890; 

	PS_common_init();

	return (1);
}

/*
 * PS_common_init
 *
 *	 Initialization that is common to both layouts
 */
static
PS_common_init()
{

	vdevice.depth = 1;

	/*	Set other line drawing parameters	*/

	fprintf(fp, "2 setlinewidth\n1 setlinejoin\n1 setlinecap\n");

	/*	Speed up symbol font handling	*/

	fprintf(fp, "/sf /Courier findfont def\n");

	/*	Move	*/

	fprintf(fp, "/m /moveto load def\n");

	/*	Draw	*/

	fprintf(fp, "/d { lineto currentpoint stroke moveto } def\n");

	/*	Polygon Draw	*/

	fprintf(fp, "/p /lineto load def\n");

	/*	Set character height	*/

	fprintf(fp, "/h { sf exch scalefont setfont } def\n");

	/*	Show character string	*/

	fprintf(fp, "/s /show load def\n");

	/*	Set gray scale	*/

	fprintf(fp, "/g /setgray load def\n");

	/*	Set a default font height	*/
	
	fprintf(fp, "45 h\n");

	return(1);
}


/*
 * PS_exit
 *
 *	do a showpage and close the output file if neccessary.
 */
static
PS_exit()
{
	fprintf(fp, "showpage\n");
	fflush(fp);

	if (fp != stdout)
		fclose(fp);
}

/*
 * PS_draw
 *
 *	draw to an x, y point.
 */
static
PS_draw(x, y)
	int	x, y;
{
	if (pslstx != vdevice.cpVx || pslsty != vdevice.cpVy)
		fprintf(fp, "%d %d m\n", vdevice.cpVx, vdevice.cpVy);

	fprintf(fp, "%d %d d\n", x, y);
	pslstx = x;
	pslsty = y;
	drawn = 1;
}

/*
 * PS_font
 *
 * load in small or large - could be improved.
 */
static
PS_font(font)
	char	*font;
{
	if (strcmp(font, "small") == 0) {
		vdevice.hwidth = 22.0;
		vdevice.hheight = vdevice.hwidth * 1.833;
		fprintf(fp, "%d h\n", (int)vdevice.hheight);
	} else if (strcmp(font, "large") == 0) {
		vdevice.hwidth = 35.0;
		vdevice.hheight = vdevice.hwidth * 1.833;
		fprintf(fp, "%d h\n", (int)vdevice.hheight);

	} else
		return(0);

	return(1);
}

/*
 * PS_clear
 *
 *	flush the current page without resetting the graphics state of the
 * laser printer.
 */
static
PS_clear()
{
	if (drawn)
		fprintf(fp, "gsave showpage grestore\n");

	drawn = 0;
}

/*
 * PS_color
 *
 *	change the grey value of the ink
 */
static
PS_color(col)
	int	col;
{
	if (col > 7)
		return;

	curcol = col;

#ifdef GREY_LINES
	fprintf(fp, "%3.2f g\n", graymap[curcol]);
#endif
}
	
/*
 * PS_char
 *
 *	output a character making sure that a '\' is sent first when
 * appropriate.
 */
static
PS_char(c)
	char	c;
{
	int	dy, dx;

	if (pslstx != vdevice.cpVx || pslsty != vdevice.cpVy)
		fprintf(fp, "%d %d m\n", vdevice.cpVx, vdevice.cpVy);

	fprintf(fp, "(");

	switch(c) {
	case '(':
		fprintf(fp, "\\(");
		break;
	case ')':
		fprintf(fp, "\\)");
		break;
	case '\\':
		fprintf(fp, "\\");
		break;
	default:
		fprintf(fp, "%c",c);
	}

	fprintf(fp,") s \n");

	drawn = 1;
	pslstx = pslsty = -1;
}

/*
 * PS_string
 *
 *	output a string one char at a time.
 */
static
PS_string(s)
	char	*s;
{
	char	c;
	int	dy, dx;

	if (pslstx != vdevice.cpVx || pslsty != vdevice.cpVy)
		fprintf(fp, "%d %d m\n", vdevice.cpVx, vdevice.cpVy);

	fprintf(fp, "(");
	while (c = *s++)
		switch(c) {
		case '(':
			fprintf(fp, "\\(");
			break;
		case ')':
			fprintf(fp, "\\)");
			break;
		case '\\':
			fprintf(fp, "\\");
			break;
		default:
		fprintf(fp, "%c",c);
		}

	fprintf(fp,") s \n");
	drawn = 1;
	pslstx = pslsty = -1;
}

/*
 * PS_fill
 *
 *      fill a polygon
 */
static
PS_fill(n, x, y)
	int     n, x[], y[];
{
	int     i;


	fprintf(fp, "newpath \n");

	fprintf(fp, "%d %d m\n", x[0], y[0]);

	for (i = 1; i < n; i++)
		fprintf(fp, "%d %d p\n", x[i], y[i]);

	fprintf(fp, "closepath\n");

#ifndef GREY_LINES
	fprintf(fp, "%3.2f g\n", graymap[curcol]);
#endif

	fprintf(fp, "fill\n");

#ifndef GREY_LINES
	fprintf(fp, "0 g\n");
#endif

	vdevice.cpVx = x[n - 1];
	vdevice.cpVy = y[n - 1];

	pslstx = pslsty = -1;		/* fill destroys current path */
}

static DevEntry psdev = {
	"postscript",
	"large",
	"small",
	noop,
	PS_char,
	noop,
	PS_clear,
	PS_color,
	PS_draw,
	PS_exit,
	PS_fill,
	PS_font,
	noop,
	noop,
	PS_init,
	noop,
	noop,
	PS_string,
	noop
};

/*
 * _PS_devcpy
 *
 *	copy the postscript device into vdevice.dev.
 */
_PS_devcpy()
{
/*	- if you don't have structure assignment ...
	char    *dev, *tdev, *edev;
	dev = (char *)&psdev;
	tdev = (char *)&vdevice.dev;
	edev = dev + sizeof(Device);

	while (dev != edev)
		*tdev++ = *dev++;
*/

	vdevice.dev = psdev;
}

/*
 * _PSP_devcpy
 *
 *	copy the postscript portrait device into vdevice.dev.
 */
_PSP_devcpy()
{
/*	- if you don't have structure assignment ...
	char    *dev, *tdev, *edev;
	dev = (char *)&psdev;
	tdev = (char *)&vdevice.dev;
	edev = dev + sizeof(Device);

	while (dev != edev)
		*tdev++ = *dev++;
*/

	vdevice.dev = psdev;
	vdevice.dev.Vinit = PSP_init;
}


