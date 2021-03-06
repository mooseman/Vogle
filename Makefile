#
# Makefile for vogle
#
# Usage: make os
#
# You might have to set:
#
#	DEVICES
#	FONTLIB
#	OS
#	RANLIB
#	MCFLAGS
#	F77
#	MFFLAGS
#
############################################################
#
# The Devices you want compiled into the library.
# (Note the "make sun" automatically includes -DSUN later on)
#
DEVICES = -DPOSTSCRIPT -DDXY -DHPGL -DTEK
#
# Where the fonts a going to live
#
FONTLIB = /usr/local/lib/hershey/
#FONTLIB = /tmp/

#
# You can set -DBSD or -DSYS5 here
#
#OS = -DBSD

# If you set -DSYS5 then set RANLIB = "ar ts"
#RANLIB = ar ts

#
# Global CFLAGS can be set here. These are the ones we use on a sun.
#
#MCFLAGS = -O $(OS) -f
MCFLAGS = $(OS) -g -f68881 -fsingle /usr/lib/f68881/libm.il

#
# Or on an apollo... (-Wp make it use the 'other cpp')
#MCFLAGS = $(OS) -O -Wp -M3000


#
# Define F77 if you want the f77 examples.
# You also define your f77 flags here too. These are the ones we used on sun
#
F77 = f77
MFFLAGS = -g /usr/lib/f77/f68881/libm.il
#
# Or on an apollo (We didn't have ftn)
#F77 = 
#MFFLAGS = 

#
# The name of the library to install and where to put it.
#
LIB = libvogle.a
DEST = /usr/local/lib

#
# Any other libraries that are needed go here
#

SUNLIBS = -lsuntool -lsunwindow -lpixrect
X11LIBS = -lX11
UNIXLIBS = 
APOLLOLIBS =


all:
	@echo "Usage: 'make unix' "

install:
	cp src/$(LIB) $(DEST)
	chmod 644 $(DEST)/$(LIB)
	$(RANLIB) $(DEST)/$(LIB)

unix:
	cd src; make -f Makefile \
			DEVICES="$(DEVICES)" \
			FONTLIB="$(FONTLIB)" \
			MCFLAGS="$(MCFLAGS)" \
			DOBJS="../drivers/tek.o"

	cd examples; make -f Makefile \
			MCFLAGS="$(MCFLAGS)" \
			LIBS="$(UNIXLIBS)"

	if test -n "$(F77)" ; \
	then cd examples; make -f Makefile.f77 \
			LIBS="$(UNIXLIBS)" \
			MFFLAGS="$(MFFLAGS)" \
			F77="$(F77)" ; \
	fi ; exit 0

	cd hershey/src; make -f Makefile \
			FONTLIB="$(FONTLIB)" \
			MCFLAGS="$(MCFLAGS)" \
			LIBS="$(UNIXLIBS)"

clean:
	cd src; make clean
	cd hershey/src; make clean
	cd drivers; make clean
	cd examples; make clean
	cd examples; make -f Makefile.f77 clean

clobber:
	cd src; make clobber
	cd hershey/src; make clobber
	cd drivers; make clobber
	cd examples; make clobber
	cd examples; make -f Makefile.f77 clobber
