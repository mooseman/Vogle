c
c Demonstrate how to use non-square viewports, the associated
c distortion caused and how to fix it.
c
	program fdistrt

	integer BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
	parameter(BLACK = 0)
	parameter(RED = 1)
	parameter(GREEN = 2)
	parameter(YELLOW = 3)
	parameter(BLUE = 4)
	parameter(MAGENTA = 5)
	parameter(CYAN = 6)
	parameter(WHITE = 7)
	character device*50, buf*120
	real	xfact, yfact

	print*,'Enter output device:'
	read(*,'(a)') device

	call vinit(device)

	call color(BLACK)
	call clear

c 
c Make the viewport the same size as the screen/window.
c
	call getfactors(xfact, yfact)
	call viewport(-1.0, xfact, -1.0, yfact)

c
c Draw a square. (Looks like a rectangle, if the viewport
c wasn't "accidentally" square)
c
	call color(1)
	call rect(-0.5, -0.5, 0.5, 0.5)

c 
c Tell them what it is.
c
	call move2(-1.0, 0.9)
	write(buf,'(''Distorted square (viewport(-1, '',
     +     F7.3, '', -1, '', F7.3, ''))'')') xfact, yfact
	call drawstr(buf)

	call getkey

c
c Fix up the distortion (The actual formula to fix
c the distortion is (viewport.xmax * (1 + xfact) / 2.0),
c and similar for the y axis.
c
	call ortho2(-1.0, xfact, -1.0, yfact)

c
c Draw another square (Really is square this time)
c
	call color(3)
	call rect(-0.5, -0.5, 0.5, 0.5)

c 
c Tell them what it is.
c
	call move2(-1.0, -0.9)
	write(buf,'(''Fixed up square with ortho2(-1,'',
     +	   F7.3, '', -1, '', F7.3, ''))'')') xfact, yfact
	call drawstr(buf)

	call getkey

c
c Do it with world coords going from 0 - 5, 0 - 5.
c Reset square viewport.
c

	call color(0)
	call clear

	call viewport(-1.0, 1.0, -1.0, 1.0)
	call ortho2(0.0, 5.0, 0.0, 5.0)
	call textsize(0.1, 0.1)

c
c Square from 1 to 3. (Really is square)
c

	call color(2)
	call rect(1.0, 1.0, 3.0, 3.0)

	call move2(0.0, 4.5)
	call drawstr('Square from 0 - 3, 0 - 3')

	call getkey

c
c Distort it with a non-square viewport.
c
	call viewport(-1.0, xfact, -1.0, yfact)

	call color(4)
	call rect(1.0, 1.0, 3.0, 3.0)

	call move2(0.0, 0.5)
	call drawstr('Distorted square from 0 - 3, 0 - 3')

	call getkey

c 
c Fix the distortion.
c 
	call ortho2(0.0, 5.0 * (1.0 + xfact) / 2.0, 0.0,
     +                   5.0 * (1.0 + yfact) / 2.0)
	
	call color(5)
	call rect(1.0, 1.0, 3.0, 3.0)

	call move2(0.0, 2.5)
	call drawstr('Fixed up  square from 0 - 3, 0 - 3')

	call getkey

	call vexit

	end
