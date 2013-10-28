c
c makesphere
c
c	make a sphere object
c
	subroutine makesphere

	integer SPHERE
	real i, r, z, a, RADIUS, PI
	parameter (PI = 3.1415926535, RADIUS = 10.0, SPHERE = 1)

	call makeobj(SPHERE)

c
c create the latitudinal rings
c
	    do 10 i = 0.0, 180.0, 20.0
		call pushmatrix
		    call rotate(i, 'y')
		    call circle(0.0, 0.0, RADIUS)
		call popmatrix
10	    continue
		
c
c create the longitudinal rings
c
	    call pushmatrix
		call rotate(90.0, 'x')
		do 20 a = -90.0, 90.0, 20.0
		    r = RADIUS * cos(a * PI / 180.0)
		    z = RADIUS * sin(a * PI / 180.0)
		    call pushmatrix
			call translate(0.0, 0.0, -z)
			call circle(0.0, 0.0, r)
		    call popmatrix	
20		continue
	    call popmatrix

	call closeobj

	end

c
c a demonstration of objects
c
	program fballs

	integer SPHERE
	integer BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
	real RADIUS
	parameter (RADIUS = 10.0)
	parameter(SPHERE = 1)
	parameter(BLACK = 0)
	parameter(RED = 1)
	parameter(GREEN = 2)
	parameter(YELLOW = 3)
	parameter(BLUE = 4)
	parameter(MAGENTA = 5)
	parameter(CYAN = 6)
	parameter(WHITE = 7)
	character device*50

	print*,'Enter output device:'
	read(*,'(a)') device

	call vinit(device)

c
c set up our viewing transformation
c
	call perspective(90.0, 1.0, 0.001, 500.0)
	call lookat(13.0, 13.0, 8.0, 0.0, 0.0, 0.0, 0.0)

	call color(BLACK)
	call clear

c
c Call a routine to make the sphere object
c
	call makesphere

c
c Now draw the sphere object scaled down. We use the pushmatrix
c and the popmatrix to preserve the transformation matrix so
c that only this sphere is drawn scaled. The callobj then enables
c us to draw the sphere we generated with makeobj in makesphere.
c
	call color(CYAN)

	call pushmatrix
	    call scale(0.5, 0.5, 0.5)
	    call callobj(SPHERE)
	call popmatrix

c
c now we draw the same sphere translated, with a different
c scale and color.
c
	call color(WHITE)

	call pushmatrix
	    call translate(0.0, -1.4 * RADIUS, 1.4 * RADIUS)
	    call scale(0.3, 0.3, 0.3)
	    call callobj(SPHERE)
	call popmatrix

c
c and maybe a few more times....
c

	call color(RED)

	call pushmatrix
	    call translate(0.0, RADIUS, 0.7 * RADIUS)
	    call scale(0.2, 0.2, 0.2)
	    call callobj(SPHERE)
	call popmatrix

	call color(GREEN)

	call pushmatrix
	    call translate(0.0, 1.5 * RADIUS, -RADIUS)
	    call scale(0.15, 0.15, 0.15)
	    call callobj(SPHERE)
	call popmatrix

	call color(YELLOW)

	call pushmatrix
	    call translate(0.0, -RADIUS, -RADIUS)
	    call scale(0.12, 0.12, 0.12)
	    call callobj(SPHERE)
	call popmatrix

	call color(BLUE)

	call pushmatrix
	    call translate(0.0, -2.0*RADIUS, -RADIUS)
	    call scale(0.3, 0.3, 0.3)
	    call callobj(SPHERE)
	call popmatrix

	call getkey

	call vexit

	end
