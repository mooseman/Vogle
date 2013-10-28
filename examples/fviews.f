
c
c Shows various combinations of viewing and
c projection transformations.
c
	program fviews
	integer BLACK, GREEN, RED, MAGENTA, YELLOW
	parameter (BLACK = 0, GREEN = 2, RED = 1, MAGENTA = 5)
	parameter (YELLOW = 3)
	character*50 device

	print*,'Enter output device:'
	read(*,'(a)') device

	call vinit(device)

	call color(BLACK)
	call clear

c
c we want to draw just within the boundaries of the screen
c
	call viewport(-0.9, 0.9, -0.9, 0.9)

c
c set the world size
c
	call ortho2(-5.0, 5.0, -5.0, 5.0)

c
c draw a boundary frame
c
	call color(RED)
	call rect(-5.0, -5.0, 5.0, 5.0)

c
c set up a perspective projection with a field of view of
c 40.0 degrees, aspect ratio of 1.0, near clipping plane 0.1,
c and the far clipping plane at 1000.0.
c
	call perspective(40.0, 1.0, 0.1, 1000.0)
c
c we want the drawing to be done with our eye point at (5.0, 8.0, 5.0)
c looking towards (0.0, 0.0, 0.0). The last parameter gives a twist
c in degrees around the line of sight, in this case zero.
c
	call lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0)

	call drawtetra

c
c set the text size
c
	call textsize(0.6, 0.9)

	call move2(-4.5, -4.5)
	call drawstr('perspective/lookat')

	call getkey

c
c window can also be used to give a perspective projection. Its
c arguments are 6 clipping planes, left, right, bottom, top, near,
c and far.
c
	call window(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0)
c
c as window replaces the current transformation matrix we must
c specify our viewpoint again.
c
	call lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0)

	call color(BLACK)
	call clear

	call color(GREEN)
	call rect(-5.0, -5.0, 5.0, 5.0)

	call drawtetra

	call textsize(0.6, 0.9)
	call move2(-4.5,-4.5)
	call drawstr('window/lookat')

	call getkey

c
c set up our original perspective projection again.
c
	call perspective(40.0, 1.0, 0.1, 1000.0)
c
c polarview also specifies our viewpoint, but, unlike lookat, in polar
c coordinates. Its arguments are the distance from the world origin, an
c azimuthal angle in the x-y plane measured from the y axis, an 
c incidence angle in the y-z plane measured from the z axis, and a
c twist around the line of sight.
c
	call polarview(15.0, 30.0, 30.0, 30.0)

	call color(BLACK)
	call clear

	call color(MAGENTA)
	call rect(-5.0, -5.0, 5.0, 5.0)

	call drawtetra

	call move2(-4.5,-4.5)
	call textsize(0.6, 0.9)
	call drawstr('perspective/polarview')

	call getkey

c
c once more with window for comparison
c
	call window(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0)
	call polarview(6.0, 20.0, -30.0, 70.0)

	call color(BLACK)
	call clear

	call color(YELLOW)
	call rect(-5.0, -5.0, 5.0, 5.0)

	call drawtetra

	call move2(-4.5,-4.5)
	call textsize(0.6, 0.9)
	call drawstr('window/polarview')

	call getkey

	call vexit
	
	end

c
c drawtetra 
c 
c generate a tetrahedron as a series of move draws 
c
c
	subroutine drawtetra
	
	integer WHITE
	parameter (WHITE = 7)

	call move(-0.5,  0.866, -0.5)
	call draw(-0.5, -0.866, -0.5)
	call draw( 1.0,  0.0,   -0.5)
	call draw(-0.5,  0.866, -0.5)
	call draw( 0.0,  0.0,    1.5)
	call draw(-0.5, -0.866, -0.5)
	call move( 1.0,  0.0,   -0.5)
	call draw( 0.0,  0.0,    1.5)
	
c 
c    Label the vertices.
c
	call color(WHITE)
	call textsize(0.3, 0.5)	
	call move(-0.5,  0.866, -0.5)
	call drawchar('a')
	call move(-0.5, -0.866, -0.5)
	call drawchar('b')
	call move( 1.0,  0.0,   -0.5)
	call drawchar('c')
	call move( 0.0,  0.0,    1.5)
	call drawchar('d')

	end
