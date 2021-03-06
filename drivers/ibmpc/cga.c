#include	"vogle.h"
#include	<stdio.h>
#ifdef TC
#include	<dos.h>
#define		_dos_allocmem	allocmem
#define		_dos_freemem	freemem
#endif

#define		C_PIX_ASPECT	2.4
#define		NPARA	(640 * 200 / 16)

static	unsigned	allocated = 0, old_mode;
static	unsigned	char	*backbuf;

extern	unsigned	int	_buffer_segment;
extern	unsigned	int	_buffer_offset;
extern	unsigned	int	_cur_color;
static	unsigned	int	save_seg;

extern	int	cga_clear(),
		cga_frontbuf(),
		cga_swapbuf(),
		_cga_set_buffer(),
		pc_fill(),
		pc_font(),
		pc_getkey(),
		pc_checkkey(),
		pc_locator(),
		pc_string(),
		setmode();


cga_init()
{
	vdevice.sizeX = 199 * C_PIX_ASPECT;
	vdevice.sizeY = 199;
	vdevice.sizeSx = 640;
	vdevice.sizeSy = 199;
	vdevice.depth = 1;
	_buffer_segment = 0xB800;
	_buffer_offset = 0;
	_cur_color = 1;
	old_mode = setmode(6);
	pc_locinit(vdevice.sizeSx, vdevice.sizeSy);
	return (1);
}

/*
 * cga_exit
 *
 *	Sets the display back to text mode.
 */
cga_exit()
{
	unshowmouse();
	if (allocated)
		_dos_freemem(save_seg);

	setmode(old_mode);
	return (1);
}

cga_draw(x, y)
	int	x, y;
{
	cgaline(vdevice.cpVx, vdevice.sizeSy - vdevice.cpVy, x, vdevice.sizeSy - y, _cur_color);
	vdevice.cpVx = x;
	vdevice.cpVy = y;
}

cga_char(c)
	int	c;
{
	cgachar(c, vdevice.cpVx, vdevice.sizeSy - vdevice.cpVy, _cur_color, 1 - _cur_color);
}

cga_color(i)
	int	i;
{
	_cur_color = (i > 0 ? 1 : 0);
}

cga_backbuf()
{
	if (!allocated) {
		if (_dos_allocmem(NPARA, &_buffer_segment) != 0)
			verror("cga_backbuf: couldn't allocate space");

		allocated = 1;
		save_seg = _buffer_segment;
	}
	return(1);
}

static	int
noop()
{
	return (-1);
}

static DevEntry cgadev = {
	"cga",
	"large",
	"small",
	cga_backbuf,
	cga_char,
	pc_checkkey,
	cga_clear,
	cga_color,
	cga_draw,
	cga_exit,
	pc_fill,
	pc_font,
	cga_frontbuf,
	pc_getkey,
	cga_init,
	pc_locator,
	noop,
	pc_string,
	cga_swapbuf
};

/*
 * _cga_devcpy
 *
 *	copy the pc device into vdevice.dev.
 */
_cga_devcpy()
{
	vdevice.dev = cgadev;
}

