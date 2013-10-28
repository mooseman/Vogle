c
c	Draws patches of various bases
c
	program fpatch

	character *20 dev

	integer BLACK, RED, GREEN, YELLOW, BLUE,
     +		CYAN, WHITE
	parameter (BLACK = 0, RED = 1, GREEN = 2,
     +		YELLOW = 3, BLUE = 4, CYAN = 5, WHITE = 7)
		  
c
c  patch basis types
c
	real bezier(4,4), cardinal(4, 4), bspline(4, 4)
	real power(4, 4)
	real x1(4, 4), y1(4, 4), z1(4, 4)
	real x2(4, 4), y2(4, 4), z2(4, 4)

	character *50 labels(4)

	real	basis(64)
	equivalence (basis(1), bezier(1))
	equivalence (basis(17), cardinal(1))
	equivalence (basis(33), bspline(1))
	equivalence (basis(49), power(1))

	data bezier/
     +		-1.0,	3.0,	-3.0,	1.0,
     +		3.0,	-6.0,	3.0,	0.0,
     +		-3.0,	3.0,	0.0,	0.0,
     +		1.0,	0.0,	0.0,	0.0/ 

	data cardinal/
     +		-0.5,	1.5,	-1.5,	0.5,
     +		1.0,	-2.5,	2.0,	-0.5,
     +		-0.5,	0.0,	0.5,	0.0,
     +		0.0,	1.0,	0.0,	0.0/

	data bspline/
     + 		-0.166666,     0.5,     -0.5,     0.166666,
     +		 0.5,	      -1.0,      0.5,     0.0,
     +	        -0.5,          0.0,      0.5,     0.0, 
     +		 0.166666,     0.666666, 0.166666, 0.0 /

	data power/
     +		1.0, 0.0, 0.0, 0.0,
     +		0.0, 1.0, 0.0, 0.0,
     +		0.0, 0.0, 1.0, 0.0,
     +		0.0, 0.0, 0.0, 1.0/

	data	x1 / 
     +		0.0,   0.2588,   0.5,   0.7071,
     +		0.0,   0.51764,  1.0,   1.4142,
     +		0.0,   0.51764,  1.0,   1.4142,
     +		0.0,   0.2588,   0.5,   0.7071/

	data	y1 / 
     +		1.0,   0.966,   0.866,  0.7071,
     +		2.0,   1.9318,  1.732,  1.4142,
     +		2.0,   1.9318,  1.732,  1.4142,
     +		1.0,   0.966,   0.866,  0.7071/

	data	z1 / 
     +		1.0,   1.0,     1.0,    1.0,
     +		1.0,   1.0,     1.0,    1.0,
     +		0.0,   0.0,     0.0,    0.0,
     +		0.0,   0.0,     0.0,    0.0/

	data	x2 / 
     +		0.7071, 0.8660, 0.9660, 1.0,
     +		1.4142, 1.7320, 1.932,  2.0,
     +		1.4142, 1.7320, 1.932,  2.0,
     +		0.7071, 0.8660, 0.9660, 1.0/

	data	y2 / 
     +		0.7071, 0.5,    0.2588, 0.0,
     +		1.4142, 1.0,    0.5176, 0.0,
     +		1.4142, 1.0,    0.5176, 0.0,
     +		0.7071, 0.5,    0.2588, 0.0/

	data	z2 / 
     +		1.0,   1.0,     1.0,    1.0,
     +		1.0,   1.0,     1.0,    1.0,
     +		0.0,   0.0,     0.0,    0.0,
     +		0.0,   0.0,     0.0,    0.0/


	data labels /
     +		'Bezier Patch(es)',
     +		'Cardinal Patch(es)',
     +		'B-Spline Patch(es)',
     +		'''Power'' Patch(es)' /

c
c  demonstrate patches
c

	write (*,*)'Enter device:'
	read(*,'(a)') dev

	call vinit(dev)

	call color(BLACK)
	call clear

c
c Set up two viewports (They actually overlap)
c

	call viewport(-1.0, 0.3, -1.0, 0.3)
	call ortho(-2.0, 5.0, -2.0, 5.0, -2.0, 5.0)
	call lookat(0.0, 0.0, 0.0, -3.0, 2.0, -4.0, 0.0)
c
c	Save it 
c
	call pushviewport
	call pushmatrix

	call viewport(-0.3, 1.0, -0.3, 1.0)
	call ortho(-2.0, 5.0, -2.0, 5.0, -2.0, 5.0)
	call lookat(0.0, 0.0, 0.0, 3.0, 2.0, -4.0, 0.0)

	call textsize(0.4, 0.4)

c
c	patchcurves provides a number of curves in the t and u
c	directions. patchprecision gives the minimum number of line
c	segments making up the curves in the t and u directions. The
c	actual number of linesegments in t or u is equal to the closest
c	integer multiple of the number of curves, > nsegs, in t or u,
c	greater than or equal to the number set by patchprecision in u or
c	t. eg. curves in t will be made up of 21 line segments so that we
c	can match up the 7 curves in u; curves in u will have 24 as 4 by 5
c	gives 20.
c
	call patchcurves(4, 7)
	call patchprecision(20, 20)

	do 10 i = 0, 3

		call axes


c
c 		patchbasis sets the basis matrices for the t and u
c 		functions
c 
c
		call patchbasis(basis(i*16 + 1), basis(i*16 + 1))

c 
c		Draw with viewport 2
c
		call move(0.0, 4.0, 0.0)
		call drawstr(labels(i+1))

c
c		Now draw the patches according to the geometry matrices in
c		x1, y1, and z1, x2, y2, z2.
c
		call drawhull(x1, y1, z1)
		call patch(x1, y1, z1)

		call drawhull(x2, y2, z2)
		call patch(x2, y2, z2)

		call getkey
c
c	 	Now with viewport 1
c
		call popviewport
		call popmatrix

		call axes

		call move(0.0, 4.0, 0.0)
		call drawstr(labels(i + 1))

c
c		now draw the patches according to the geometry matrices in
c 		x1, y1, and z1, x2, y2, z2.
c
		call drawhull(x1, y1, z1)
		call patch(x1, y1, z1)

		call drawhull(x2, y2, z2)
		call patch(x2, y2, z2)

		call getkey

c
c 		Save viewport 1 again and reset to viewport 2
c
		call pushviewport
		call pushmatrix

		call viewport(-0.3, 1.0, -0.3, 1.0)
		call ortho(-1.5, 5.0, -1.5, 5.0, -1.5, 5.0)
		call lookat(0.0, 0.0, 0.0, 3.0, 2.0, -4.0, 0.0)

		call color(BLACK)
		call clear
10	continue

	call vexit

	end


	subroutine drawhull(x, y, z)
	real	x(4,4), y(4,4), z(4,4)

	integer MAGENTA, WHITE, GREEN
	parameter (MAGENTA = 5, WHITE = 7, GREEN = 2)

	call color(MAGENTA)	
	do 10 i = 1,4
		call move(x(i,1), y(i,1), z(i,1))
		do 5 j = 1,4
			call draw(x(i,j), y(i,j), z(i,j))
5		continue
10	continue
	
	do 20 i = 1,4
		call move(x(1,i), y(1,i), z(1,i))
		do 15 j = 1,4
			call draw(x(j,i), y(j,i), z(j,i))
15		continue
20	continue

	call color(GREEN)
	end

c
c axes
c
c	draw the axes
c

	subroutine axes

	integer YELLOW
	parameter (YELLOW = 3)

	call color(YELLOW)
	call move(0.0, 0.0, 0.0)
	call draw(4.0, 0.0, 0.0)

	call move(0.0, 0.0, 0.0)
	call draw(0.0, 4.0, 0.0)

	call move(0.0, 0.0, 0.0)
	call draw(0.0, 0.0, 4.0)

	end
