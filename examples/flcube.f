
	program flcube
	parameter(TRANS = 20.0)

        integer BLACK
        parameter (BLACK = 0)

	character *10 device, but*1
	integer getdepth, checkkey, slocator, backbuffer

	print*, 'Enter output device:'
	read(*, '(a)') device

	call prefposition(50, 50)
	call prefsize(500, 500)

	call vinit(device)

	call window(-800.0, 800.0, -800.0, 800.0, -800.0, 800.0)
	call lookat(0.0, 0.0, 1500.0, 0.0, 0.0, 0.0, 0.0)

	tdir = TRANS

	call makeobj(1)
		call makepoly
			call rect(-200.0, -200.0, 200.0, 200.0)
		call closepoly
	call closeobj


	nplanes = getdepth()
	if (nplanes .eq. 1) call makecubes(0)

	call makecubes(1)

	call backface(1)
c
c Setup drawing into the backbuffer....
c
	if (backbuffer().lt.0) then
		call vexit
		write(*,*)'Device can''t support doublebuffering'
		stop
	endif

1	continue
		idum = slocator(x, y)
		call pushmatrix
			call rotate(100.0 * x, 'y')
			call rotate(100.0 * y, 'x')
			call color(BLACK)
			call clear
			call callobj(3)
			if (nplanes .eq. 1) call callobj(2)
		call popmatrix
		call swapbuffers

		
		but = char(checkkey())
		if (but .eq. 'x') then
			call translate(tdir, 0.0, 0.0)
		else if (but .eq. 'y') then
			call translate(0.0, tdir, 0.0)
		else if (but .eq. 'z') then
			call translate(0.0, 0.0, tdir)
		else if (but .eq. '-') then
			tdir = -tdir
		else if (but .eq. '+') then
			tdir = TRANS
		else if (but .eq. 'q' .or. ICHAR(but) .eq. 27) then
			call vexit
			stop
		end if

	goto 1
	end

	subroutine makecubes(fill)
	integer	fill
        integer BLACK, RED, GREEN, YELLOW, BLUE,
     +          CYAN, MAGENTA, WHITE
        parameter (BLACK = 0, RED = 1, GREEN = 2, YELLOW = 3,
     +		 BLUE = 4, CYAN = 5, MAGENTA = 6, WHITE = 7)


	call makeobj(fill + 2)
		if (fill .ne. 0) then
			call polyfill(1)
		else
			call polyfill(0)
			call color(BLACK)
		end if

		call pushmatrix
			call translate(0.0, 0.0, 200.0)
			if (fill .ne. 0) call color(RED)
			call callobj(1)
		call popmatrix

		call pushmatrix
			call translate(200.0, 0.0, 0.0)
			call rotate(90.0, 'y')
			if (fill .ne. 0) call color(GREEN)
			call callobj(1)
		call popmatrix

		call pushmatrix
			call translate(0.0, 0.0, -200.0)
			call rotate(180.0, 'y')
			if (fill .ne. 0) call color(BLUE)
			call callobj(1)
		call popmatrix

		call pushmatrix
			call translate(-200.0, 0.0, 0.0)
			call rotate(-90.0, 'y')
			if (fill .ne. 0) call color(CYAN)
			call callobj(1)
		call popmatrix

		call pushmatrix
			call translate(0.0, 200.0, 0.0)
			call rotate(-90.0, 'x')
			if (fill .ne. 0) call color(MAGENTA)
			call callobj(1)
		call popmatrix

		call pushmatrix
			call translate(0.0, -200.0, 0.0)
			call rotate(90.0, 'x')
			if (fill .ne. 0) call color(YELLOW)
			call callobj(1)
		call popmatrix

	call closeobj

	return
	end
