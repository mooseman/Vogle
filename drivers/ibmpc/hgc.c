#include "vogle.h"

#define H_PIX_ASPECT	1.45   /* For real PC monitor */
/*#define H_PIX_ASPECT	1.0	/* For SUN emulator */
extern	unsigned	int	_cur_color;

extern	void	
		hgc_tmode(),
		hgc_gmode(),
		hgc_config(),
		set_loc(),
		hgcline();

extern	int	hgc_clear(),
		hgc_backbuf(),
		pc_fill(),
		pc_font(),
		pc_getkey(),
		pc_checkkey(),
		pc_locator(),
		pc_string(),
		hgc_frontbuf(),
		hgc_swapbuf(),
		setmode();

static	int
noop()
{
	return (-1);
}


int
hgc_init()
{
	vdevice.sizeX = 347 * H_PIX_ASPECT;
	vdevice.sizeY = 347;
	vdevice.sizeSx = 719;
	vdevice.sizeSy = 347;
	vdevice.depth = 1;
	hgc_config();
	hgc_gmode();	/* Also sets _buffer_segment */
	_cur_color = 0;
	hgc_clear();
	_cur_color = 1;
	set_loc(5);	/* For the mouse */
	pc_locinit(vdevice.sizeSx, vdevice.sizeSy);
	return (1);
}
/*
 * hgc_exit
 *
 *	Sets the display back to text mode.
 */
hgc_exit()
{
	unshowmouse();
	/*hgc_tmode();
	_cur_color = 0;
	_hgc_clear();
	*/
	(void)setmode(3);
	return (1);
}

hgc_draw(x, y)
	int	x, y;
{
	hgcline(vdevice.cpVx, vdevice.sizeSy - vdevice.cpVy, x, vdevice.sizeSy - y, _cur_color);
	vdevice.cpVx = x;
	vdevice.cpVy = y;
}

hgc_char(c)
	int	c;
{
	hgcchar(c, vdevice.cpVx, vdevice.sizeSy - vdevice.cpVy, _cur_color, 1 - _cur_color);
}

hgc_color(i)
	int	i;
{
	_cur_color = (i > 0 ? 1 : 0);
}

static DevEntry hgcdev = {
	"hercules",
	"large",
	"small",
	hgc_backbuf,
	hgc_char,
	pc_checkkey,
	hgc_clear,
	hgc_color,
	hgc_draw,
	hgc_exit,
	pc_fill,
	pc_font,
	hgc_frontbuf,
	pc_getkey,
	hgc_init,
	pc_locator,
	noop,
	pc_string,
	hgc_swapbuf
};

/*
 * _hgc_devcpy
 *
 *	copy the pc device into vdevice.dev.
 */
_hgc_devcpy()
{
	vdevice.dev = hgcdev;
}

