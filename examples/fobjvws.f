c
c Demonstrate just how much you can put in an object
c
	program fobjviews

	integer BLACK, RED, GREEN, YELLOW, BLUE, CYAN, MAGENTA
	parameter(BLACK = 0, RED = 1, GREEN = 2, YELLOW = 3,
     +            BLUE = 4, CYAN = 5, MAGENTA = 6)
	
	integer CUBE, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT
	parameter(CUBE = 1, TOPLEFT = 2, TOPRIGHT = 3,
     +            BOTTOMLEFT = 4, BOTTOMRIGHT = 5)

	character *20 device

	print*,'Enter device name:'
	read(*,'(A)')device
	call vinit(device)
	call pushviewport

	call textsize(0.5, 0.9)
	call font('futura.m')

	call color(BLACK)
	call clear

c
c make an object that represents the cube
c
	call makecube

c
c set up an object which draws in the top left of the screen.
c
	call makeobj(TOPLEFT)
		call viewport(-1.0, 0.0, 0.0, 1.0)
		call ortho2(-5.0, 5.0, -5.0, 5.0)

		call color(RED)

		call rect(-5.0, -5.0, 5.0, 5.0)

		call perspective(40.0, 1.0, 0.1, 1000.0)
		call lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0)
c
c          Call an object within another object
c
		call callobj(CUBE)

		call color(GREEN)

		call move2(-4.5, -4.5)
		call drawstr('perspective/lookat')
	call closeobj

c
c now set up one which draws in the top right of the screen
c
	call makeobj(TOPRIGHT)
		call viewport(0.0, 1.0, 0.0, 1.0)
		call ortho2(-5.0, 5.0, -5.0, 5.0)

		call color(GREEN)

		call rect(-5.0, -5.0, 5.0, 5.0)

		call window(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0)
		call lookat(5.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0)

		call callobj(CUBE)

		call color(RED)

		call move2(-4.5, -4.5)
		call drawstr('window/lookat')
	call closeobj

c
c try the bottom left
c
	call makeobj(BOTTOMLEFT)
		call viewport(-1.0, 0.0, -1.0, 0.0)
		call ortho2(-5.0, 5.0, -5.0, 5.0)

		call color(MAGENTA)

		call rect(-5.0, -5.0, 5.0, 5.0)

		call perspective(40.0, 1.0, 0.1, 1000.0)
		call polarview(15.0, 30.0, 30.0, 30.0)

		call callobj(CUBE)

		call color(YELLOW)

		call move2(-4.5, -4.5)
		call drawstr('perspective/polarview')
	call closeobj

c
c and the bottom right
c
	call makeobj(BOTTOMRIGHT)
		call viewport(0.0, 1.0, -1.0, 0.0)
		call ortho2(-5.0, 5.0, -5.0, 5.0)

		call color(CYAN)

		call rect(-5.0, -5.0, 5.0, 5.0)

		call window(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0)
		call polarview(8.0, -18.0, -3.0, 18.0)

		call callobj(CUBE)

		call color(BLUE)

		call move2(-4.5, -4.5)
		call drawstr('window/polarview')
	call closeobj

c
c now draw them
c
	call callobj(TOPLEFT)
	call callobj(TOPRIGHT)
	call callobj(BOTTOMLEFT)
	call callobj(BOTTOMRIGHT)

	call getkey

	call vexit

	end

c
c makecube
c
c set up a cube
c
	subroutine makecube
	integer CUBE
	parameter (CUBE = 1)

	call makeobj(CUBE)

c
c The border around the cube
c
	    call rect(-5.0, -5.0, 10.0, 10.0)

c
c Make the cube from 4 squares
c
	    call pushmatrix
		call side
		call rotate(90.0, 'x')
		call side
		call rotate(90.0, 'x')
		call side
		call rotate(90.0, 'x')
		call side
	    call popmatrix

	call closeobj

	end

c
c side
c
c define a face for the cube
c
	subroutine side

	call pushmatrix
	    call translate(0.0, 0.0, 1.0)
	    call rect(-1.0, -1.0, 1.0, 1.0)
	call popmatrix

	end
