
/*
 * Vogle driver for Sun using sunview.
 *
 */
#include <stdio.h>
#include <sys/termios.h>
#include <suntool/sunview.h>
#include <sys/filio.h>
#include <fcntl.h>
#include <errno.h>

#include "vogle.h"

#define STDMAPSIZE	16	/* map that can be used with buffering */
#define	CMAPSIZE	256
#define	STDFONTDIR	"/usr/lib/fonts/fixedwidthfonts/"

#define MIN(x,y)	((x) < (y) ? (x) : (y))
#define COL(c)		((usememory) ? (c) : (c) | (c << 4))

#define OP_WHITE	(PIX_SRC | PIX_COLOR(COL(7)) | PIX_DONTCLIP)
#define OP_BLACK	(PIX_SRC | PIX_COLOR(COL(0)) | PIX_DONTCLIP)
#define COL_WHITE	COL(7)
#define COL_BLACK	COL(0)

static Pixwin	*pw_tmp, *pw;

#ifdef BASE_COL_SET
static Pixwin	*pw0;
#endif

static Pixrect	*frontb, *backb;
static Pixfont	*font_id;
static int	inbackb;
static int	wfd, blanket_win;
static int	oldflags;
static unsigned char	quit_char, intr_char, susp_char;
static int	pwfd, h, w;
static int	colour, usememory, fmask, bmask, shift;
static u_char	fr[CMAPSIZE], fg[CMAPSIZE], fb[CMAPSIZE];
static u_char	br[CMAPSIZE], bg[CMAPSIZE], bb[CMAPSIZE];
static u_char	*red, *green, *blue;

/*
 * default colour map
 */
static u_char	defred[STDMAPSIZE] = {
			0, 255, 0, 255, 0, 255, 0, 255, 0,
		},
		defgreen[STDMAPSIZE] = {
			0, 0, 255, 255, 0, 0, 255, 255, 0,
		},
		defblue[STDMAPSIZE] = {
			0, 0, 0, 0, 255, 255, 255, 255, 0,
		};

/*
 * redisplay
 *
 *	redisplay the window.
 */
static void
redisplay()
{
	pw_damaged(pw);

	pw_repairretained(pw);

	pw_donedamaged(pw);
}

/*
 * SUN_init
 *
 *	initialises drawing canvas to occupy current window
 */
SUN_init()
{
	int		i, prefx, prefy, prefxs, prefys, bw;
	char		name[WIN_NAMESIZE];
	Inputmask	im;
	Rect		rect;
	struct termios	term;
	int		rootfd;

	pw = (Pixwin *)NULL;

#ifdef BASE_COL_SET
	pw0 = pw;
#endif

	/*
	 * get the gfx win so we have some default sizes to use
	 */
	we_getgfxwindow(name);
	pwfd = open(name, 2);
	win_getrect(pwfd, &rect);

	/*
	 * get a new window (either going to be a blanket window or
	 * a window in it's own right)
	 */
	if ((wfd = win_getnewwindow()) == -1) {
		fprintf(stderr, "No new windows!\n");
		exit(1);
	}

	getprefposandsize(&prefx, &prefy, &prefxs, &prefys);

	if (prefx > -1) {
		rect.r_left = prefx;
		rect.r_top = prefy;
	}

	if (prefxs > -1) {
		rect.r_width = prefxs;
		rect.r_height = prefys;
	}

	w = rect.r_width;
	h = rect.r_height;

	bw = 3;
	if (prefx > -1 || prefxs > -1) {
		/*
		 * Make room for a 3 pixel border
		 */
		if (rect.r_left <= 2)
			rect.r_left = 0;
		else
			rect.r_left -= bw;

		if (rect.r_top <= 2)
			rect.r_top = 0;
		else
			rect.r_top -= bw;

		rect.r_width += 2 * bw;
		rect.r_height += 2 * bw;

		win_setrect(wfd, &rect);

		/*
		 * get the parent (probably full screen window)
		 * so we can size our window to any size we like
		 * on the screen.
		 */
		we_getparentwindow(name);
		rootfd = open(name, 2);

		win_setlink(wfd, WL_PARENT, win_fdtonumber(rootfd));
		/*win_setlink(wfd, WL_PARENT, 0);*/
		win_setlink(wfd, WL_COVERED, WIN_NULLLINK);
		win_insert(wfd);

		wmgr_top(wfd, rootfd);

		pw = pw_open(wfd);
		/*pw_set_region_rect(pw, &rect, 1);*/
#ifdef BASE_COL_SET
		/*
		 * Get the pixrect for the window that we started in
		 * so we can set it's colourmap as well
		 */
		pw0 = pw_open(pwfd);
#endif

		close(rootfd);
		blanket_win = 0;
	} else {
		win_insertblanket(wfd, pwfd);
		pw = pw_region(pw_open(wfd), 0, 0, w, h);
		blanket_win = 1;
	}

	/*
	 * Set non-blocking input for window.
	 */
	oldflags = fcntl(wfd, F_GETFL, 0);
	if (fcntl(wfd, F_SETFL, FNDELAY) < 0) {
		perror("F_SETFL");
		exit(1);
	}

	/*
	 * Setup the input masks for window.
	 */

	/*
	 * Keyboard....
	 */
	input_imnull(&im);
	im.im_flags = IM_ASCII | IM_META;

	win_setinputcodebit(&im, SHIFT_CAPSLOCK);
	win_setinputcodebit(&im, SHIFT_LOCK);
	win_setinputcodebit(&im, SHIFT_LEFT);
	win_setinputcodebit(&im, SHIFT_RIGHT);
	win_setinputcodebit(&im, SHIFT_LEFTCTRL);
	win_setinputcodebit(&im, SHIFT_RIGHTCTRL);
	win_setinputcodebit(&im, SHIFT_META);
	win_setinputcodebit(&im, WIN_STOP);

        for (i = KEY_LEFTFIRST; i <= KEY_LEFTLAST; i++)
		win_setinputcodebit(&im, i);
        
        for (i = KEY_TOPFIRST; i <= KEY_TOPLAST; i++)
		win_setinputcodebit(&im, i);

        for (i = KEY_RIGHTFIRST; i <= KEY_RIGHTLAST; i++)
		win_setinputcodebit(&im, i);

	/* 
	 * Find out what the users INTR and QUIT and SUSP chars are.
	 */
	if (ioctl(0, TCGETS, &term) < 0) {
		perror("TCGETS");
		exit(1);
	}

	quit_char = term.c_cc[VQUIT];
	intr_char = term.c_cc[VINTR];
	susp_char = term.c_cc[VSUSP];

	win_set_kbd_mask(wfd, &im);

	/*
	 * Mouse ....
	 */
	input_imnull(&im);
        im.im_flags = IM_ASCII | IM_META | IM_NEGEVENT | IM_INTRANSIT;
 
        win_setinputcodebit(&im, LOC_MOVE);
        win_setinputcodebit(&im, LOC_DRAG);
        win_setinputcodebit(&im, MS_LEFT);
        win_setinputcodebit(&im, MS_MIDDLE);
        win_setinputcodebit(&im, MS_RIGHT);
        win_set_pick_mask(wfd, &im);

	vdevice.depth = pw->pw_pixrect->pr_depth;

	/* 
	 *  Set up the color map.  
	 */

	for (i = 0; i < CMAPSIZE; i++) {
		fr[i] = defred[i & 0x0f];
		fg[i] = defgreen[i & 0x0f];
		fb[i] = defblue[i & 0x0f];

		br[i] = defred[(i & 0xf0) >> 4];
		bg[i] = defgreen[(i & 0xf0) >> 4];
		bb[i] = defblue[(i & 0xf0) >> 4];
	}

	fr[255] = fg[255] = fb[255] = 255;
	br[255] = bg[255] = bb[255] = 255;

	red = fr;
	green = fg;
	blue = fb;

	if (vdevice.depth > 1) {
		pw_setcmsname(pw, "vogle");
		pw_putcolormap(pw, 0, CMAPSIZE, fr, fg, fb);
#ifdef BASE_COL_SET
		if (pw0 != (Pixwin *)NULL) {
			pw_setcmsname(pw0, "vogle");
			pw_putcolormap(pw0, 0, CMAPSIZE, fr, fg, fb);
		}
#endif
	}

	if (prefx > -1 || prefxs > -1) {
		/*
		 * Draw the border...
		 */
		int	x0, y0, x1, y1;

		x0 = y0 = 0;
		x1 = rect.r_width - 1;
		y1 = 0;
		pw_vector(pw, x0, y0, x1, y1, OP_WHITE, COL_WHITE);
		pw_vector(pw, x0 + 2, y0 + 2, x1 - 2, y1 + 2, OP_WHITE, COL_WHITE);
		pw_vector(pw, x0 + 1, y0 + 1, x1 - 1, y1 + 1, OP_BLACK, COL_BLACK);
		x0 = x1;
		y0 = y1;
		x1 = x0;
		y1 = rect.r_height - 1;
		pw_vector(pw, x0, y0, x1, y1, OP_WHITE, COL_WHITE);
		pw_vector(pw, x0 - 2, y0 + 2, x1 - 2, y1 - 2, OP_WHITE, COL_WHITE);
		pw_vector(pw, x0 - 1, y0 + 1, x1 - 1, y1 - 1, OP_BLACK, COL_BLACK);
		x0 = x1;
		y0 = y1;
		x1 = 0;
		y1 = rect.r_height - 1;
		pw_vector(pw, x0, y0, x1, y1, OP_WHITE, COL_WHITE);
		pw_vector(pw, x0 - 2, y0 - 2, x1 + 2, y1 - 2, OP_WHITE, COL_WHITE);
		pw_vector(pw, x0 - 1, y0 - 1, x1 + 1, y1 - 1, OP_BLACK, COL_BLACK);
		x0 = x1;
		y0 = y1;
		x1 = 0;
		y1 = 0;
		pw_vector(pw, x0, y0, x1, y1, OP_WHITE, COL_WHITE);
		pw_vector(pw, x0 + 2, y0 - 2, x1 + 2, y1 + 2, OP_WHITE, COL_WHITE);
		pw_vector(pw, x0 + 1, y0 - 1, x1 + 1, y1 + 1, OP_BLACK, COL_BLACK);

		pw_tmp = pw;
		pw = pw_region(pw_tmp, 3, 3, w, h);
		pw_close(pw_tmp);
	}


	frontb = pw->pw_prretained = mem_create(w, h, vdevice.depth);
	backb = (Pixrect *)NULL;

	fmask = 0xf0;
	bmask = 0x0f;

	signal(SIGWINCH, redisplay);

	/*
	 *  Let VOGLE know about the window size.
	 */
        vdevice.sizeX = vdevice.sizeY = MIN(w, h);
	vdevice.sizeSx = w;
	vdevice.sizeSy = h;

	return(1);
}

/*
 * SUN_exit
 *
 *	cleans up before returning the window to normal.
 */
SUN_exit()
{
	long	nbytes;
	int	i;
	Event	event;

	/*
	 * Flush all events for this window.
	 *
	 * While doing non-blocking input input_readevent returns -1 and
	 * errno == EWOULDBLOCK when everything has been read, so if 
	 * errno != EWOULDBLOCK then something naughty happened...
	 */
	while (input_readevent(wfd, &event) >= 0)
		;

	if (errno != EWOULDBLOCK) {
		perror("SUN_exit(flushing), input_readevent");
		exit();
	}

	/*
	 * reset wfd to blocking input.
	 */
	if (fcntl(wfd, F_SETFL, oldflags) < 0) {
		perror("oldflags, F_SETFL");
		exit(1);
	}

	if (blanket_win)
		win_removeblanket(wfd);
	else 
		win_remove(wfd);

	signal(SIGWINCH, SIG_DFL);

	return(1);
}

/*
 * SUN_draw
 *
 *	draws a line from the current graphics position to (x, y).
 *
 * Note: (0, 0) is defined as the top left of the window on a sun (easy
 * to forget).
 */
SUN_draw(x, y)
	int	x, y;
{
	pw_vector(pw, vdevice.cpVx, vdevice.sizeSy - vdevice.cpVy, x, vdevice.sizeSy - y, PIX_SRC | PIX_COLOR(COL(colour)), COL(colour));
}

/*
 * check_chars
 *
 *	Check if the incoming character is a quit, intr or susp
 *	and take the appropiate action. (ie. send the signals)
 */
static int
check_chars(i)
	int	i;
{
	if (i == intr_char) {
		kill(getpid(), SIGINT);
		/* shouldn't return  unless user has their own signal handler */
	} else if (i == quit_char) {
		kill(getpid(), SIGQUIT);
		/* shouldn't return  unless user has their own signal handler */
	} else if (i == susp_char) {
		kill(getpid(), SIGTSTP);
		return(1);
	} else
		return(i);
}

/*
 * SUN_getkey
 *
 *	grab a character from the keyboard.
 */
int
SUN_getkey()
{
	Event	event;

	do {
		while ((input_readevent(wfd, &event) < 0) && (errno == EWOULDBLOCK))
		;	/* Nothing to read - wait for something */
		
	} while (!event_is_ascii(&event));	/* Wait for a key press */

	return(check_chars(event_action(&event)));
}

/*
 * SUN_checkkey
 *
 *	Check if a keyboard key has been hit. If so return it.
 */

int
SUN_checkkey()
{
	Event	event;
	int	i;
	
	if (input_readevent(wfd, &event) < 0) {
		if (errno == EWOULDBLOCK) {
			return(0);
		} else {
			perror("SUN_checkkey, input_readevent");
			exit(1);
		}
	} else if ((i = event_action(&event)) >= ASCII_FIRST && i <= META_LAST) {
		return(check_chars(i));
	}
	return(0);
}
		

/*
 * SUN_locator
 *
 *	return the window location of the cursor, plus which mouse button,
 * if any, is been pressed.
 */
int
SUN_locator(wx, wy)
	int	*wx, *wy;
{
	*wx = win_get_vuid_value(wfd, LOC_X_ABSOLUTE);
	*wy = (int)vdevice.sizeSy - win_get_vuid_value(wfd, LOC_Y_ABSOLUTE);

	if (win_get_vuid_value(wfd, BUT(1)))
		return(1);

	if (win_get_vuid_value(wfd, BUT(2)))
		return(2);

	if (win_get_vuid_value(wfd, BUT(3)))
		return(4);

	return(0);
}

/*
 * SUN_clear
 *
 *	Clear the screen to current colour
 */
SUN_clear()
{
	pw_writebackground(pw, 0, 0, w, h, PIX_SRC | PIX_COLOR(COL(colour)) | PIX_DONTCLIP);
}

/*
 * SUN_color
 *
 *	set the current drawing color index.
 */
SUN_color(ind)
        int	ind;
{
	colour = ind;
}

/*
 * SUN_mapcolor
 *
 *	change index i in the color map to the appropriate r, g, b, value.
 */
SUN_mapcolor(i, r, g, b)
	int	i;
	int	r, g, b;
{
	int	j;

	if (i >= 255 || vdevice.depth == 1)
		return(-1);

	fr[i] = (u_char)r;
	fg[i] = (u_char)g;
	fb[i] = (u_char)b;

	if (i > 15)
		usememory = 1;
	else {
		defred[i] = r;
		defgreen[i] = g;
		defblue[i] = b;

		for (j = 0; j < CMAPSIZE; j++) {
			fr[i] = defred[j & 0x0f];
			fg[i] = defgreen[j & 0x0f];
			fb[i] = defblue[j & 0x0f];

			br[i] = defred[(j & 0xf0) >> 4];
			bg[i] = defgreen[(j & 0xf0) >> 4];
			bb[i] = defblue[(j & 0xf0) >> 4];
		}
	}

	/*
	 * gaurantee that background and forground differ
	 */
	fr[255] = (u_char)~fr[0];
	fg[255] = (u_char)~fg[0];
	fb[255] = (u_char)~fb[0];

	br[255] = (u_char)~br[0];
	bg[255] = (u_char)~bg[0];
	bb[255] = (u_char)~bb[0];

	pw_putcolormap(pw, 0, CMAPSIZE, red, green, blue);
}
	
/*
 * SUN_font
 *
 *   Set up a hardware font. Return 1 on success 0 otherwise.
 *
 */
SUN_font(fontfile)
        char	*fontfile;
{
	char	name[BUFSIZ];

	if (font_id != (Pixfont *)NULL)
		pf_close(font_id);

	if ((font_id = pf_open(fontfile)) == NULL)
		if (*fontfile != '/') {
			strcpy(name, STDFONTDIR);
			strcat(name, fontfile);
			if ((font_id = pf_open(name)) == NULL)
				return(0);
		} else 
			return(0);

	vdevice.hheight = font_id->pf_defaultsize.y;
	vdevice.hwidth = font_id->pf_defaultsize.x;

	return(1);
}

/* 
 * SUN_char
 *
 *	 outputs one char - is more complicated for other devices
 */
SUN_char(c)
	char	c;
{
	char	*s = " ";

	s[0] = c;
	pw_ttext(pw, vdevice.cpVx, (int)(vdevice.sizeSy - vdevice.cpVy), PIX_SRC | PIX_COLOR(COL(colour)), font_id, s);
}

/*
 * SUN_string
 *
 *	Display a string at the current drawing position.
 */
SUN_string(s)
        char	s[];
{
	pw_ttext(pw, vdevice.cpVx, (int)(vdevice.sizeSy - vdevice.cpVy), PIX_SRC | PIX_COLOR(COL(colour)), font_id, s);
}

/*
 * SUN_fill
 *
 *	fill a polygon
 */
SUN_fill(n, x, y)
	int	n, x[], y[];
{
	struct	pr_pos	vlist[128];
	int	i, npnts;

	if (n > 128)
		verror("vogle: more than 128 points in a polygon");

	npnts = n;

	for (i = 0; i < n; i++) {
		vlist[i].x = x[i];
		vlist[i].y = vdevice.sizeSy - y[i];
	}

	pw_polygon_2(pw, 0, 0, 1, &npnts, vlist, PIX_SRC | PIX_COLOR(COL(colour)) | PIX_DONTCLIP, (Pixwin *)NULL, 0, 0);

	vdevice.cpVx = x[n-1];
	vdevice.cpVy = y[n-1];
}

/*
 * SUN_backb
 *
 *	swap to memory only drawing (backbuffer) - a little slow but it
 * works on everything. Where we can, we use the frame buffer.
 */
SUN_backb()
{
	int	mask = 0xff;

	if (vdevice.depth == 1 || usememory) {
		if (vdevice.depth > 1)
			pw_putattributes(pw, &mask);

		if (backb == (Pixrect *)NULL) {
			if ((backb = mem_create((int)vdevice.sizeSx, (int)vdevice.sizeSy, vdevice.depth)) == (Pixrect *)NULL)
				return(-1);
		}

		if (pw->pw_prretained == backb)
			pw->pw_prretained = frontb;
		else
			pw->pw_prretained = backb;

		pw_batch_on(pw);
	} else {
		pw_getattributes(pw, &mask);
		if (mask == bmask) {
			red = fr;
			green = fg;
			blue = fb;
			pw_putattributes(pw, &fmask);
		} else {
			red = br;
			green = bg;
			blue = bb;
			pw_putattributes(pw, &bmask);
		}

		pw_setcmsname(pw, "vogle");
		pw_putcolormap(pw, 0, CMAPSIZE, red, green, blue);
	}

	return(0);
}

/*
 * SUN_swapb
 *
 *	swap the front and back buffers.
 */
SUN_swapb()
{
	int	mask = 0xff;

	if (vdevice.depth == 1 || usememory) {
		if (vdevice.depth > 1)
			pw_putattributes(pw, &mask);

		if (vdevice.inbackbuffer) {
			pw_batch_off(pw);
			if (pw->pw_prretained == backb)
				pw->pw_prretained = frontb;
			else
				pw->pw_prretained = backb;
			pw_batch_on(pw);
		} else {
			if (backb == (Pixrect *)NULL) {
				if ((backb = mem_create((int)vdevice.sizeSx, (int)vdevice.sizeSy, vdevice.depth)) == (Pixrect *)NULL)
					return(-1);
			}

			if (pw->pw_prretained == backb)
				pw->pw_prretained = frontb;
			else
				pw->pw_prretained = backb;
		}
	} else {

		pw_getattributes(pw, &mask);
		if (mask == bmask) {
			red = fr;
			green = fg;
			blue = fb;
			if (vdevice.inbackbuffer)
				pw_putattributes(pw, &fmask);
		} else {
			red = br;
			green = bg;
			blue = bb;
			if (vdevice.inbackbuffer)
				pw_putattributes(pw, &bmask);
		}

		pw_putcolormap(pw, 0, CMAPSIZE, red, green, blue);
	}

	return(0);
}

/*
 * SUN_frontb
 *
 *	draw in the front buffer
 */
SUN_frontb()
{
	int	mask;

	if (vdevice.depth == 1 || usememory)
		pw_batch_off(pw);
	else {
		if (vdevice.inbackbuffer) {
			mask = 0xff;
			pw_putattributes(pw, &mask);
		}
	}
}

/*
 * the device entry
 */
static DevEntry sundev = {
	"sun",
	"cour.r.24",
	"cour.r.12",
	SUN_backb,
	SUN_char,
	SUN_checkkey,
	SUN_clear,
	SUN_color,
	SUN_draw,
	SUN_exit,
	SUN_fill,
	SUN_font,
	SUN_frontb,
	SUN_getkey,
	SUN_init,
	SUN_locator,
	SUN_mapcolor,
	SUN_string,
	SUN_swapb
};

/*
 * _SUN_devcpy
 *
 *	copy the sun device into vdevice.dev.
 */
_SUN_devcpy()
{
	vdevice.dev = sundev;
}
