#include "vogle.h"

/*
 * backbuffer
 *
 *	swap drawing to backbuffer - returns -1 if no
 * backbuffer is available.
 */
int
backbuffer()
{
	vdevice.inbackbuffer = 1;

	return((*vdevice.dev.Vbackb)());
}

/*
 * frontbuffer
 *
 *	start drawing in the front buffer again. This
 * will always work!
 */
void
frontbuffer()
{
	(*vdevice.dev.Vfrontb)();

	vdevice.inbackbuffer = 0;
}

/*
 * swapbuffers
 *
 *	swap the back and front buffers - returns -1 if
 * no backbuffer is available.
 */
int
swapbuffers()
{
	if (vdevice.inbackbuffer != 1)
		verror("swapbuffers: double buffering not initialised.\n");

	return((*vdevice.dev.Vswapb)());
}
