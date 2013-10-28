#include "vogle.h"

static	int	have_mouse = 0;

pc_locinit(x, y)
	int	x, y;
{
	if ((have_mouse = ismouse(x, y))) 
		showmouse();
}

int
pc_locator(x, y)
	int *x, *y;
{
	int ix, iy, b;

	if (!have_mouse) 
		return (-1);


	b = readmouse(&ix, &iy);

	*x = ix;
	*y = vdevice.sizeSy - iy;
	return (b);
}
