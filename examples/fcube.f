
c
c a program to demonstrate  double buffering and what happens
c when you hit a clipping plane. Specifying an extra argument
c turns on the filling.
c
	program cube
	character device*30, ans*1
	real	r, t, dr, dt
	integer nplanes
	integer getdepth, backbuffer, checkkey

	integer BLACK, GREEN, RED, BLUE, WHITE
	parameter (BLACK = 0, GREEN = 2, RED = 1, BLUE = 4, WHITE = 7)

	print*,'Enter output device:'
	read(*,'(a)') device

	print*,'Fill the polygons (Y/N)?'
	read(*, '(a)') ans
	ifill = 0
	if (ans .eq. 'y' .or. ans .eq. 'Y') ifill = 1
				  
	call prefsize(300, 300)

	call vinit(device)

	dr = 10.0
	dt = 0.2

	nplanes = getdepth()

	call polyfill(ifill)

	call color(BLACK)
	call clear

	call window(-1.5, 1.5, -1.5, 1.5, 9.0, -5.0)
	call lookat(0.0, 0.0, 12.0, 0.0, 0.0, 0.0, 0.0)

	call backface(1)
c
c Setup drawing into the backbuffer....
c
	if (backbuffer().lt.0) then
		call vexit
		write(*,*)'Device can''t support doublebuffering'
		stop
	endif

	t = 0.0

	r = 0.0

 10	continue
	    if (r.ge.360) r = 0.0
	    call color(BLACK)
	    call clear

	    call pushmatrix

	    call translate(0.0, 0.0, t)
	    call rotate(r, 'y')
	    call rotate(r, 'z')
	    call rotate(r, 'x')
	    call color(WHITE)

	    call drawcube(nplanes)

	    if (nplanes .eq. 1 .and. ifill .gt. 0) then
	        call polyfill(0)
	        call color(0)
	        call drawcube(nplanes)
	    endif

	    call polyfill(ifill)

	    call popmatrix

	    t = t + dt
	    if (t.gt.3.0 .or. t.lt.-18.0) dt = -dt

	    call swapbuffers

	    if (checkkey() .ne. 0) then
	    	call vexit
	    	stop
	    endif

	    r = r + dr
	goto 10

	end

c
c this routine draws the cube, using colours if available
c
	subroutine drawcube(nplanes)
	integer nplanes

	integer BLACK, RED, GREEN, YELLOW, BLUE
	integer MAGENTA, CYAN, WHITE
	parameter (BLACK = 0, RED = 1, GREEN = 2)
	parameter (YELLOW = 3, BLUE = 4, MAGENTA = 5)
	parameter (CYAN = 6, WHITE = 7)

	real carray(3, 8)
	data carray/
     +     -1.0,  -1.0,   1.0,
     +      1.0,  -1.0,   1.0,
     +      1.0,   1.0,   1.0,
     +     -1.0,   1.0,   1.0,
     +     -1.0,  -1.0,  -1.0,
     +      1.0,  -1.0,  -1.0,
     +      1.0,   1.0,  -1.0,
     +     -1.0,   1.0,  -1.0/

	if (nplanes.gt.1) call color(RED)

	call makepoly
		call move(carray(1,1), carray(2,1), carray(3,1))
		call draw(carray(1,2), carray(2,2), carray(3,2))
		call draw(carray(1,3), carray(2,3), carray(3,3))
		call draw(carray(1,4), carray(2,4), carray(3,4))
		call draw(carray(1,1), carray(2,1), carray(3,1))
	call closepoly
	
	if (nplanes.gt.1) call color(GREEN)

	call makepoly
		call move(carray(1,6), carray(2,6), carray(3,6))
		call draw(carray(1,5), carray(2,5), carray(3,5))
		call draw(carray(1,8), carray(2,8), carray(3,8))
		call draw(carray(1,7), carray(2,7), carray(3,7))
		call draw(carray(1,6), carray(2,6), carray(3,6))
	call closepoly

	if (nplanes.gt.1) call color(YELLOW)

	call makepoly
		call move(carray(1,2), carray(2,2), carray(3,2))
		call draw(carray(1,6), carray(2,6), carray(3,6))
		call draw(carray(1,7), carray(2,7), carray(3,7))
		call draw(carray(1,3), carray(2,3), carray(3,3))
		call draw(carray(1,2), carray(2,2), carray(3,2))
	call closepoly

	if (nplanes.gt.1) call color(BLUE)

	call makepoly
		call move(carray(1,1), carray(2,1), carray(3,1))
		call draw(carray(1,4), carray(2,4), carray(3,4))
		call draw(carray(1,8), carray(2,8), carray(3,8))
		call draw(carray(1,5), carray(2,5), carray(3,5))
		call draw(carray(1,1), carray(2,1), carray(3,1))
	call closepoly

	if (nplanes.gt.1) call color(MAGENTA)

	call makepoly
		call move(carray(1,3), carray(2,3), carray(3,3))
		call draw(carray(1,7), carray(2,7), carray(3,7))
		call draw(carray(1,8), carray(2,8), carray(3,8))
		call draw(carray(1,4), carray(2,4), carray(3,4))
		call draw(carray(1,3), carray(2,3), carray(3,3))
	call closepoly
	
	if (nplanes.gt.1) call color(CYAN)

	call makepoly
		call move(carray(1,1), carray(2,1), carray(3,1))
		call draw(carray(1,5), carray(2,5), carray(3,5))
		call draw(carray(1,6), carray(2,6), carray(3,6))
		call draw(carray(1,2), carray(2,2), carray(3,2))
		call draw(carray(1,1), carray(2,1), carray(3,1))
	call closepoly

	end

