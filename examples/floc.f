c
c a routine to demonstrate using locator.
c
	program flocator

	character dev*20
	integer bt, BLACK, GREEN, BLUE
	real x, y, sx, sy
	logical act, curpnt
	parameter (BLACK = 0, GREEN = 2, BLUE = 4)
c
c Note the declaration of the function locator below
c
	integer locator

	print*,'Enter device name:'
	read(*,'(a)') dev

	call vinit(dev)

	call color(BLACK)
	call clear

	call color(BLUE)

c
c	draw some axes
c
	call move2(0.0, 1.0)
	call draw2(0.0, -1.0)

	call move2(1.0, 0.0)
	call draw2(-1.0, 0.0)

	call color(GREEN)

	act = .false.
	curpnt = .false.
c
c	locator returns whether a mouse button has been
c	pressed or not. In a device such as the tektronix
c	where you have to wait for a keypress to get the
c	position of the crosshairs locator returns 0
c	automatically on every second call. A return value
c	of 2 indicates the second mouse button has been pressed.
c	A return value of 1 indicates the first mouse button has
c	been pressed. We wait for the locator to return zero so
c	that we know the mouse button has been released.
c

1	continue
		bt = locator(x, y)
		if (bt .eq. -1) then
			call vexit
			print*,'No locator device found'
			stop
		else if (bt .eq. 2) then
			call vexit
			stop
		else if (bt .eq. 0) then
			act = .true.
		else if (act) then 
			act = .false.
			if (bt .eq. 1) then
				if (curpnt) then
					call move2(sx, sy)
					call draw2(x, y)
					curpnt = .false.
				else
					curpnt = .true.
				end if

				sx = x
				sy = y
			end if
		end if
	goto 1

	end
