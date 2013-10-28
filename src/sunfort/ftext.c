#include <stdio.h>
#include "vogle.h"

/*
 * font_
 */
void
font_(fontfile, len)
	char	*fontfile;
	int	len;
{
	char		buf[BUFSIZ];
	register char	*p;

	strncpy(buf, fontfile, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	font(buf);
}

/*
 * textsize_
 */
void
textsize_(width, height)
	float	*width, *height;
{
	textsize(*width, *height);
}

/*
 * boxtext_
 */
boxtext_(x, y, l, h, s, len)
	float	*x, *y, *l, *h;
	char	*s;
	int	len;
{
	char		buf[BUFSIZ];
	register char   *p;

	strncpy(buf, s, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	boxtext(*x, *y, *l, *h, buf);
}

/*
 * boxfit_
 */
boxfit_(l, h, nchars)
	float	*l, *h;
	int	*nchars;
{
	boxfit(*l, *h, *nchars);
}

/*
 * textang_
 */
void
textang_(ang)
	float	*ang;
{
	textang(*ang);
}

/*
 * drawchar_
 */
drawchar_(s)
	char	*s;
{
	drawchar(*s);
}

/*
 * drawstr_
 */
drawstr_(s, len)
	char	*s;
	int	len;
{
        char            buf[BUFSIZ];
	register char   *p;

	strncpy(buf, s, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	drawstr(buf);
}

/*
 * getfontsize_
 */
void
getfontsize_(cw, ch)
	float 	*cw, *ch;
{
	getfontsize(cw, ch);
}

/*
 * getcharsize_
 */
void
getcharsize_(c, cw, ch)
	char	*c;
	float 	*cw, *ch;
{
	getcharsize(*c, cw, ch);
}

/*
 * fixedwidth
 */
void
fixedwidth_(i)
	int	*i;
{
	fixedwidth(*i);
}

/*
 * centertext
 */
void
centertext_(i)
	int	*i;
{
	centertext(*i);
}

/*
 * numchars_
 */
int
numchars_()
{
	return(numchars());
}

/*
 * strlength_
 */
float
strlength_(str, len)
	char	*str;
	int	len;
{
        char            buf[BUFSIZ];
	register char   *p;

	strncpy(buf, str, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	return(strlength(buf));
}
