c
c display all the hershey fonts and demonstrate textang
c
	program fcirctxt

	character*40 str1, str2, str3, str4, fonts(22)
	character*100 buf
	integer BLACK, YELLOW, GREEN
	integer i
	parameter (BLACK = 0, YELLOW = 3, GREEN = 2)
	data fonts/ 'astrology', 'cursive', 'futura.l',
     +  	'futura.m', 'gothic.eng', 'gothic.ger',
     +  	'gothic.ita', 'greek', 'japanese', 'markers',
     +  	'math.low', 'math.upp', 'meteorology', 'music',
     +  	'cyrillic', 'script', 'symbolic', 'times.g',
     +  	'times.ib', 'times.i', 'times.r', 'times.rb' /

	data str1/ 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' /
	data str2/ 'abcdefghijklmnopqrstuvwxyz' /
	data str3/ '1234567890+-=!@#$%^&*(){}[]' /
	data str4/ '<>,./?~`\|_BONK,blark' /

	print*,'Enter output device:'
	read(*,'(a)')buf

	call vinit(buf)

	call color(BLACK)
	call clear

c
c define the world space
c
	call ortho2(-14.0, 14.0, -14.0, 14.0)

	do 10 i = 1, 22

c
c textang is used to specify the orientation of text. As
c we want the title to come out straight we make sure it is
c zero each time we go through this loop.
c
	    call textang(0.0)

c
c do the title
c
	    call color(YELLOW)
	    call font('futura.m')
	    write(buf, '(''This is Hershey font '',a)') fonts(i)
	    call boxtext(-11.0, 12.0, 20.0, 1.0, buf)

c
c draw a box around the title
c
	    call rect(-11.0, 12.0, 9.0, 13.0)

	    call color(GREEN)

c
c grab a font from the table
c
	    call font(fonts(i))

c
c show the outer ring
c
	    call textsize(1.5, 1.5)
	    call ShowCircularText(11.0, str1)

c
c show the second ring
c
	    call textsize(1.3, 1.3)
	    call ShowCircularText(8.5, str2)

c
c show the third ring
c
	    call textsize(1.1, 1.1)
	    call ShowCircularText(7.0, str3)

c
c show the inside ring
c
	    call textsize(0.9, 0.9)
	    call ShowCircularText(5.0, str4)

	    call getkey

	    call color(BLACK)
	    call clear
10	continue

	call vexit

	end
c
c nchars
c
c return the real length of a string padded with blanks
c
	integer function nchars(str)
	character *(*) str

	do 10 i = len(str), 1, -1
	    if (str(i:i) .ne. ' ') then
	    	nchars = i
	    	return
	    end if
10      continue

	nchars = 0

	return

	end
c
c ShowCircularText
c
c	show a ring of text
c
	subroutine ShowCircularText(r, str)
	real r
	character*(*) str

	real i, inc, x, y, a, pi
	integer j
	character*1 c
	parameter (pi = 3.1415926535)

	j = 1
	inc = 360.0 / nchars(str)

	do 10 i = 0, 360.0, inc
c
c calculate the next drawing position
c
	    c = str(j:j)
	    x = r * cos(i * pi / 180.0)
	    y = r * sin(i * pi / 180.0)
	    call move2(x, y)
c
c calculate angle for next character
c
	    a = 90.0 + i
c
c set the orientation of the next character
c
	    call textang(a)
c
c draw the character
c
	    call drawchar(c)
	    j = j + 1
10	continue

	end
