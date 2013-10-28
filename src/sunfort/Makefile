#
# Makefile for f77 interface routines.
#

MCFLAGS = -g -fsingle -f68881 /usr/lib/f68881/libm.il

SRC =	farcs.c faspect.c fattr.c fbuffer.c fcurves.c fclip.c fdraw.c \
	fdrivers.c fgetgp.c fviewing.c fviewp.c fmatrix.c fmove.c  \
	fobjects.c fpatches.c fpoints.c fpoly.c frect.c ftrans.c  \
	fyobbarays.c ftext.c fgetstr.c fpref.c

OBJS = $(SRC:.c=.o)

CFLAGS = -I../ $(MCFLAGS)

all:	$(OBJS)

$(OBJS): ../vogle.h

clean:
	rm -f $(OBJS) core

