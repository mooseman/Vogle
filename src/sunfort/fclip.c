#include "vogle.h"

/*
 * clipping
 *
 *	turn clipping on/off
 */
void
clipping_(onoff)
	int	*onoff;
{
	vdevice.clipoff = !*onoff;
}
