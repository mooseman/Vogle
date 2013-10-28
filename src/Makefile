#
# Make the vogle library.
#
# Below are our defaults for compliers etc. These are set in the
# main Makefile.
#

MCFLAGS = -g -f68881 -fsingle /usr/lib/f68881/libm.il

LIB = libvogle.a

RANLIB = ranlib		# = "ar ts" for SYS5

#DEVICES = -DSUN -DTEK -DHPGL -DPOSTSCRIPT -DPOSTSCRIPTP -DDXY
DEVICES = -DSUN

DOBJS = ../drivers/sun.o
DRIVEROBJS = ../drivers/ps.o ../drivers/hpdxy.o ../drivers/tek.o $(DOBJS)

FONTLIB=/usr/local/lib/hershey/

HDRS =	vogle.h

CSRC =	arcs.c aspect.c attr.c buffer.c clip.c curves.c draw.c drivers.c \
	viewing.c viewp.c mapping.c matrix.c move.c objects.c patches.c \
	points.c polygons.c rect.c tensor.c text.c newtokens.c trans.c \
	scale.c getstring.c getgp.c valloc.c yobbarays.c pref.c

COBJS =	arcs.o aspect.o attr.o buffer.o clip.o curves.o draw.o drivers.o \
	viewing.o viewp.o mapping.o matrix.o move.o objects.o patches.o \
	points.o polygons.o rect.o tensor.o text.o newtokens.o trans.o \
	scale.o getstring.o getgp.o valloc.o yobbarays.o pref.o


FOBJS =	sunfort/farcs.o sunfort/faspect.o sunfort/fattr.o sunfort/fcurves.o \
	sunfort/fclip.o sunfort/fdraw.o sunfort/fdrivers.o sunfort/fgetgp.o  \
	sunfort/fviewing.o sunfort/fviewp.o sunfort/fmatrix.o sunfort/fmove.o \
	sunfort/fobjects.o sunfort/fpatches.o sunfort/fpoints.o sunfort/fpoly.o\
	sunfort/frect.o sunfort/ftrans.o sunfort/fyobbarays.o sunfort/ftext.o \
	sunfort/fgetstr.o sunfort/fbuffer.o sunfort/fpref.o

#
#  Where the fonts live
#

#  You can use -DSYS5 on a System V system.
#
CFLAGS= $(DEVICES) -DFONTLIB=\"$(FONTLIB)\" $(MCFLAGS)
LINTFLAGS=


$(LIB): $(DRIVEROBJS) $(COBJS) $(FOBJS) vogle.h
	rm -f $@
	ar rcv $@ $(DRIVEROBJS) $(COBJS) $(FOBJS)
	$(RANLIB) $@

lint:
	lint -hac $(DEVICES) $(CSRC) sunfort/*.c > vogle.lint

clean:
	rm -f $(COBJS) core
	cd sunfort; make clean
	cd ../drivers; make clean

clobber:
	rm -f $(LIB) $(COBJS) $(FOBJS) core 
	cd sunfort; make clean

$(COBJS): vogle.h

$(FOBJS): vogle.h
	cd sunfort; make -f Makefile MCFLAGS="$(MCFLAGS)"

$(DRIVEROBJS): vogle.h
	cd ../drivers; make -f Makefile \
			MCFLAGS="$(MCFLAGS)" \
			DRIVEROBJS="$(DRIVEROBJS)"

