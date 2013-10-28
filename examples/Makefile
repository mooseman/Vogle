#
# examples makefile 
#
CEXAMPS = trivial simple shapes poly views circtxt moretxt curves \
	  getstr patches balls objvws world loc teapot showg \
	  distrt cube lcube tetra

COBJS = trivial.o simple.o shapes.o poly.o views.o circtxt.o moretxt.o \
	getstr.o curves.o patches.o balls.o objvws.o world.o loc.o \
	teapot.o showg.o distrt.o cube.o lcube.o tetra.o

#
# Where to find library
LIB = ../src/libvogle.a
LIBS = -lsuntool -lsunwindow -lpixrect
#
MCFLAGS = -g -fsingle -f68881 /usr/lib/f68881/libm.il
CFLAGS = -I../src $(MCFLAGS)

all:	$(CEXAMPS)

$(CEXAMPS): $(LIB) $(COBJS)
	$(CC) $(CFLAGS) -o $@ $@.o $(LIB) $(LIBS) -lm

clean:
	rm -f *.o core

clobber:
	rm -f $(CEXAMPS) *.o core
