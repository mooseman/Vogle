c
c using curves
c
	program fcurves

	integer i, BLACK, RED, GREEN, YELLOW, MAGENTA
	parameter (BLACK = 0, RED = 1, GREEN = 2, YELLOW = 3)
	parameter (MAGENTA = 5)
	character buf*50
	real bezier(4, 4), cardinal(4, 4), bspline(4, 4)
	real geom1(3, 4), geom2(3, 6)
c
c curve basis types
c
	data bezier /
     +  	-1.0,	3.0,	-3.0,	1.0,
     +  	3.0,	-6.0,	3.0,	0.0,
     +  	-3.0,	3.0,	0.0,	0.0,
     +  	1.0,	0.0,	0.0,	0.0 
     +  /

	data cardinal /
     +  	-0.5,	1.5,	-1.5,	0.5,
     +  	1.0,	-2.5,	2.0,	-0.5,
     +  	-0.5,	0.0,	0.5,	0.0,
     +  	0.0,	1.0,	0.0,	0.0
     +  /

	data bspline /
     +          -0.166666,     0.5,     -0.5,     0.166666,
     +           0.5,         -1.0,      0.5,     0.0,
     +          -0.5,          0.0,      0.5,     0.0,
     +           0.166666,     0.666666, 0.166666, 0.0
     +  /

c
c Geometry matrix to demonstrate basic spline segments
c
	data geom1 /
     +  	 -180.0, 10.0, 0.0,
     +  	 -100.0, 110.0, 0.0,
     +  	 -100.0, -90.0, 0.0,
     +  	 0.0, 50.0, 0.0
     +  /

c
c Geometry matrix to demonstrate overlapping control points to
c produce continuous (Well, except for the bezier ones) curves
c from spline segments
c
	data geom2 /
     +  	200.0, 480.0, 0.0,
     +  	380.0, 180.0, 0.0,
     +  	250.0, 430.0, 0.0,
     +  	100.0, 130.0, 0.0,
     +  	50.0,  280.0, 0.0,
     +  	150.0, 380.0, 0.0
     +  /


	print*,'Enter output device:'
	read(*,'(a)') buf

	call vinit(buf)

	call ortho2(-200.0, 400.0, -100.0, 500.0)

	call color(BLACK)
	call clear()

	call color(YELLOW)

	call textsize(10.0, 10.0)

c
c label the control points in geom1
c
	do 10 i = 1, 4
	    call move2(geom1(1, i), geom1(2, i))
	    write(buf, '(i1)')i
	    call drawstr(buf)
10	continue
								 
c
c label the control points in geom2
c
	do 20 i = 1, 6
	    call move2(geom2(1, i), geom2(2, i))
	    write(buf, '(i1)')i
	    call drawstr(buf)
20	continue

c
c scale the current font so that 30 of the largest characters
c in the current font will fit in a region 300 world units wide,
c 20 high.
c
	call boxfit(300.0, 20.0, 30)

c
c set the number of line segments appearing in each curve to 20
c
	call curveprecision(20)

c
c copy the bezier basis matrix into the curve basis matrix.
c
	call curvebasis(bezier)

	call color(RED)

c
c draw a curve using the current basis matrix (bezier in this case)
c and the control points in geom1
c
	call curve(geom1)

	call move2(70.0, 60.0)
	call drawstr('Bezier Curve Segment')

	call move2(-190.0, 450.0)
	call drawstr('Three overlapping Bezier Curves')

c
c curven draws overlapping curve segments according to geom2, the
c number of curve segments drawn is three less than the number of
c points passed, assuming there are a least four points in the
c geometry matrix (in this case geom2). This call will draw 3
c overlapping curve segments in the current basis matrix - still
c bezier.
c
	call curven(6, geom2)

	call getkey

c
c load in the cardinal basis matrix
c
	call curvebasis(cardinal)

	call color(MAGENTA)

	call move2(70.0, 10.0)
	call drawstr('Cardinal Curve Segment')

c
c plot out a curve segment using the cardinal basis matrix
c
	call curve(geom1)

	call move2(-190.0, 400.0)
	call drawstr('Three overlapping Cardinal Curves')

c
c now draw a bunch of them again.
c
	call curven(6, geom2)

	call getkey

c
c change the basis matrix again
c
	call curvebasis(bspline)

	call color(GREEN)

	call move2(70.0, -40.0)
	call drawstr('Bspline Curve Segment')

c
c now draw our curve segment in the new basis...
c
	call curve(geom1)

	call move2(-190.0, 350.0)
	call drawstr('Three overlapping Bspline Curves')

c
c ...and do some overlapping ones
c
	call curven(6, geom2)

	call getkey

	call vexit

	end
