
c
c This program shows some of the simple primitives.
c
	program fshapes
	integer   BLACK, RED, GREEN, BLUE, MAGENTA, WHITE
	parameter(BLACK = 0)
	parameter(RED = 1, GREEN = 2, BLUE = 4, MAGENTA = 5, WHITE = 7)
	character*50 device

	print*,'Enter output device:'
	read(*,'(a)')device

	call vinit(device)

c 
c the two lines below clear the screen to white if we have
c colours, on a monochrome device color is ignored so the
c screen will be cleared to its background color, normally black.
c
	call color(BLACK)
	call clear()

c
c set the screen to be 2.0 units wide and 2.0 units wide, with
c the drawable coordinates going from -1.0 to 1.0.
c
	call ortho2(-1.0, 1.0, -1.0, 1.0)

c
c set the text size. After this call no characters in the
c current font will be wider than 0.1 or higher than 0.1 in
c world units. As the window is currently 2.0 units wide and
c 2.0 units high text will be about one twentieth of the screen
c size.
c
	call textsize(0.1, 0.1)

	call color(MAGENTA)

c
c okay, so we want to draw in the range -1 to 1, but we
c only want to draw in the top lefthand corner of the
c screen. The call to viewport allows us to do this. As
c viewport always takes screen coordinates, which are 
c always in the range of -1 to 1 we can change always
c change the viewport to somewhere else on the screen
c by giving a range in -1 to 1.
c
	call viewport(-1.0, 0.0, 0.0, 1.0)

c
c write out a heading
c
	call move2(-0.9, -0.5)
	call drawstr('rect')

c
c draw a rectangle around the points (-0.2, -0.2), (-0.2, 0.2),
c (0.3, 0.2), and (0.3, -0.2).
c
	call rect(-0.2, -0.2, 0.3, 0.2)

	call color(BLUE)

c
c now we want to draw in the top right corner of the screen
c
	call viewport(0.0, 1.0, 0.0, 1.0)

	call move2(-0.9, -0.5)
	call drawstr('circle')

c
c draw a circle of radius 0.4 around the point (0.0, 0.0)
c
	call circle(0.0, 0.0, 0.4)

	call color(GREEN)

c
c draw in bottom left corner 
c
	call viewport(-1.0, 0.0, -1.0, 0.0)

	call move2(-0.9, -0.5)
	call drawstr('ellipse')

c
c To draw an ellipse we change the aspect ratio so it is no longer
c 1 and call circle. In this case we use ortho2 to make the square
c viewport appear to be higher than it is wide. Alternatively you
c could use arc to construct one.
c
c The call to pushmatrix saves the current viewing transformation.
c After the ortho2 has been done, we restore the current viewing
c transformation with a call to popmatrix. (Otherwise everything
c after the call to ortho would come out looking squashed as the
c world aspect ratio is no longer 1).
c
	call pushmatrix()
		call ortho2(-1.0, 1.0, -1.0, 2.0)
		call circle(0.0, 0.5, 0.4)
	call popmatrix()

	call color(RED)
c
c now draw in bottom right corner
c
	call viewport(0.0, 1.0, -1.0, 0.0)

	call move2(-0.9, -0.5)
	call drawstr('arc')

c
c draw an arc centered at (0.0, 0.0), radius of 0.4. 0.0 is the start
c angle and 90.0 is the end angle of the arc being drawn. So this
c draws a quarter circle.
c
	call arc(0.0, 0.0, 0.4, 0.0, 90.0)

	call getkey()

	call vexit()

	end
