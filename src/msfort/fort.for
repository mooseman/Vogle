c
c  Fortran Test of Microsoft C interfaces
c
      program fort
      character *100 s
      real a(4, 4)
      real w(4, 4)
      real b(3, 4)
      real c(3, 6)
      real d(2, 6)
      
      integer getkey, locator, slocator, genobj, getopenobj, getstring
      integer backbuffer, getdepth
      logical isobj

      data a/0.0, 1.0, 2.0, 3.0,
     +       4.0, 5.0, 6.0, 7.0,
     +       8.0, 9.0, 10.0, 11.0,
     +       12.0, 13.0, 14.0, 15.0/

      data b/100.0, 200.0, 300.0,
     +       400.0, 500.0, 600.0,
     +       700.0, 800.0, 900.0,
     +       1000.0, 1100.0, 1200.0/

      data c/50.0, 60.0, 70.0,
     +       80.0, 90.0, 100.0,
     +       110.0, 120.0, 130.0, 
     +       140.0, 150.0, 160.0,
     +       170.0, 180.0, 190.0,
     +       200.0, 210.0, 220.0/


      data d/50.0, 60.00,
     +       80.0, 90.0,
     +       110.0, 120.0, 
     +       140.0, 150.0,
     +       170.0, 180.0,
     +       200.0, 210.0/

	data s/'A Sample String'/

	print*,'Calling vinit'
	call vinit(s)

	print*,'Calling vexit'
	call vexit

	print*,'Calling voutput'
	call voutput(s)

	print*,'Calling vnewdev'
	call vnewdev(s)

	print*,'Calling vgetdev'
	call vgetdev(s)
	print*,'vgetdev returns: ', s

	print*,'Calling clear'
	call clear

	print*,'Calling color(7)'
	call color(7)

	print*,'Calling mapcolor(1, 2, 3, 4)'
	call mapcolor(1, 2, 3, 4)

	print*,'Calling clipping(.true.)'
	call clipping(.true.)

	print*,'calling getkey()'
	print*,'getkey returns: ',getkey()

	print*,'calling getdepth()'
	print*,'getdepth returns: ',getdepth()

	print*,'calling locator()'
	print*,'locator returns: ',locator(x, y), x, y

	print*,'calling slocator()'
	print*,'slocator returns: ',slocator(x, y), x, y

	print*,'Calling viewport(10.0, 11.0, 12.0, 13.0)'
	call viewport(10.0, 11.0, 12.0, 13.0)

	print*,'Calling getviewport(a1, a2, a3, a4)'
	call getviewport(a1, a2, a3, a4)
	print*,'getviewport returns: ', a1, a2, a3, a4

	print*,'Calling pushviewport'
	call pushviewport

	print*,'Calling popviewport'
	call popviewport

	print*,'Calling pushattributes'
	call pushattributes

	print*,'Calling popattributes'
	call popattributes

	print*,'Calling ortho(20.0, 30.0, 40.0, 50.0, 60.0, 70.0)'
	call ortho(20.0, 30.0, 40.0, 50.0, 60.0, 70.0)

	print*,'Calling ortho2(40.0, 50.0, 60.0, 70.0)'
	call ortho2(40.0, 50.0, 60.0, 70.0)

	print*,'Calling perspective(140.0, 150.0, 160.0, 170.0)'
	call perspective(140.0, 150.0, 160.0, 170.0)

	print*,'Calling window(20.0, 30.0, 40.0, 50.0, 60.0, 70.0)'
	call window(20.0, 30.0, 40.0, 50.0, 60.0, 70.0)

	print*,'Calling pushmatrix'
	call pushmatrix

	print*,'Calling popmatrix'
	call popmatrix

	print*,'Calling polarview(240.0, 250.0, 260.0, 270.0)'
	call polarview(240.0, 250.0, 260.0, 270.0)

	print*,'Calling lookat(20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0)'
	call lookat(20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0)

	print*,'Calling move(23.0, 24.0, 25.0)'
	call move(23.0, 24.0, 25.0)

	print*,'Calling rmove(230.0, 240.0, 250.0)'
	call rmove(230.0, 240.0, 250.0)

	print*,'Calling move2(240.0, 250.0)'
	call move2(240.0, 250.0)

	print*,'Calling rmove2(40.0, 50.0)'
	call rmove2(40.0, 50.0)

	print*,'Calling smove2(540.0, 550.0)'
	call smove2(540.0, 550.0)

	print*,'Calling rsmove2(1540.0, 1550.0)'
	call rsmove2(1540.0, 1550.0)

	print*,'Calling draw(23.0, 24.0, 25.0)'
	call draw(23.0, 24.0, 25.0)

	print*,'Calling rdraw(230.0, 240.0, 250.0)'
	call rdraw(230.0, 240.0, 250.0)

	print*,'Calling draw2(240.0, 250.0)'
	call draw2(240.0, 250.0)

	print*,'Calling rdraw2(40.0, 50.0)'
	call rdraw2(40.0, 50.0)

	print*,'Calling sdraw2(540.0, 550.0)'
	call sdraw2(540.0, 550.0)

	print*,'Calling rsdraw2(1540.0, 1550.0)'
	call rsdraw2(1540.0, 1550.0)

	print*,'Calling arcprecision(44)'
	call arcprecision(44)

	print*,'Calling arc(1.0, 2.0, 3.0, 4.0, 5.0)'
	call arc(1.0, 2.0, 3.0, 4.0, 5.0)

	print*,'Calling sector(11.0, 12.0, 13.0, 14.0, 15.0)'
	call sector(11.0, 12.0, 13.0, 14.0, 15.0)

	print*,'Calling circle(11.0, 12.0, 13.0)'
	call circle(11.0, 12.0, 13.0)

	print*,'Calling curvebasis(a)'
	call prinm(4, 4, a)
	call curvebasis(a)

	print*,'Calling curveprecision(45)'
	call curveprecision(45)

	print*,'Calling rcurve(a)'
	call prinm(4, 4, a)
	call rcurve(a)
	
	print*,'Calling curve(b)'
	call prinm(3, 4, b)
	call curve(b)
	
	print*,'Calling curven(6, c)'
	call prinm(3, 6, c)
	call curven(6, c)
	
	print*,'Calling rect(10.0, 11.0, 12.0, 13.0)'
	call rect(10.0, 11.0, 12.0, 13.0)

	print*,'Calling polyfill(.false.)'
	call polyfill(.false.)

	print*,'Calling polyhatch(.true.)'
	call polyhatch(.true.)

	print*,'Calling hatchang(45.0)'
	call hatchang(45.0)

	print*,'Calling hatchpitch(5.0)'
	call hatchpitch(5.0)

	print*,'Calling poly(6, c)'
	call prinm(3, 6, c)
	call poly(6, c)

	print*,'Calling poly2(6, d)'
	call prinm(2, 6, d)
	call poly2(6, c)

	print*,'Calling makepoly()'
   	call makepoly
	
	print*,'Calling closepoly()'
   	call closepoly

	print*,'Calling font(s)'
	call font(s)

	print*,'Calling numchars()'
	print*,'Numchars returns: ', numchars()

	print*,'Calling textsize(3.0, 4.5)'
	call textsize(3.0, 4.5)

	print*,'Calling textang(33.3)'
	call textang(33.3)

	print*,'Calling fixedwidth(2)'
	call fixedwidth(2)

	print*,'Calling centertext(2)'
	call centertext(2)

	print*,'Calling getcharsize(''A'', x, y)'
	call getcharsize('A', x, y)
	print*,'x = ', x, ' y = ',y

	print*,'Calling getfontsize(x, y)'
	call getfontsize(x, y)
	print*,'x = ', x, ' y = ',y

	print*,'Calling drawchar(''K'')'
	call drawchar('K')

	print*,'Calling drawstr(''Hello'')'
	call drawstr('Hello')

	print*,'Calling strlength(s)'
	print*,'strlength returns: ',strlength(s)

	print*,'Calling boxtext(1.0, 2.0, 3.0, 4.0, s)'
	call boxtext(1.0, 2.0, 3.0, 4.0, s)

	print*,'Calling boxfit(22.3, 44.5, 11)'
	call boxfit(22.3, 44.5, 11)

	print*,'Calling translate(0.5, 0.6, 0.7)'
	call translate(0.5, 0.6, 0.7)

	print*,'Calling scale(0.5, 0.6, 0.7)'
	call scale(0.5, 0.6, 0.7)

	print*,'Calling rotate(22.4, ''x'')'
	call rotate(22.4, 'x')

	print*,'Calling patchbasis(a, a)'
	call prinm(4, 4, a)
	call patchbasis(a, a)

	print*,'calling patchprecision(34, 45)'
	call patchprecision(34, 45)

	print*,'calling patchcurves(134, 415)'
	call patchcurves(134, 415)

	print*,'calling rpatch(a, a, a, a)'
	call rpatch(a, a, a, a)

	print*,'calling patch(a, a, a)'
	call patch(a, a, a)

	print*,'calling point(500.0, 600.0, 700.0)'
	call point(500.0, 600.0, 700.0)

	print*,'calling point2(500.0, 600.0)'
	call point2(500.0, 600.0)

	print*,'Calling makeobj(3)'
	call makeobj(3)

	print*,'Calling closeobj()'
	call closeobj

	print*,'Calling genobj()'
	print*,'genobj returns: ', genobj()

	print*,'calling getopenobj()'
	print*,'getopenobj returns: ', getopenobj()
	
	print*,'Calling callobj(23)'
	call callobj(23)

	print*,'calling isobj(5)'
	print*,'isobj returns: ',isobj(5)

	print*,'Calling loadobj(8, s)'
	call loadobj(8, s)

	print*,'Calling saveobj(9, s)'
	call saveobj(9, s)

	print*,'Calling getgp(x, y, z)'
	call getgp(x, y, z)
	print*,'x = ', x, ' y = ', y, ' z = ', z

	print*,'Calling getgp2(x, y)'
	call getgp2(x, y)
	print*,'x = ', x, ' y = ', y

	print*,'Calling sgetgp2(x, y)'
	call sgetgp2(x, y)
	print*,'x = ', x, ' y = ', y

	print*,'Calling getmatrix(w)'
	call getmatrix(w)
	call prinm(4, 4, w)

	print*,'Calling multmatrix(a)'
	call multmatrix(a)

	print*,'Calling loadmatrix(a)'
	call loadmatrix(a)

	print*,'Calling getstring(3, s)'
	print*,'getstring(3, s) returns: ',
     +  getstring(3, s), s

	print*,'Calling getaspect()'
	print*,'getaspect returns: ',
     +  getaspect()

	print*,'Calling getfactors(x, y)'
	call getfactors(x, y)
	print*,'getfactors returns: ',x, y

	print*,'Calling getdisplaysize(x, y)'
	call getdisplaysize(x, y)
	print*,'getdisplaysize returns: ',x, y

	print*,'Calling backbuffer: ', backbuffer()

	print*,'Calling frontbuffer'
	call frontbuffer

	print*,'Calling swapbuffers'
	call swapbuffers

	print*, 'Calling up(1.3, 2.3, 3.3)'
	call up(1.3, 2.3, 3.3)

	print*,'Calling prefsize(200, 200)'
	call prefsize(200, 200)

	print*,'Calling prefposition(20, 30)'
	call prefposition(20, 30)

	print*,'Calling backface(.true.)'
	call backface(.true.)

	print*,'Calling backfacedir(1)'
	call backfacedir(1)
	
	
	end

	subroutine prinm(n, m, a)
    	real a(n, m)
        do 10 i = 1, n
		print*,(a(i,j), j = 1, m)
10  	continue
        end

