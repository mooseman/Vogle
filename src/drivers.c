#include <stdio.h>
#include "vogle.h"

extern char	*getenv();

struct vdev	vdevice;

static FILE	*fp = stdout;

static int	allocated = 0;

/* device-independent function routines */

/*
 * voutput
 *
 *	redirect output - only for postscript, hpgl (this is not a feature)
 */
void
voutput(path)
	char	*path;
{
	char	buf[128];

	if ((fp = fopen(path, "w")) == (FILE *)NULL) {
		sprintf(buf, "voutput: couldn't open %s", path);
		verror(buf);
	}
}

/*
 * _voutfile
 *
 *	return a pointer to the current output file - designed for internal
 * use only.
 */
FILE *
_voutfile()
{
	return(fp);
}

/*
 * verror
 *
 *	print an error on the graphics device, and then exit. Only called
 * for fatal errors. We assume that stderr is always there.
 *
 */
void
verror(str)
	char	*str;
{
	if (vdevice.initialised)
		vexit();

	fprintf(stderr, "%s\n", str);
	exit(1);
}

/*
 * getdev
 *
 *	get the appropriate device table structure
 */
static
getdev(device)
	char	*device;
{
	if (device == (char *)NULL || *device == 0)
		if ((device = getenv("VDEVICE")) == (char *)NULL) 
			device = "";
	
#ifdef SUN
	if (strcmp(device, "sun") == 0)
		_SUN_devcpy();
	else
#endif
#ifdef X11
	if (strcmp(device, "X11") == 0)
		_X11_devcpy();
	else
#endif
#ifdef DECX11
	if (strcmp(device, "decX11") == 0)
		_DECX11_devcpy();
	else
#endif
#ifdef POSTSCRIPT
	if (strcmp(device, "postscript") == 0)
		_PS_devcpy();
	else
	if (strcmp(device, "postscriptp") == 0)
		_PSP_devcpy();
	else
#endif
#ifdef HPGL
	if (strcmp(device, "hpgl") == 0 || strcmp(device, "hpgla2") == 0)
		_HPGL_A2_devcpy();
	else if (strcmp(device, "hpgla1") == 0)
		_HPGL_A1_devcpy();
	else if (strcmp(device, "hpgla3") == 0)
		_HPGL_A3_devcpy();
	else if (strcmp(device, "hpgla4") == 0)
		_HPGL_A4_devcpy();
	else
#endif
#ifdef DXY
	if (strcmp(device, "dxy") == 0)
		_DXY_devcpy();
	else
#endif
#ifdef TEK
	if (strcmp(device, "tek") == 0)
		_TEK_devcpy();
	else
#endif
#ifdef HERCULES
	if (strcmp(device, "hercules") == 0)
		_hgc_devcpy();
	else
#endif
#ifdef CGA
	if (strcmp(device, "cga") == 0)
		_cga_devcpy();
	else
#endif
#ifdef EGA
	if (strcmp(device, "ega") == 0)
		_ega_devcpy();
	else
#endif
#ifdef VGA
	if (strcmp(device, "vga") == 0)
		_vga_devcpy();
	else
#endif
#ifdef SIGMA
	if (strcmp(device, "sigma") == 0)
		_sigma_devcpy();
	else
#endif
	{
		fprintf(stderr, "vogle: %s is an invalid device type\n", device);
		fprintf(stderr, "The devices compiled into this library are:\n");
#ifdef SUN
		fprintf(stderr, "sun\n");
#endif
#ifdef X11
		fprintf(stderr, "X11\n");
#endif
#ifdef DECX11
		fprintf(stderr, "decX11\n");
#endif
#ifdef POSTSCRIPT
		fprintf(stderr, "postscript\n");
		fprintf(stderr, "postscriptp\n");
#endif
#ifdef HPGL
		fprintf(stderr, "hpgla1\n");
		fprintf(stderr, "hpgla2 (or hpgl)\n");
		fprintf(stderr, "hpgla3\n");
		fprintf(stderr, "hpgla4\n");
#endif
#ifdef DXY
		fprintf(stderr, "dxy\n");
#endif
#ifdef TEK
		fprintf(stderr, "tek\n");
#endif
#ifdef HERCULES
		fprintf(stderr, "hercules\n");
#endif
#ifdef CGA
		fprintf(stderr, "cga\n");
#endif
#ifdef EGA
		fprintf(stderr, "ega\n");
#endif
#ifdef VGA
		fprintf(stderr, "vga\n");
#endif
#ifdef SIGMA
		fprintf(stderr, "sigma\n");
#endif
		exit(1);
	}
}

/*
 * vinit
 *
 * 	initialise VOGLE
 *
 */
void
vinit(device)
	char	*device;
{
	getdev(device);

	if (vdevice.initialised)
		vexit();

	if (!allocated) {
		allocated = 1;
		vdevice.transmat = (Mstack *)vallocate(sizeof(Mstack));
		vdevice.transmat->back = (Mstack *)NULL;
		vdevice.attr = (Astack *)vallocate(sizeof(Astack));
		vdevice.attr->back = (Astack *)NULL;
		vdevice.viewport = (Vstack *)vallocate(sizeof(Vstack));
		vdevice.viewport->back = (Vstack *)NULL;
	}

	vdevice.clipoff = 0;
	vdevice.upset = 0;
	vdevice.cpW[V_W] = 1.0;			/* never changes */

	vdevice.attr->a.fill = 0;
	vdevice.attr->a.hatch = 0;
	vdevice.attr->a.backface = 0;
	vdevice.attr->a.centered = 0;
	vdevice.attr->a.textcos = 1.0;
	vdevice.attr->a.textsin = 0.0;
	vdevice.attr->a.fixedwidth = 0;
	vdevice.attr->a.hatchcos = 1.0;
	vdevice.attr->a.hatchsin = 0.0;
	vdevice.attr->a.hatchpitch = 0.1;

	if ((*vdevice.dev.Vinit)()) {
		vdevice.initialised = 1;

		viewport(-1.0, 1.0, -1.0, 1.0);

		identmatrix(vdevice.transmat->m);
		_mapmsave(vdevice.transmat->m);

		move(0.0, 0.0, 0.0);

		font("futura.l");	/* set up default font */

		textsize(0.05, 0.05);
		vdevice.inobject = 0;
		vdevice.inpolygon = 0;
	} else {
		fprintf(stderr, "vogle: error while setting up device\n");
		exit(1);
	}
}

/*
 * vnewdev
 *
 * reinitialize vogle to use a new device but don't change any
 * global attributes like the window and viewport settings.
 */
void
vnewdev(device)
	char	*device;
{
	if (!vdevice.initialised)
		verror("vnewdev: vogle not initialised\n");

	pushviewport();	

	(*vdevice.dev.Vexit)();

	vdevice.initialised = 0;

	getdev(device);

	(*vdevice.dev.Vinit)();

	vdevice.initialised = 1;

	popviewport();
}

/*
 * vgetdev
 *
 *	Returns the name of the current vogle device 
 *	in the buffer buf. Also returns a pointer to
 *	the start of buf.
 */
char	*
vgetdev(buf)
	char	*buf;
{
	/*
	 * Note no exit if not initialized here - so that vexit
	 * can be called before printing the name.
	 */
	if (vdevice.dev.devname)
		strcpy(buf, vdevice.dev.devname);
	else
		strcpy(buf, "(no device)");

	return(&buf[0]);
}


/*
 * getkey
 *
 *	returns the next key pressed.
 */
int
getkey()
{
	if (!vdevice.initialised)
		verror("getkey: vogle not initialised\n");

	return((*vdevice.dev.Vgetkey)());
}

/*
 * checkkey
 *
 *	returns true if a key has been hit, or 0 otherwise
 *	(doesn't wait around like getkey)
 */
int
checkkey()
{
	if (!vdevice.initialised)
		verror("checkkey: vogle not initialised\n");

	return((*vdevice.dev.Vcheckkey)());
}

/*
 * locator
 *
 *	returns the current position of the crosshair or equivalent
 * in world coordinates, and the mouse buttons pressed (if any).
 */
int
locator(wx, wy)
	float	*wx, *wy;
{
	int	a, b, c;

	if (!vdevice.initialised)
		verror("locator: vogle not initialised");

	c = (*vdevice.dev.Vlocator)(&a, &b);
	VtoWxy((float)a, (float)b, wx, wy);

	return(c);
}

/*
 * slocator
 *
 *	returns the current position of the crosshair or equivalent
 * in screen coordinates, and the mouse buttons pressed (if any).
 */
int
slocator(wx, wy)
	float	*wx, *wy;
{
	int	a, b, c;
	float	sx, sy;

	if (!vdevice.initialised)
		verror("slocator: vogle not initialised");

	c = (*vdevice.dev.Vlocator)(&a, &b);
	sx = vdevice.sizeX;
	sy = vdevice.sizeY;

	*wx = a / (0.5 * sx) - 1.0;
	*wy = b / (0.5 * sy) - 1.0;

	return(c);
}

/*
 * clear
 *
 *	clears the screen to the current colour, excepting devices
 * like a laser printer where it flushes the page.
 *
 */
void
clear()
{
	Token	*tok;

	if (!vdevice.initialised)
		verror("clear: vogle not initialised");

	if (vdevice.inobject) {
		tok = newtokens(1);
		tok->i = CLEAR;

		return;
	}

	(*vdevice.dev.Vclear)();
}

/*
 * vexit
 *
 *	exit the vogle system
 *
 */
void
vexit()
{
	if (!vdevice.initialised)
		verror("vexit: vogle not initialised");

	(*vdevice.dev.Vexit)();

	vdevice.initialised = 0;
	fp = stdout;
}

/*
 * color
 *
 *	set the current colour to colour index number i.
 *
 */
void
color(i)
	int	i;
{
	Token	*tok;

	if (!vdevice.initialised)
		verror("color: vogle not initialised");

	if (vdevice.inobject) {
		tok = newtokens(2);

		tok[0].i = COLOR;
		tok[1].i = i;
		return;
	}

	vdevice.attr->a.color = i;
	(*vdevice.dev.Vcolor)(i);
}

/*
 * mapcolor
 *
 *	set the color of index i.
 */
void
mapcolor(i, r, g, b)
	int	i;
	short	r, g, b;
{
	Token	*tok;

	if (!vdevice.initialised)
		verror("mapcolor: vogle not initialised");

	if (vdevice.inobject) {
		tok = newtokens(5);

		tok[0].i = MAPCOLOR;
		tok[1].i = i;
		tok[2].i = r;
		tok[3].i = g;
		tok[4].i = b;

		return;
	}

	(*vdevice.dev.Vmapcolor)(i, r, g, b);
}

/*
 * getdepth
 *
 *	Returns the number if bit planes on a device.
 */
int
getdepth()
{
	if (!vdevice.initialised)
		verror("getdepth: vogle not initialised\n");

	return(vdevice.depth);
}
