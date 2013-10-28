c
c drawgrid
c
c	draw a grid in the middle of the screen
c
	subroutine drawgrid

	real x
	integer i, GREEN, YELLOW
	parameter (GREEN = 2, YELLOW = 3)

	call color(GREEN)

	call rect(0.1, 0.4, 0.9, 0.6)

	x = 0.2

	do 10 i = 1, 8
		call move2(x, 0.4)
		call draw2(x, 0.6)
		x = x + 0.1
10	continue

	call move2(0.1, 0.5)
	call draw2(0.9, 0.5)

	call color(YELLOW)

	end

c
c demonstrate some more features of text
c
	program	fmoretxt

	character device*50, fname*80
	integer BLACK
	parameter (BLACK = 0)

	print*,'Enter output device:'
	read(*,'(a)') device

	print*,'Enter a font name:'
	read(*,'(a)') fname

	call vinit(device)

	call font(fname)

	call ortho2(0.0, 1.0, 0.0, 1.0)

	call drawgrid

c
c show some scaled text on the grid (In the bottom part)
c
	call boxtext(0.1, 0.4, 0.8, 0.1,
     +      '{This is Some text] | $')

	call getkey

	call color(BLACK)
	call clear

	call drawgrid

c
c centertext causes text to be centered around the current graphics
c position this is especially usefull if you want your text to come
c out centered on a line, or a character to be centered on a point
c in a graph. A non-zero (.true.) argument turns centertext on.
c
c show a string centered on the center line
c
	call centertext(.true.)

	call boxtext(0.5, 0.5, 0.8, 0.1,
     +      '{This is Some Centered text] | $')
c
c turn centertext off. We use an argument with the value zero (.false.).
c
	call centertext(.false.)

	call getkey

	call color(BLACK)
	call clear

c
c rotate the grid so that it is the same angle as the text after
c textang for text ang.
c
	call pushmatrix
		call translate(0.5, 0.5, 0.0)
		call rotate(90.0, 'z')
		call translate(-0.5, -0.5, 0.0)

		call drawgrid
	call popmatrix

c
c turn on centered text again
c
	call centertext(.true.)

c
c set the angle to 90.
c
	call textang(90.0)

c
c draw the string
c
	call boxtext(0.5, 0.5, 0.8, 0.1,
     +      '{This is Some Rotated Centered text] | $')
c
c turn off center text
c
	call centertext(.false.)

c
c set text angle back to 90
c
	call textang(0.0)

	call getkey

	call color(BLACK)
	call clear

	call drawgrid

c
c as all the software fonts are proportionally spaced we use
c the fixedwidth call to make each character take the same amount
c of horizontal space. As with centertext this is done by passing
c fixedwidth a non-zero (.true.) argument.
c
	call fixedwidth(.true.)

	call boxtext(0.1, 0.5, 0.8, 0.1,
     +      '{This is Some Fixedwidth text] | $')

	call getkey

	call color(BLACK)
	call clear

	call drawgrid

c
c now try centered and fixewidth at the same time
c
	call centertext(.true.)

	call move2(0.5, 0.5)
	call drawstr('{This is Some Cent.Fixedwidth text] | $')

	call centertext(.false.)
	
	call getkey
	call color(BLACK)
	call clear

	call drawgrid

c
c scale the text so tha a character is the size of a box in
c the grid.
c
	call boxfit(0.8, 0.1, 8)

c
c draw the two strings fixedwidth (it is still turned on)
c
	call move2(0.1, 0.4)
	call drawstr('ABCDefgh')

	call move2(0.1, 0.5)
	call drawstr('IJKLmnop')

	call getkey

	call vexit

	end
