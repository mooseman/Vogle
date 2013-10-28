#
# if your system is running 4.2 or is a sun running
# a sun os before 4.0 you need to add -DBSD to CFLAGS
#
MCFLAGS = -g -fsingle -f68881 /usr/lib/f68881/libm.il

HDRS= ../src/vogle.h

DRIVEROBJS = sun.o ps.o hpdxy.o tek.o

CFLAGS= -I../src $(MCFLAGS)

all:	$(DRIVEROBJS)

$(DRIVEROBJS): $(HDRS)

clean:
	rm -f core $(DRIVEROBJS)

clobber:
	rm -f core *.o
	
