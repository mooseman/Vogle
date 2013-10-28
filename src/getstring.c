#include "vogle.h"
#include <stdio.h>

#define	EOT	4		/* Our EOF char */
#define	BS	8		/* A backspace char */
#define	DEL	127		/* Another backspace char (or erase) */
#define	CR	13		/* End of line */

/*
 * getstring
 *
 *	Get a character string from the keyboard in graphics mode.
 *	Echoes in the current color/font/transformation.
 *	returns s as parameter and the number of chars read as
 *	function value (-1 on EOF).
 *
 *	Draws in the current color, erases in the color bcol.
 *
 *	NB. no overflow cheching is done on the string s.
 */
int
getstring(bcol, s)
	int	bcol;
	char	*s;
{
	int	i, nc, pos, col;
	float	cw, ch;

	s[0] = '\0';
	pos = -1;
	nc = numchars() + 32;

	col = vdevice.attr->a.color;

	while ((i = getkey()) != CR) {
		switch (i) {
		case EOT:
			s[++pos] = '\0';
			return (pos);

		case BS:
		case DEL:
			if (pos >= 0) {
				/*
				 * Over draw prev char in color bcol
				 */
				getcharsize(s[pos], &cw, &ch);
				rmove2(-cw, 0.0, 0.0);
				color(bcol);
				drawchar(s[pos]);
				rmove2(-cw, 0.0, 0.0);
				color(col);
				s[pos--] = '\0';
			}
			break;

		default:
			/*
			 * A new char... draw it in color col.
			 */
			if (i > nc || i < 32)
				continue;

			s[++pos] = (char)i;
			drawchar(s[pos]);
		}
	}

	s[++pos] = '\0';
	return (pos);
}
