#include <stdio.h>
#include "vogle.h"

/*
 * voutput_
 */
void
voutput_(path, len)
	char	*path;
	int	len;
{
	char		buf[BUFSIZ];
	register char	*p;

	strncpy(buf, path, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	voutput(buf);
}

/*
 * vinit_
 */
void
vinit_(dev, len)
	char	*dev;
	int	len;
{
	char		buf[BUFSIZ];
	register char	*p;

	strncpy(buf, dev, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	vinit(buf);
}

/*
 * vnewdev_
 */
void
vnewdev_(dev, len)
	char	*dev;
	int	len;
{
	char		buf[BUFSIZ];
	register char	*p;

	strncpy(buf, dev, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	vnewdev(buf);
}

/*
 * vgetdev_
 */
void
vgetdev_(buf, len)
	char	*buf;
	int	len;
{
	register char	*p;

	(void)vgetdev(buf);

	for (p = &buf[len - 1]; *p == ' '; p--)
		;
}
	
/*
 * vexit_
 */
void
vexit_()
{
	vexit();
}

/*
 * clear_
 */
void
clear_()
{
	clear();
}

/*
 * color_
 */
void
color_(col)
	int	*col;
{
	color(*col);
}

/*
 * _mapcolor
 */
void
mapcolor_(indx, red, green, blue)
	int	*indx, *red, *green, *blue;
{
	mapcolor(*indx, *red, *green, *blue);
}

/*
 * getkey_
 */
int
getkey_()
{
	return(getkey());
}

/*
 * checkkey_
 */
int
checkkey_()
{
	return(checkkey());
}

/*
 * getdepth_
 */
int
getdepth_()
{
	return(getdepth());
}

/*
 * locator_
 */
int
locator_(xaddr, yaddr)
	float	*xaddr, *yaddr;
{
	return(locator(xaddr, yaddr));
}

/*
 * slocator_
 */
int
slocator_(xaddr, yaddr)
	float	*xaddr, *yaddr;
{
	return(slocator(xaddr, yaddr));
}
