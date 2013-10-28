#
# examples makefile 
#
FEXAMPS = ftrivial fsimple fshapes fpoly fviews fcirctxt fmoretxt fcurves \
	  fgetstr fpatches fballs fobjvws fworld floc fdistrt ftetra fcube \
	  flcube

FOBJS = ftrivial.o fsimple.o fshapes.o fpoly.o fviews.o fcirctxt.o fmoretxt.o \
	fgetstr.o fcurves.o fpatches.o fballs.o fobjvws.o fworld.o floc.o \
	fdistrt.o ftetra.o fcube.o flcube.o

#
# Where to find library
LIB = ../src/libvogle.a
LIBS = -lsuntool -lsunwindow -lpixrect
#
F77 = f77

MFFLAGS = -g -f68881 /usr/lib/f77/f68881/libm.il
FFLAGS = $(MFFLAGS)

.f.o:
	$(F77) -c $(FFLAGS) $*.f

all:	$(FEXAMPS)

$(FEXAMPS): $(LIB) $(FOBJS)
	$(F77) $(FFLAGS) -o $@ $@.o $(LIB) $(LIBS) 

clean:
	rm -f *.o core

clobber:
	rm -f $(FEXAMPS) *.o core
