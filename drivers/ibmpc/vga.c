#include	"vogle.h"

#define	V_PIX_ASPECT	1.0

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


vga_init()
{
	old_mode = setmode(18);
	vdevice.sizeX = 479 * V_PIX_ASPECT;
	vdevice.sizeY = 479;
	vdevice.sizeSx = 640;
	vdevice.sizeSy = 479;
	vdevice.depth = 4;
	_buffer_segment = 0xA000;
	_buffer_offset = 0;
	pc_locinit(vdevice.sizeSx, vdevice.sizeSy);
	zsetup();
	vega_setpal();
	return (1);
}

/*
 * vga_exit
 *
 *	Sets the display back to text mode.
 */
vga_exit()
{
	(void)setmode(old_mode);
	return (1);
}

static	int
noop()
{
	return (-1);
}

static DevEntry vgadev = {
	"vga",
	"large",
	"small",
	vega_backbuf,
	vega_char,
	pc_checkkey,
	vega_clear,
	vega_color,
	vega_draw,
	vga_exit,
	pc_fill,
	vega_font,
	vega_frontbuf,
	pc_getkey,
	vga_init,
	pc_locator,
	noop,
	vega_string,
	vega_swapbuf
};

/*
 * _vga_devcpy
 *
 *	copy the pc device into vdevice.dev.
 */
_vga_devcpy()
{
	vdevice.dev = vgadev;
}

