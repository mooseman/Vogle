c
c drawpoly
c
c	draw some polygons
c
	subroutine drawpoly
	
	integer YELLOW, GREEN, MAGENTA
	parameter (YELLOW = 3, GREEN = 2, MAGENTA = 5)
c
c	An array of points for a polygon
c
	real parray(3,4)

	data parray/ -8.0, -8.0, 0.0,
     +  	    -5.0, -8.0, 0.0,
     +  	    -5.0, -5.0, 0.0,
     +  	    -8.0, -5.0, 0.0 /

	call color(YELLOW)

c
c Draw a polygon using poly, parray is our array of
c points and 4 is the number of points in it.
c
	call poly(4, parray)

	call color(GREEN)

c
c Draw a 5 sided figure by using move, draw and closepoly.
c
	call makepoly()
		call move(0.0, 0.0, 0.0)
		call draw(3.0, 0.0, 0.0)
		call draw(3.0, 4.0, 0.0)
		call draw(-1.0, 5.0, 0.0)
		call draw(-2.0, 2.0, 0.0)
	call closepoly()

	call color(MAGENTA)

c
c draw a sector representing a 1/4 circle
c
	call sector(1.5, -7.0, 3.0, 0.0, 90.0)

	call getkey

	end

c
c Using polygons, hatching, and filling.
c
	program fpoly
	integer BLACK, YELLOW, GREEN, MAGENTA
	parameter (BLACK = 0)
	parameter (YELLOW = 3, GREEN = 2, MAGENTA = 5)
        character*50 device

	print*,'Enter output device:'
	read(*,'(a)')device

	call vinit(device)

c
c clear to black
c
	call color(BLACK)
	call clear

c
c world coordinates are now in the range -10 to 10
c in x, y, and z. Note that positive z is towards us.
c
	call ortho(-10.0, 10.0, -10.0, 10.0, 10.0, -10.0)

	call color(YELLOW)

c
c write out the string "Polygon from poly()" in the
c starting at (-8.0, -4.0) and scaled to be 4.0 units long,
c 0.5 units high.
c
	call boxtext(-8.0, -4.0, 4.0, 0.5, 'Polygon from poly()')

	call color(GREEN)

c
c write out a scaled string starting at (0.0, 6.0)
c
	call boxtext(0.0, 6.0, 4.0, 0.5, 'Polygon from move()/ draw()')

	call color(MAGENTA)

c
c write out a scaled string starting at (0.0, 6.0)
c
	call boxtext(3.5, -3.5, 1.9, 0.5, 'Sector')

c
c draw some polygons
c
	call drawpoly

c
c turn on polygon hatching
c
	call polyhatch(.true.)
	call hatchang(45.0)
	call hatchpitch(0.3)

c
c  Rotate 20 degrees around x and 30 around y
c
	call rotate(20.0, 'x')
	call rotate(30.0, 'y')

c
c draw some polygons with hatching
c
	call drawpoly

c
c turn on polygon filling - this automatically turns off hatching
c
	call polyfill(.true.)

c
c  Do another set of rotations.
c
	call rotate(20.0, 'x')
	call rotate(30.0, 'y')

c
c draw some polygons with filling
c
	call drawpoly

	call vexit

	end
