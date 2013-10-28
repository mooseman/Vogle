c
c most of the things in this program have been done before but it has
c a certain novelty value.
c
	program fworld

	integer BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
	parameter(BLACK = 0)
	parameter(RED = 1)
	parameter(GREEN = 2)
	parameter(YELLOW = 3)
	parameter(BLUE = 4)
	parameter(MAGENTA = 5)
	parameter(CYAN = 6)
	parameter(WHITE = 7)

	integer SPHERE
	real RADIUS, PI
	parameter (RADIUS = 10.0, PI = 3.1415926535, SPHERE = 1)

	character *20 dev
	
	print*,'Enter device:'
	read(*,'(a)') dev
	call vinit(dev)

	call clipping(.false.)

	call font('futura.m')

	call perspective(80.0, 1.0, 0.001, 50.0)
	call lookat(13.0, 13.0, 8.0, 0.0, 0.0, 0.0, 0.0)

	call color(BLACK)
	call clear

	call makesphere

c
c 	draw the main one in cyan
c
	call color(CYAN)

	call callobj(SPHERE)

c
c	draw a smaller one outside the main one in white
c
	call color(WHITE)

	call pushmatrix
		call translate(0.0, -1.4 * RADIUS, 1.4 * RADIUS)
		call scale(0.3, 0.3, 0.3)
		call callobj(SPHERE)
	call popmatrix

c
c	scale the text
c
	call boxfit(2.0 * PI * RADIUS, 0.25 * RADIUS, 31)

c
c	now write the text in rings around the main sphere
c

	call color(GREEN)
	call showroundtext('Around the world in eighty days ')

	call color(BLUE)
c
c	note: that software text is rotated here as
c	anything else would be whether you use textang
c	or rotate depends on what you are trying to do.
c	Experience is the best teacher here.
c
	call rotate(90.0, 'x')
	call showroundtext('Around the world in eighty days ')

	call color(RED)
	call rotate(90.0, 'z')
	call showroundtext('Around the world in eighty days ')

	call getkey

	call vexit

	end
c
c showroundtext
c
c	draw string str wrapped around a circle in 3d
c
	subroutine showroundtext(str)
	character *(*) str

	real i, inc, RADIUS
	parameter (RADIUS = 10.0)
	integer j

	inc = 360.0 / float(nchars(str))

	j = 1
	do 10 i = 0.0, 360.0, inc
		call pushmatrix
c
c 			find the spot on the edge of the sphere
c 			by making it (0, 0, 0) in world coordinates
c
			call rotate(i, 'y')
			call translate(0.0, 0.0, RADIUS)

			call move(0.0, 0.0, 0.0)

			call drawchar(str(j:j))
			j = j + 1
		call popmatrix
10	continue

	end

c
c makesphere
c
c	create the sphere object
c
	subroutine makesphere
	integer SPHERE
	parameter (SPHERE = 1)
	parameter(PI = 3.1415926535)
	parameter(RADIUS = 10.0)
	real i

	call makeobj(SPHERE)

	do 10 i = 0.0, 180.0, 20.0
		call pushmatrix
			call rotate(i, 'y')
			call circle(0.0, 0.0, RADIUS)
		call popmatrix
10	continue
	
	call pushmatrix
		call rotate(90.0, 'x')
		do 20 a = -90.0, 90.0, 20.0
			r = RADIUS * cos(a*PI/180.0)
			z = RADIUS * sin(a*PI/180.0)
			call pushmatrix
				call translate(0.0, 0.0, -z)
				call circle(0.0, 0.0, r)
			call popmatrix	
20		continue
	call popmatrix

	call closeobj

	return
	end
c
c nchars
c
c	find the number of characters in the string str
c
	integer function nchars(str)
	character *(*) str
	
	do 10 i = len(str), 1, -1
		if (str(i:i) .ne. ' ') then
			nchars = i
			return
		end if
10	continue
	nchars = 0
	return
	end
