#include <stdio.h>
#include "vogle.h"

static	Vstack	*vsfree = (Vstack *)NULL;

/*
 * pushviewport
 *
 * pushes the current viewport on the viewport stack
 *
 */
void
pushviewport()
{
	Vstack	*nvport;
	Token	*tok;

	if (!vdevice.initialised)
		verror("pushviewport: vogle not initialised");
	
	if (vdevice.inobject) {
		tok = newtokens(1);

		tok->i = PUSHVIEWPORT;

		return;
	}

	if (vsfree != (Vstack *)NULL) {
		nvport = vdevice.viewport;
		vdevice.viewport = vsfree;
		vsfree = vsfree->back;
		vdevice.viewport->back = nvport;
		vdevice.viewport->v.left = nvport->v.left;
		vdevice.viewport->v.right = nvport->v.right;
		vdevice.viewport->v.bottom = nvport->v.bottom;
		vdevice.viewport->v.top = nvport->v.top;
	} else {
		nvport = (Vstack *)vallocate(sizeof(Vstack));
		nvport->back = vdevice.viewport;
		nvport->v.left = vdevice.viewport->v.left;
		nvport->v.right = vdevice.viewport->v.right;
		nvport->v.bottom = vdevice.viewport->v.bottom;
		nvport->v.top = vdevice.viewport->v.top;
		vdevice.viewport = nvport;
	}
}

/*
 * popviewport
 *
 * pops the top viewport off the viewport stack.
 *
 */
void
popviewport()
{
	Token	*tok;
	Vstack	*nvport;

	if (!vdevice.initialised)
		verror("popviewport: vogle not initialised");
	
	if (vdevice.inobject) {
		tok = newtokens(1);

		tok->i = POPVIEWPORT;

		return;
	}

	if (vdevice.viewport->back == (Vstack *)NULL)
		verror("popviewport: viewport stack underflow");
	else {
		nvport = vdevice.viewport;
		vdevice.viewport = vdevice.viewport->back;
		nvport->back = vsfree;
		vsfree = nvport;
	}

	vdevice.maxVx = vdevice.viewport->v.right * vdevice.sizeX;
	vdevice.maxVy = vdevice.viewport->v.top * vdevice.sizeY;
	vdevice.minVx = vdevice.viewport->v.left * vdevice.sizeX;
	vdevice.minVy = vdevice.viewport->v.bottom * vdevice.sizeY;

	CalcW2Vcoeffs();
}

/*
 * viewport
 *
 * Define a Viewport in Normalized Device Coordinates
 *
 * The viewport defines that fraction of the screen that the window will
 * be mapped onto.  The screen dimension is -1.0 -> 1.0 for both X & Y.
 */
void
viewport(xlow, xhigh, ylow, yhigh)
	float	xlow, xhigh, ylow, yhigh;
{
	Token	*tok;
	char	buf[35];

	if (!vdevice.initialised) 
		verror("viewport: vogle not initialised");

	/*
	 *	A few preliminary checks ....
	 */
	
	if (xlow >= xhigh) {
		sprintf(buf,"viewport: xleft(%5.2f) >= xright(%5.2f)", xlow, xhigh);
		verror(buf);
	} 
	if (ylow >= yhigh) {
		sprintf(buf,"viewport: ybottom(%5.2f) >= ytop(%5.2f)", ylow, yhigh);
		verror(buf);
	} 

	if (vdevice.inobject) {
		tok = newtokens(5);

		tok[0].i = VIEWPORT;
		tok[1].f = xlow;
		tok[2].f = xhigh;
		tok[3].f = ylow;
		tok[4].f = yhigh;

		return;
	}

	/*
	 * convert to 0.0 to 1.0
	 */
	xlow = xlow / 2 + 0.5;
	xhigh = xhigh / 2 + 0.5;
	ylow = ylow / 2 + 0.5;
	yhigh = yhigh / 2 + 0.5;

	/*
	 * Make sure the viewport stack knows about us.....
	 */
	vdevice.viewport->v.left = xlow;
	vdevice.viewport->v.right = xhigh;
	vdevice.viewport->v.bottom = ylow;
	vdevice.viewport->v.top = yhigh;

	vdevice.maxVx = xhigh * vdevice.sizeX;
	vdevice.maxVy = yhigh * vdevice.sizeY;
	vdevice.minVx = xlow * vdevice.sizeX;
	vdevice.minVy = ylow * vdevice.sizeY;

	CalcW2Vcoeffs();
}

/*
 * getviewport
 *
 *	Returns the left, right, bottom and top limits of the current
 *	viewport.
 */
void
getviewport(left, right, bottom, top)
	float	*left, *right, *bottom, *top;
{
	*left = (vdevice.viewport->v.left - 0.5) * 2;
	*right = (vdevice.viewport->v.right - 0.5) * 2;
	*bottom = (vdevice.viewport->v.bottom - 0.5) * 2;
	*top = (vdevice.viewport->v.top - 0.5) * 2;
}
