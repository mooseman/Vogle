/*
 * VOGLE driver for X11.
 */
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "vogle.h"

#define LARGEX11R2	"courier12f.snf"
#define SMALLX11R2	"courier10f.snf"

#define LARGEX11R3	"-adobe-courier-medium-r-normal--24-240-75-75-m-150-iso8859-1"
#define SMALLX11R3	"-adobe-courier-medium-r-normal--10-100-75-75-m-60-iso8859-1"

#define MIN(x,y)	((x) < (y) ? (x) : (y))
#define	CMAPSIZE	256
#define	EV_MASK		KeyPressMask|ButtonReleaseMask|ExposureMask|ButtonPressMask

static	Window		winder;
static	Display		*display;
static	int		screen;
static	unsigned long	carray[CMAPSIZE];
static	Colormap	colormap;

static	Drawable	theDrawable;
static	GC		theGC;
static	Pixmap		bbuf;		/* Back buffer pixmap */
static	int		back_used;	/* Have we backbuffered ? */

static	XFontStruct	*font_id;
XEvent			event;

static	int		size;
static	unsigned long	colour;
static	unsigned int	h, w;

/*
 * X11_init
 *
 *	initialises X11 display.
 */
X11_init()
{
	int		i;
	int		x, y, prefx, prefy, prefxs, prefys;
	unsigned int	bw, depth, mask;
	Window		rootw, childw;
	char		*av[2], name[50];

	XSetWindowAttributes    theWindowAttributes;
        XSizeHints              theSizeHints;
        unsigned long           theWindowMask;
	XWMHints                theWMHints;


	av[0] = "vogle.X11";
	av[1] = (char *)NULL;

	if ((display = XOpenDisplay((char *)NULL)) == (Display *)NULL) {
		fprintf(stderr,"vogle: X11_init: can't connect to X server\n");
		exit(1);
	}

	winder = DefaultRootWindow(display);
	screen = DefaultScreen(display);
	vdevice.depth = DefaultDepth(display, screen);
	colormap = DefaultColormap(display, screen);

	/*
	 * Set our standard colors...
	 */
	if (vdevice.depth == 1) {
		/*
		 * Black and white - anything that's not black is white.
		 */
		carray[0] = BlackPixel(display, screen);
		for (i = 1; i < CMAPSIZE; i++)
			carray[i] = WhitePixel(display, screen);
	} else {
		/*
		 * Color, try to get our colors close to what's in the
		 * default colormap.
		 */
		X11_mapcolor(0, 0, 0, 0);
		X11_mapcolor(1, 255, 0, 0);
		X11_mapcolor(2, 0, 255, 0);
		X11_mapcolor(3, 255, 255, 0);
		X11_mapcolor(4, 0, 0, 255);
		X11_mapcolor(5, 255, 0, 255);
		X11_mapcolor(6, 0, 255, 255);
		X11_mapcolor(7, 255, 255, 255);
	}

	getprefposandsize(&prefx, &prefy, &prefxs, &prefys);

	/*
	 * NEED TO USE XGRABPOINTER here???
	 */
	XQueryPointer(display, winder, &rootw, &childw, &x, &y, &x, &y, &mask);

	if (childw == None)
		childw = rootw;

	XGetGeometry(display, childw, &rootw, &x, &y, &w, &h, &bw, &depth);

	/*
	 * Tell the window manager not to fuck with this window...
	 * (and hope the bastard of a thing listens)
	 * Unless it's using prefsize of prefposition of course.
	 */
        theWindowAttributes.override_redirect = True;

	if (prefx > -1) {
		theWindowAttributes.override_redirect = False;
	        x = prefx;
	        y = prefy;
	}

	if (prefxs > -1) {
		theWindowAttributes.override_redirect = False;
	        w = prefxs;
	        h = prefys;
	}

	x += bw;
	y += bw;

	w -= 2 * bw;
	h -= 2 * bw;

        /*theWindowMask = CWBackPixel|CWBorderPixel|CWOverrideRedirect;*/
        theWindowMask = CWOverrideRedirect;

        winder = XCreateWindow(display,
                                winder,
                                x, y,
                                w, h,
                                bw,
                                (int)depth,
                                InputOutput,
                                CopyFromParent,
                                theWindowMask,
                                &theWindowAttributes
                        );

        theWMHints.initial_state = NormalState;
        theWMHints.input = True;
        theWMHints.flags = StateHint | InputHint;
        XSetWMHints(display, winder, &theWMHints);
 
        theSizeHints.flags = PPosition|PSize;
        theSizeHints.x = x;
        theSizeHints.y = y;
        theSizeHints.width = w;
        theSizeHints.height = h;
 
        XSetNormalHints(display, winder, &theSizeHints);

	sprintf(name, "vogle %d", getpid());

	XSetStandardProperties(display,
		winder,
		name,
		name,
		None,
		av,
		1,
		&theSizeHints
	);

	XSelectInput(display, winder, EV_MASK);

	theDrawable = (Drawable)winder;

	/*
	 *  Let VOGLE know about the window size.
	 */
	vdevice.sizeX = vdevice.sizeY = MIN(h, w) - 1;
	vdevice.sizeSx = w - 1;
	vdevice.sizeSy = h - 1;

	/*
	 * Create Graphics Context and Drawable
	 */
	theGC = XDefaultGC(display, screen);
	theDrawable = (Drawable)winder;
	X11_color(0);

	XMapRaised(display, winder);
	XFlush(display);

	/*
	 * Wait for Exposure event.
	 */
	do {
		XNextEvent(display, &event);
	} while (event.type != Expose);

	/*
	 * Set the input Focus to us.
	 */

        if (prefx == -1 && prefxs == -1)
                XSetInputFocus(display, winder, RevertToParent, CurrentTime);

	back_used = 0;
	return(1);
}

/*
 * X11_exit
 *
 *	cleans up before returning the window to normal.
 */
X11_exit()
{
	XFreeGC(display, theGC);

	if (back_used) 
		XFreePixmap(display, bbuf);

	XUnmapWindow(display, winder);

	XDestroyWindow(display, winder);

	return(1);
}

/*
 * X11_draw
 *
 *	draws a line from the current graphics position to (x, y).
 *
 * Note: (0, 0) is defined as the top left of the window in X (easy
 * to forget).
 */
X11_draw(x, y)
	int	x, y;
{
	XDrawLine(display,
		theDrawable,
		theGC,
		vdevice.cpVx, vdevice.sizeSy - vdevice.cpVy,
		x, vdevice.sizeSy - y
	);

	XFlush(display);
}

/*
 * X11_getkey
 *
 *	grab a character from the keyboard - blocks until one is there.
 */
int
X11_getkey()
{
	char	c;

	do {
		XNextEvent(display, &event);
		if (event.type == KeyPress) {
			if (XLookupString(&event, &c, 1, NULL, NULL) > 0)
				return((int)c);
			else
				return(0);
		}
	} while (event.type != KeyPress);
}

/*
 * X11_checkkey
 *
 *	Check if there has been a keyboard key pressed.
 *	and return it if there is.
 */
int
X11_checkkey()
{
	char	c;
	int	i;

	if (!XCheckWindowEvent(display, winder, KeyPressMask, &event))
		return(0);

	if (event.type == KeyPress)
		if (XLookupString(&event, &c, 1, NULL, NULL) > 0)
			return((int)c);

	return(0);
}

/*
 * X11_locator
 *
 *	return the window location of the cursor, plus which mouse button,
 * if any, is been pressed.
 */
int
X11_locator(wx, wy)
	int	*wx, *wy;
{
	Window	rootw, childw;
	int	x, y, mask;

	XQueryPointer(display, winder, &rootw, &childw, &x, &y, wx, wy, &mask);

	*wy = (int)vdevice.sizeSy - *wy;

	return(mask >> 8);
}

/*
 * X11_clear
 *
 * Clear the screen (or current buffer )to current colour
 */
X11_clear()
{
	XSetBackground(display, theGC, colour);
	XFillRectangle(display,
		theDrawable,
		theGC,
		0,
		0, 
		(unsigned int)vdevice.sizeSx + 1,
		(unsigned int)vdevice.sizeSy + 1
	);
}

/*
 * X11_color
 *
 *	set the current drawing color index.
 */
X11_color(ind)
        int	ind;
{
	colour = carray[ind];
	XSetForeground(display, theGC, colour);
}

/*
 * X11_mapcolor
 *
 *	change index i in the color map to the appropriate r, g, b, value.
 */
X11_mapcolor(i, r, g, b)
	int	i;
	int	r, g, b;
{
	int	stat;
	XColor	tmp;

	if (i >= CMAPSIZE)
		return(-1);


	/*
	 * For Black and White.
	 * If the index is 0 and r,g,b != 0 then we are remapping black.
	 * If the index != 0 and r,g,b == 0 then we make it black.
	 */
	if (vdevice.depth == 1) {
		if (i == 0 && (r != 0 || g != 0 || b != 0)) 
			carray[i] = WhitePixel(display, screen);
		else if (i != 0 && r == 0 && g == 0 && b == 0)
			carray[i] = BlackPixel(display, screen);
	} else {
		tmp.red = (unsigned short)(r / 255.0 * 65535);
		tmp.green = (unsigned short)(g / 255.0 * 65535);
		tmp.blue = (unsigned short)(b / 255.0 * 65535);
		tmp.flags = 0;
		tmp.pixel = (unsigned long)i;

		if ((stat = XAllocColor(display, colormap, &tmp)) == 0) {
			fprintf(stderr, "XAllocColor failed (status = %d)\n", stat);
			exit(1);
		}
		carray[i] = tmp.pixel;
	}

	XFlush(display);
	return(0);
}
	
/*
 * X11_font
 *
 *   Set up a hardware font. Return 1 on success 0 otherwise.
 *
 */
X11_font(fontfile)
        char	*fontfile;
{
	XGCValues	xgcvals;

	if (font_id != (XFontStruct *)NULL)
		XFreeFont(display, font_id);

	if (strcmp(fontfile, "small") == 0) {
		if ((font_id = XLoadQueryFont(display, SMALLX11R2)) == (XFontStruct *)NULL) {		/* X11 R2 */
			if ((font_id = XLoadQueryFont(display, SMALLX11R3)) == (XFontStruct *)NULL)	 	/* X11 R3 */
				return(0);
			else
				fontfile = SMALLX11R3;
		} else
			fontfile = SMALLX11R2;
	} else if (strcmp(fontfile, "large") == 0) {
		if ((font_id = XLoadQueryFont(display, LARGEX11R2)) == (XFontStruct *)NULL) {		/* X11 R2 */
			if ((font_id = XLoadQueryFont(display, LARGEX11R3)) == (XFontStruct *)NULL)	 	/* X11 R3 */
				return(0);
			else
				fontfile = LARGEX11R3;
		} else
			fontfile = LARGEX11R2;
	} else if ((font_id = XLoadQueryFont(display, fontfile)) == (XFontStruct *)NULL)
		return(0);

	vdevice.hheight = font_id->max_bounds.ascent + font_id->max_bounds.descent;
	vdevice.hwidth = font_id->max_bounds.width;

	xgcvals.font = XLoadFont(display, fontfile);
	XChangeGC(display, theGC, GCFont, &xgcvals);

	return(1);
}

/* 
 * X11_char
 *
 *	 outputs one char - is more complicated for other devices
 */
X11_char(c)
	char	c;
{
	char	*s = " ";

	s[0] = c;
	XDrawString(display, theDrawable, theGC, vdevice.cpVx, (int)(vdevice.sizeSy - vdevice.cpVy), s, 1);
	XFlush(display);
}

/*
 * X11_string
 *
 *	Display a string at the current drawing position.
 */
X11_string(s)
        char	s[];
{
	XDrawString(display, theDrawable, theGC, vdevice.cpVx, (int)(vdevice.sizeSy - vdevice.cpVy), s, strlen(s));
	XSync(display, 0);
}

/*
 * X11_fill
 *
 *	fill a polygon
 */
X11_fill(n, x, y)
	int	n, x[], y[];
{
	XPoint	plist[128];
	int	i;

	if (n > 128)
		verror("vogle: more than 128 points in a polygon");

	for (i = 0; i < n; i++) {
		plist[i].x = x[i];
		plist[i].y = vdevice.sizeSy - y[i];
	}

	XFillPolygon(display, theDrawable, theGC, plist, n, Nonconvex, CoordModeOrigin);

	vdevice.cpVx = x[n-1];
	vdevice.cpVy = y[n-1];

	XFlush(display);
}

#define	GC_COPY_MASK	~0

/*
 * X11_backbuf
 *
 *	Set up double buffering by allocating the back buffer and
 *	setting drawing into it.
 */
X11_backbuf()
{
	if (!back_used)
		bbuf = XCreatePixmap(display,
			(Drawable)winder,
			(unsigned int)vdevice.sizeSx + 1,
			(unsigned int)vdevice.sizeSy + 1,
			(unsigned int)vdevice.depth
		);

	theDrawable = (Drawable)bbuf;

	back_used = 1;

	return(1);
}

/*
 * X11_swapbuf
 *
 *	Swap the back and from buffers. (Really, just copy the
 *	back buffer to the screen).
 */
X11_swapbuf()
{
	XCopyArea(display,
		theDrawable,
		winder,
		theGC,
		0, 0,
		(unsigned int)vdevice.sizeSx + 1,
		(unsigned int)vdevice.sizeSy + 1,
		0, 0
	);

	XSync(display, 0);	/* Not XFlush */
}

/*
 * X11_frontbuf
 *
 *	Make sure we draw to the screen.
 */
X11_frontbuf()
{
	theDrawable = (Drawable)winder;
}

/*
 * the device entry
 */
static DevEntry X11dev = {
	"X11",
	"large",
	"small",
	X11_backbuf,
	X11_char,
	X11_checkkey,
	X11_clear,
	X11_color,
	X11_draw,
	X11_exit,
	X11_fill,
	X11_font,
	X11_frontbuf,
	X11_getkey,
	X11_init,
	X11_locator,
	X11_mapcolor,
	X11_string,
	X11_swapbuf
};

/*
 * _X11_devcpy
 *
 *	copy the X11 device into vdevice.dev.
 */
_X11_devcpy()
{
	vdevice.dev = X11dev;
}
