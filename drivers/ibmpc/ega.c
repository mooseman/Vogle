#include	"vogle.h"

#define	E_PIX_ASPECT	1.3

static	int	old_mode;
extern	unsigned	int	_buffer_segment;
extern	unsigned	int	_buffer_offset;

extern	int
		vega_backbuf(),
		vega_char(),
		vega_clear(),
		vega_color(),
		vega_draw(),
		vega_setpal(),
		pc_fill(),
		vega_font(),
		vega_frontbuf(),
		pc_getkey(),
		pc_checkkey(),
		pc_locator(),
		vega_string(),
		vega_swapbuf(),
		setmode();

ega_init()
{
	old_mode = setmode(16);
	vdevice.sizeX = 349 * E_PIX_ASPECT;
	vdevice.sizeY = 349;
	vdevice.sizeSx = 640;
	vdevice.sizeSy = 349;
	vdevice.depth = 4;
	_buffer_segment = (unsigned) 0xA000;
	_buffer_offset = 0;
	pc_locinit(vdevice.sizeSx, vdevice.sizeSy);
	zsetup();
	vega_setpal();
	return (1);
}

/*
 * ega_exit
 *
 *	Sets the display back to text mode.
 */
ega_exit()
{
	(void)setmode(old_mode);
	return (1);
}

static	int
noop()
{
	return (-1);
}

static DevEntry egadev = {
	"ega",
	"large",
	"small",
	vega_backbuf,
	vega_char,
	pc_checkkey,
	vega_clear,
	vega_color,
	vega_draw,
	ega_exit,
	pc_fill,
	vega_font,
	vega_frontbuf,
	pc_getkey,
	ega_init,
	pc_locator,
	noop,
	vega_string,
	vega_swapbuf
};

/*
 * _ega_devcpy
 *
 *	copy the pc device into vdevice.dev.
 */
_ega_devcpy()
{
	vdevice.dev = egadev;
}

