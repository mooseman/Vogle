#include <stdio.h>
#include "vogle.h"

static	Astack	*asfree = (Astack *)NULL;

/*
 * copyattributes
 *
 *	Copies attribute stack entries from b to a
 */
static	void
copyattributes(a, b)
	Attribute	*a, *b;
{
	a->color = b->color;
	a->fill = b->fill;
	a->hatch = b->hatch;
	a->textcos = b->textcos;
	a->textsin = b->textsin;
	a->hatchcos = b->hatchcos;
	a->hatchsin = b->hatchsin;
	a->hatchpitch = b->hatchpitch;
	a->centered = b->centered;
	a->fixedwidth = b->fixedwidth;
	a->fontwidth = b->fontwidth;
	a->fontheight = b->fontheight;
	strcpy(a->font, b->font);
}

/*
 * pushattributes
 *
 * save the current attributes on the matrix stack
 *
 */
void
pushattributes()
{
	Astack	*nattr;
	Token	*p;

	if (!vdevice.initialised)
		verror("pushattributes:  vogle not initialised");
	
	if (vdevice.inobject) {
		p = newtokens(1);

		p[0].i = PUSHATTRIBUTES;

		return;
	}

	if (asfree != (Astack *)NULL) {
		nattr = vdevice.attr;
		vdevice.attr = asfree;
		asfree = asfree->back;
		vdevice.attr->back = nattr;
		copyattributes(&vdevice.attr->a, &nattr->a);
	} else {	
		nattr = (Astack *)vallocate(sizeof(Astack));
		nattr->back = vdevice.attr;
		copyattributes(&nattr->a, &vdevice.attr->a);
		vdevice.attr = nattr;
	}
}

/*
 * popattributes
 *
 * pop the top entry on the attribute stack 
 *
 */
void
popattributes()
{
	Astack	*nattr;
	Token	*p;

	if (!vdevice.initialised)
		verror("popattributes: vogle not initialised");
	
	if (vdevice.inobject) {
		p = newtokens(1);

		p[0].i = POPATTRIBUTES;

		return;
	}

	if (vdevice.attr->back == (Astack *)NULL) 
		verror("popattributes: attribute stack is empty");
	else {
		font(vdevice.attr->back->a.font);
		textsize(vdevice.attr->back->a.fontwidth, vdevice.attr->back->a.fontheight);
		nattr = vdevice.attr;
		vdevice.attr = vdevice.attr->back;
		nattr->back = asfree;
		asfree = nattr;
	}

	color(vdevice.attr->a.color);
}

#ifdef	DEBUG

printattribs(s)
	char	*s;
{
	printf("%s\n", s);
	printf("clipoff    = %d\n", vdevice.clipoff);
	printf("color      = %d\n", vdevice.attr->a.color);
	printf("fill       = %d\n", vdevice.attr->a.fill);
	printf("hatch      = %d\n", vdevice.attr->a.hatch);
	printf("textcos    = %f\n", vdevice.attr->a.textcos);
	printf("textsin    = %f\n", vdevice.attr->a.textsin);
	printf("hatchcos   = %f\n", vdevice.attr->a.hatchcos);
	printf("hatchsin   = %f\n", vdevice.attr->a.hatchsin);
	printf("hatchpitch = %f\n", vdevice.attr->a.hatchpitch);
	printf("centered   = %d\n", vdevice.attr->a.centered);
	printf("fixedwidth = %d\n", vdevice.attr->a.fixedwidth);
	printf("fontwidth  = %f\n", vdevice.attr->a.fontwidth);
	printf("fontwidth  = %f\n", vdevice.attr->a.fontheight);
	printf("font       = %s\n", vdevice.attr->a.font);
}

#endif
