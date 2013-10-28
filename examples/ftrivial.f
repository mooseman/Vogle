c 
c  the basic test program for a driver if we can draw a line and do
c  hardware text we are almost there!
c
	program ftrivial
	integer BLACK, GREEN
	parameter (BLACK = 0, GREEN = 2)
	character*50 device

c
c  read in device name
c
	print*,'Enter output device:'
	read(*,'(a)')device

	call vinit(device)
c
c  set font to hardware text large 
c
	call font('large')		
c
c  set current color to black 
c
	call color(BLACK)
c
c  clear to current color
c
	call clear
c
c  we want to draw in green 
c
	call color(GREEN)
c
c  draw a horizontal line at y = 0 
c
	call move2(-1.0, 0.0)
	call draw2(1.0, 0.0)
c
c  pause for some input 
c
	call getkey
c
c  draw a line along x = 0 
c
	call move2(0.0, 0.0)
	call draw2(0.0, 1.0)
c
c  move to the middle of the screen 
c
	call move2(0.0, 0.0)
c
c  draw 'Hello' starting at the origin 
c
	call drawstr('Hello')
c
c  pause again 
c
	call getkey
c
c  set screen back to original state 
c
	call vexit
	end
