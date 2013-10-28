#include "vogle.h"

#define S_PIX_ASPECT	1.2 
static	int			old_mode = 3;
extern	unsigned int	_cur_color;
extern	unsigned int	_buffer_segment;

static	unsigned char 	pal[17] = {0, 4, 2, 14, 1, 5, 3, 15,
                        12, 10, 6, 9, 11, 13, 14, 15, 0};

extern	void	
		sig_line(),
		sig_set_colors();

extern	int	sigmaclear(),
		pc_fill(),
		pc_font(),
		pc_getkey(),
		pc_checkkey(),
		pc_locator(),
		pc_string(),
		setmode();

static	int
noop()
{
	return (-1);
}


static	unsigned	int	loc_val;

int
sigma_init()
{

	vdevice.sizeX = 399 * S_PIX_ASPECT;
	vdevice.sizeY = 399;
	vdevice.sizeSx = 639;
	vdevice.sizeSy = 399;
	vdevice.depth = 4;
	_buffer_segment = (unsigned)0xB800;
	old_mode = setmode(0x42);
	sigma_set_colors(pal);
	set_loc(64);
	pc_locinit(vdevice.sizeSx, vdevice.sizeSy);
	return (1);
}
/*
 * sigma_exit
 *
 *	Sets the display back to text mode.
 */
sigma_exit()
{
	unshowmouse();
	(void)setmode(3);
	return (1);
}

sigma_draw(x, y)
	int	x, y;
{
	sig_line(vdevice.cpVx, vdevice.sizeSy - vdevice.cpVy, x, vdevice.sizeSy - y, _cur_color);
	vdevice.cpVx = x;
	vdevice.cpVy = y;
}

sigma_char(c)
	int	c;
{
	sigmachar(c, vdevice.cpVx, vdevice.sizeSy - vdevice.cpVy, _cur_color);
}

sigma_color(i)
	int	i;
{
	_cur_color = (unsigned)i;
}

static DevEntry sigmadev = {
	"sigma",
	"large",
	"small",
	noop,
	sigma_char,
	pc_checkkey,
	sigmaclear,
	sigma_color,
	sigma_draw,
	sigma_exit,
	pc_fill,
	pc_font,
	noop,
	pc_getkey,
	sigma_init,
	pc_locator,
	noop,
	pc_string,
	noop
};

/*
 * _sigma_devcpy
 *
 *	copy the pc device into vdevice.dev.
 */
_sigma_devcpy()
{
	vdevice.dev = sigmadev;
}

