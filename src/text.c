#include <fcntl.h>
#include <stdio.h>

#ifdef	TC

extern	double	cos();
extern	double	sin();

#else 

#include <math.h>

#endif

#ifdef PC
#include <string.h>
#else
#include <strings.h>
#endif
#include "vogle.h"

#define	MAX(a, b)	((a) < (b) ? (b) : (a))
#define	XCOORD(x)	((x) - 'R')
#define	YCOORD(y)	('R' - (y))

static	float	SCSIZEX = 1.0, SCSIZEY = 1.0;
static	int	SoftText = 0, Loaded = 0;
static	short	nchars;


static	char	errmsg1[120] = "font: unable to open ";

static	struct	{
	char	*p;	/* All the vectors in the font */
	char	**ind;	/* Pointers to where the chars start in p */
	int	as;	/* Max ascender of a character in this font */
	int	dec;	/* Max decender of a character in this font */
	int	mw;	/* Max width of a character in this font */
} ftab;

float	strlength();
void	actual_move();
void	drawhardchar();
float	getfontwidth();
float	getfontheight();

extern char	*getenv();

/*
 * font
 * 	loads in a font.
 */
void
font(name)
	char	*name;
{
	Token	*tok;

	if (!vdevice.initialised)
		verror("font: vogle not initialised");

	if (vdevice.inobject) {
		tok = newtokens(2 + strlen(name) / sizeof(Token));
		tok[0].i = FONT;
		strcpy((char *)&tok[1], name);

		return;
	}

	/*
	 * check we aren't loading the same font twice in a row
	 */
#ifdef PC
	if (*name == '\\') {
		if (strcmp(strrchr(name, '\\') + 1, vdevice.attr->a.font) == 0)
			return;
#else
	if (*name == '/') {
		if (strcmp(rindex(name, '/') + 1, vdevice.attr->a.font) == 0)
			return;
#endif
	} else if (strcmp(name, vdevice.attr->a.font) == 0)
		return;

	SoftText = 0;
	if (hershfont(name)) {
		SoftText = 1;
	} else if (strcmp(name, "large") == 0) {
		if (!(*vdevice.dev.Vfont)(vdevice.dev.large)) 
			verror("font: unable to open large font");
	} else if (strcmp(name, "small") == 0) {
		if (!(*vdevice.dev.Vfont)(vdevice.dev.small))
			verror("font: unable to open small font");
	} else if (!(*vdevice.dev.Vfont)(name)) {
		strcat(errmsg1, "fontfile ");
		strcat(errmsg1, name);
		verror(errmsg1);
	}

#ifdef PC
	if (*name == '\\')
		strcpy(vdevice.attr->a.font, strrchr(name, '\\') + 1);
#else
	if (*name == '/')
		strcpy(vdevice.attr->a.font, rindex(name, '/') + 1);
#endif
	else 
		strcpy(vdevice.attr->a.font, name);
}

/*
 * numchars
 *
 *	return the number of characters in the currently loaded hershey font.
 *	(The 128 is the number of chars in a hardware font)
 */
int
numchars()
{
	if (SoftText)
		return((int)nchars);

	return(128);
}

/*
 * hershfont
 *
 * Load in a hershey font. First try the font library, if that fails try
 * the current directory, otherwise return 0.
 */
static int
hershfont(fontname)
	char	*fontname;
{
	int	fd, i, j;
	short	nvects, n;
	char	path[120], *flib;
	
	if ((flib = getenv("VFONTLIB")) == (char *)NULL) {
		strcpy(path, FONTLIB);
		strcat(path, fontname);
	} else {
		strcpy(path, flib);
#ifdef PC
		strcat(path, "\\");
#else
		strcat(path, "/");
#endif
		strcat(path, fontname);
	}

#ifdef PC	/* Binary mode stupidity */
	if ((fd = open(path, O_RDONLY | O_BINARY)) < 0) 
		if ((fd = open(fontname, O_RDONLY | O_BINARY)) < 0) 
#else
	if ((fd = open(path, O_RDONLY)) < 0) 
		if ((fd = open(fontname, O_RDONLY)) < 0) 
#endif
			return (0);

	/*
	 * In case you're wondering, the reason I don't just read in
	 * a structure here is that some machines do this funny
	 * alignment thing and that stuffs up the structures sometimes.
	 */
	if (read(fd, &nchars, sizeof(nchars)) != sizeof(nchars))
		return (0);

	if (read(fd, &nvects, sizeof(nvects)) != sizeof(nvects))
		return(0);

	if (read(fd, &n, sizeof(n)) != sizeof(n))
		return(0);

	ftab.as = (int)n;

	if (read(fd, &n, sizeof(n)) != sizeof(n))
		return(0);

	ftab.dec = (int)n;

	if (read(fd, &n, sizeof(n)) != sizeof(n))
		return(0);

	ftab.mw = (int)n;

	/*
	 *  Allocate space for it all....
	 */
	if (Loaded) {
		if (ftab.ind[0])
			free(ftab.ind[0]);
		if (ftab.ind)
			free(ftab.ind);
		Loaded = 0;
	}

	ftab.ind = (char **)vallocate(sizeof(char *)*(nchars + 1));

	ftab.p = (char *)vallocate((unsigned)(2 * nvects));

	/*
	 *  As we read in each character, figure out what ind should be
	 */

	for (i = 0; i < nchars; i++) {
		if ((j = read(fd, &n , sizeof(n))) != sizeof(n))
			return(0);

		if ((j = read(fd, ftab.p, (unsigned)n)) != (unsigned)n)
			return(0);

		ftab.ind[i] = ftab.p;
		ftab.p += n;
	}
	ftab.ind[nchars] = ftab.p;	/* To Terminate the last one */

	close(fd);
	Loaded = 1;
	return(1);
}

/*
 * getcharsize
 *
 *	get the width and height of a single character. At the moment, for
 * the hershey characters, the height returned is always that of the
 * difference between the maximun descender and ascender.
 *
 */
void
getcharsize(c, width, height)
	char	c;
	float	*width, *height;
{

	float	a, b;

	if (!vdevice.initialised)
		verror("getcharsize: vogle not initialised");

	if (SoftText) {
		if (!Loaded)
			verror("getcharsize: no software font loaded");
	
		*height = (float)(ftab.as - ftab.dec) * SCSIZEY;

		if (vdevice.attr->a.fixedwidth)
			*width = ftab.mw * SCSIZEX;
		else
			*width = (ftab.ind[c - 32][1] - ftab.ind[c - 32][0]) * SCSIZEX;
	} else {
		VtoWxy(vdevice.hwidth, vdevice.hheight, width, height);
		VtoWxy(0.0, 0.0, &a, &b);
		*height -= a;
		*width -= b;
	}
}

/*
 * drawchar
 *
 * Display a character from the currently loaded font.
 */
void
drawchar(c)
	int	c;
{
	char	*p, *e;
	Token	*pr;
	int	Move, i, x, y, xt, yt;
	float	xp, yp, tmp, xsave, ysave;
	float	a, b, tcos, tsin;

	if (vdevice.inobject) {
		pr = newtokens(2);

		pr[0].i = DRAWCHAR;
		pr[1].i = c;

		return;
	}

	if (!SoftText) {
		drawhardchar(c);
		rmove2(getfontwidth(), 0.0);
		return;
	}

	if (!Loaded)
		verror("drawchar: no font loaded");

	tcos = vdevice.attr->a.textcos;
	tsin = vdevice.attr->a.textsin;

	if ((i = c - 32) < 0)
		i = 0;
	if (i >= nchars)
		i = nchars - 1;

	xsave = vdevice.cpW[V_X];
	ysave = vdevice.cpW[V_Y];

	Move = 1;
	xt = vdevice.attr->a.centered ? 0 : (vdevice.attr->a.fixedwidth ? -ftab.mw / 2 : XCOORD(ftab.ind[i][0]));
	yt = vdevice.attr->a.centered ? 0 : ftab.dec;

	e = ftab.ind[i+1];
	p = ftab.ind[i] + 2;
	while(p < e) {
		x = XCOORD((int)(*p++));
		y = YCOORD((int)(*p++));
		if (x != -50) {			/* means move */
			xp = (float)(x - xt)*SCSIZEX;
			yp = (float)(y - yt)*SCSIZEY;
			tmp = xp;
			xp = tcos*tmp - tsin*yp + xsave;
			yp = tsin*tmp + tcos*yp + ysave;
			if (Move) {
				Move = 0;
				move(xp, yp, vdevice.cpW[V_Z]);
			} else 
			        draw(xp, yp, vdevice.cpW[V_Z]);
		} else
			Move = 1;
	}
	/*
	 * Move to right hand of character.
	 */
	
	tmp = vdevice.attr->a.fixedwidth ? (float)ftab.mw : (float)(ftab.ind[i][1] - ftab.ind[i][0]);
	tmp *= SCSIZEX;
	xsave += tcos*tmp;
	ysave += tsin*tmp;
	move(xsave, ysave, vdevice.cpW[V_Z]);
}

/*
 * drawhardchar
 *
 *	Displays a hardware character.
 *	NOTE: Only does gross clipping to the viewport.
 *	      Current world position becomes undefined (ie you have
 *	      to do an explicit move after calling hardware text)
 */
static void
drawhardchar(c)
	char	c;
{
	if (!vdevice.cpVvalid)
		actual_move();

	if (!vdevice.clipoff) {
		if (vdevice.cpVx - (int)vdevice.hwidth > vdevice.maxVx)
			return;

		if (vdevice.cpVx < vdevice.minVx)
			return;

		if (vdevice.cpVy - (int)vdevice.hheight > vdevice.maxVy)
			return;

		if (vdevice.cpVy < vdevice.minVy)
			return;
	}

	(*vdevice.dev.Vchar)(c);
}

/*
 * textsize
 *
 * set software character scaling values 
 *
 * Note: Only changes software char size. Should be called
 * after a font has been loaded.
 *
 */
void
textsize(width, height)
	float	width, height;
{
	float	a;
	Token	*tok;

	if (!vdevice.initialised)
		verror("textsize: vogle not initialised");

	if (!SoftText)
		return;

	if (!Loaded)
		verror("textsize: no font loaded");

	if (vdevice.inobject) {
		tok = newtokens(3);

		tok[0].i = TEXTSIZE;
		tok[1].f = width;
		tok[2].f = height;

		return;
	}

	a = (float)MAX(ftab.mw, (ftab.as - ftab.dec));
	SCSIZEX = width / a;
	SCSIZEY = height / a;
}

/*
 * getfontwidth
 *
 * Return the maximum Width of the current font.
 *
 */
float
getfontwidth()
{
	float	a, b, c, d;

	if (!vdevice.initialised)
		verror("getfontwidth: vogle not initialised");


	if (SoftText) {
		if (!Loaded)
			verror("getfontwidth: No font loaded");

		return((float)(SCSIZEX * MAX(ftab.mw, (ftab.as - ftab.dec))));
	} else {
		VtoWxy(vdevice.hwidth, vdevice.hheight, &c, &d);
		VtoWxy(0.0, 0.0, &a, &b);
		c -= a;
		return(c);
	}
}

/* 
 * getfontheight
 *
 * Return the maximum Height of the current font
 */
float 
getfontheight()
{
	float	a, b, c, d;

	if (!vdevice.initialised)
		verror("getfontheight: vogle not initialized");

	if (SoftText) {
		if (!Loaded)
			verror("getfontheight: No font loaded");

		return((float)(SCSIZEY * MAX(ftab.mw, (ftab.as - ftab.dec))));
	} else {
		VtoWxy(vdevice.hwidth, vdevice.hheight, &c, &d);
		VtoWxy(0.0, 0.0, &a, &b);
		d -= b;
		return(d);
	}
}

/*
 * getfontsize
 *
 * get the current character size in user coords.
 * Hardware text may or may not be really that accurate,
 * depending on what type of font you are using on the device.
 * For software Hershey fonts, the character width is that of
 * a the widest character and the height the height of the tallest.
 *
 */
void
getfontsize(cw, ch)
	float 	*cw, *ch;
{
	*cw = getfontwidth();
	*ch = getfontheight();
}

/*
 * drawhstr
 *
 * Display the text string using the currently loaded Hershey font
 */
static void
drawhstr(string)
	char	*string;
{
	char	c;
	int	i, oldClipoff, NeedClip, oldCentered;
	float	p[4], q[4];
	float	strlength(), getfontheight();


	if (!vdevice.initialised) 
		verror("drawhstr: not initialized");

	/*
	 * For the duration of hershey strings, turn off
	 * "vdevice.attr->a.centered" as we have already compensated
	 * for it in drawstr()
	 */
	oldCentered = vdevice.attr->a.centered;
	vdevice.attr->a.centered = 0;

	/*
	 * Determine if we can get away with "clipoff"
	 */
	oldClipoff = vdevice.clipoff;
	if (!oldClipoff) {  /* Only do this if we have to ... ie. if clipping is on */
		q[0] = vdevice.cpW[V_X];
		q[1] = vdevice.cpW[V_Y];
		q[2] = vdevice.cpW[V_Z];
		q[3] = 1.0;
		multvector(p, q, vdevice.transmat->m);
		NeedClip = 0;
		for (i = 0; i < 3; i++)
			NeedClip = ((p[3] + p[i] < 0.0) ||
				    (p[3] - p[i] < 0.0)) || NeedClip;
		if (!NeedClip) {   	/* The other end, only if we have to */
			q[0] += strlength(string);
			q[1] += getfontheight();
			multvector(p, q, vdevice.transmat->m);
			NeedClip = 0;
			for (i = 0; i < 3; i++)
				NeedClip = ((p[3] + p[i] < 0.0) || 
					    (p[3] - p[i] < 0.0)) || NeedClip;
		}
		if (!NeedClip)
			vdevice.clipoff = 1; /* ie. Don't clip */

	}

	/*
	 * Now display each character
	 *
	 */
	while (c = *string++)
		drawchar(c);
	
	/*
	 * Restore ClipOff
	 */
	vdevice.clipoff = oldClipoff;
	vdevice.attr->a.centered = oldCentered;
}

/*
 * drawstr
 *
 * Draw a string from the current pen position.
 *
 */
void
drawstr(string)
	char 	*string;
{
	float	sl, width, height, cx, cy;
	float	tcos, tsin;
	char	*str = string, c;
	Token	*tok;

	if(!vdevice.initialised) 
		verror("drawstr: vogle not initialized");

	if (vdevice.inobject) {
		tok = newtokens(2 + strlen(str) / sizeof(Token));

		tok[0].i = DRAWSTR;
		strcpy((char *)&tok[1], str);

		return;
	}

	sl = (float)strlen(string);

	tcos = vdevice.attr->a.textcos;
	tsin = vdevice.attr->a.textsin;

	height = getfontheight() / 2.0;
	width = strlength(string) / 2.0;

	cx = vdevice.cpW[V_X];
	cy = vdevice.cpW[V_Y];

	if (vdevice.attr->a.centered) {
		cx = vdevice.cpW[V_X] + height * tsin - width * tcos;
		cy = vdevice.cpW[V_Y] - height * tcos - width * tsin;
		move(cx, cy, vdevice.cpW[V_Z]);
	}

	if (SoftText) 

		/*  As we are using software text then call the routine 
			    to display it in the current font */

		drawhstr(string);
	else {
		actual_move();	/* Really move there */

		/*   If not clipping then simply display text and return  */

		if (vdevice.clipoff)
			(*vdevice.dev.Vstring)(string);
		else { /* Check if string is within viewport */
			if (vdevice.cpVx > vdevice.minVx &&
			    vdevice.cpVx + (int)(sl * (vdevice.hwidth - 1)) < vdevice.maxVx &&
			    vdevice.cpVy - (int)vdevice.hheight < vdevice.maxVy &&
		            vdevice.cpVy > vdevice.minVy)
				(*vdevice.dev.Vstring)(string);
			else
				while (c = *str++) {
					drawhardchar(c);
					vdevice.cpVx += vdevice.hwidth;
				}
		}

		move(cx + getfontwidth() * sl, cy, vdevice.cpW[V_Z]);

	}
}

/*
 * istrlength
 *
 * Find out the length of a string in raw "Hershey coordinates".
 */
static	int
istrlength(s)
	char	*s;
{
	char	c;
	int	i, len = 0;
	
	if (vdevice.attr->a.fixedwidth) 
		return((float)(strlen(s) * ftab.mw));
	else {
		while (c = *s++) {
			if ((i = (int)c - 32) < 0 || i >= nchars)
				i = nchars - 1;

			len += (ftab.ind[i][1] - ftab.ind[i][0]);
		}
		return (len);
	}
}

/*
 * strlength
 *
 * Find out the length (in world coords) of a string.
 *
 */
float
strlength(s)
	char	*s;
{
	if (!vdevice.initialised)
		verror("strlength: vogle not initialised");

	if (SoftText)
		return((float)(istrlength(s) * SCSIZEX));
	else
		return((float)(strlen(s) * getfontwidth()));
}

/*
 * boxtext
 *
 * Draw text so it fits in a "box" - note only works with hershey text
 */
void
boxtext(x, y, l, h, s)
	float	x, y, l, h;
	char	*s;
{
	float	oscsizex, oscsizey;
	Token	*tok;

	if (!vdevice.initialised)
		verror("boxtext: vogle not initialised");
	
	if (!SoftText)
		verror("boxtext: need a hershey vector font loaded");

	if (vdevice.inobject) {
		tok = newtokens(6 + strlen(s) / sizeof(Token));

		tok[0].i = BOXTEXT;
		tok[1].f = x;
		tok[2].f = y;
		tok[3].f = l;
		tok[4].f = h;
		strcpy((char *)&tok[5], s);

		return;
	}

	oscsizex = SCSIZEX;
	oscsizey = SCSIZEY;
	/*
	 * set width so string length is the same a "l" 
	 */
	SCSIZEX = l / (float)istrlength(s);

	/* 
	 * set character height so it's the same as "h" 
	 */
	SCSIZEY = h / (float)(ftab.as - ftab.dec);
	move(x, y, vdevice.cpW[V_Z]);
	drawstr(s);

	SCSIZEX = oscsizex;
	SCSIZEY = oscsizey;
}

/*
 * boxfit
 *
 * Set up the scales etc for text so that a string of "nchars" characters
 * of the maximum width in the font fits in a box.
 */
void
boxfit(l, h, nchars)
	float	l, h;
	int	nchars;
{
	if (!vdevice.initialised) 
		verror("boxfit: vogle not initialised");

	if (!SoftText) 
		verror("boxfit: cannot rescale hardware font");

	SCSIZEX = l / (float)(nchars * ftab.mw);
	SCSIZEY = h / (float)(ftab.as - ftab.dec);
}
/*
 * centertext
 *
 *	Turns centering of text on or off
 */
void
centertext(onoff)
	int	onoff;
{
	vdevice.attr->a.centered = onoff;
}

/*
 * fixedwidth
 *
 *	Turns fixedwidth text on or off
 */
void
fixedwidth(onoff)
	int	onoff;
{
	vdevice.attr->a.fixedwidth = onoff;
}

/*
 * textang
 *
 * set software character angle in degrees
 *
 * strings will be written along a line 'ang' degrees from the 
 * horizontal screen direction
 *
 * Note: only changes software character angle
 *
 */
void
textang(ang)
	float	ang;
{
	Token	*tok;

	if (!vdevice.initialised) 
		verror("textang: vogle not initialised");

	if (vdevice.inobject) {
		tok = newtokens(3);

		tok[0].i = TEXTANG;
		tok[1].i = cos((double)(ang * D2R));
		tok[2].i = sin((double)(ang * D2R));

		return;
	}

	vdevice.attr->a.textcos = cos((double)(ang * D2R));
	vdevice.attr->a.textsin = sin((double)(ang * D2R));
}

/*
 * Actually do a move (multplying by the current transform and updating the
 * actual screen coords) instead of just setting the current spot in world
 * coords.
 */
static void
actual_move()
{
	Vector	v2;

	multvector(v2, vdevice.cpW, vdevice.transmat->m);
	vdevice.cpVvalid = 1;

	vdevice.cpVx = WtoVx(v2);
	vdevice.cpVy = WtoVy(v2);
	
	copyvector(vdevice.cpWtrans, v2);
}
