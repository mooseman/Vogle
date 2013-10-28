c 
c  A program showing basic line drawing, text and (if applicable)
c  colour. As none of the projection routines have been called we
c  move and draw in the initial coordinate system -1.0 to 1.0.
c
	program fsimple
	integer BLACK, GREEN
	parameter (BLACK = 0, GREEN = 2)
	character device*50, fname*80, p*11
	data p/'Hello world'/

	print*,'Enter output device:'
	read(*,'(a)') device

	print*,'Enter a font name:'
	read(*,'(a)') fname
c
c  set up device 
c
	call vinit(device)
c
c  change font to the argument 
c
	call font(fname)
c
c  set current color
c
	call color(BLACK)
c
c  clear screen to current color 
c
	call clear
c
c
	call color(GREEN)
c
c  2 d move to start where we want drawstr to start 
c
	call move2(-0.9, 0.9)
c
c  draw string in current color 
c
	call drawstr('A Simple Example')

c
c  the next four lines draw the x 
c
	call move2(0.0, 0.0)
	call draw2(0.76, 0.76)
	call move2(0.0, 0.76)
	call draw2(0.76, 0.0)

	call move2(0.0, 0.5)
	call drawstr('x done')
c
	call drawstr('next sentence')

	call move2(0.0, 0.1)
	do 10 i = 1, 11
		call drawchar(p(i:i))
10	continue

c 
c  the next five lines draw the square
c
	call move2(0.0, 0.0)
	call draw2(0.76, 0.0)
	call draw2(0.76, 0.76)
	call draw2(0.0, 0.76)
	call draw2(0.0, 0.0)
c
c  wait for some input 
c
	call getkey
c
c  set the screen back to its original state 
c
	call vexit
	end
