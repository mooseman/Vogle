#include <stdio.h>
#include "vogle.h"

/*
 * getstring_
 */
int
getstring_(bcol, string, len)
	int	bcol;
	char	*string;
	int	len;
{
	int	i, j;
	
	j = getstring(bcol, string);

	for (i = j; i < len; i++)
		string[i] = ' ';

	return (j);
}
