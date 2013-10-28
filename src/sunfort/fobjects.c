#include <stdio.h>
#include "vogle.h"

/*
 * makeobj_
 */
void
makeobj_(n)
	int	*n;
{
	makeobj(*n);
}

/*
 * closeobj_
 */
void
closeobj_()
{
	closeobj();
}

/*
 * delobj_
 */
void
delobj_(n)
	int	*n;
{
	delobj(*n);
}

/*
 * genobj_
 */
int
genobj_()
{
	return(genobj());
}

/*
 * getopenobj_
 */
int
getopenobj_()
{
	return(getopenobj());
}

/*
 * callobj_
 */
void
callobj_(n)
	int	*n;
{
	callobj(*n);
}

/*
 * isobj_
 */
int
isobj_(n)
	int	*n;
{
	return(isobj(*n));
}

/*
 * saveobj_
 */
void
saveobj_(n, file, len)
	int	*n;
	char	*file;
	int	len;
{
	char		buf[BUFSIZ];
	register char	*p;

	strncpy(buf, file, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	saveobj(*n, buf);
}

/*
 * loadobj_
 */
void
loadobj_(n, file, len)
	int	*n;
	char	*file;
	int	len;
{
	char		buf[BUFSIZ];
	register char	*p;

	strncpy(buf, file, len);
	buf[len] = 0;

	for (p = &buf[len - 1]; *p == ' '; p--)
		;

	*++p = 0;

	loadobj(*n, buf);
}

