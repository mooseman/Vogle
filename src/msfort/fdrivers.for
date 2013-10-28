      interface to subroutine C_voutput[c](s[reference])
      character *(*) s
      end

      interface to subroutine C_vinit[c](s[reference])
      character *(*) s
      end

      interface to subroutine C_vnewdev[c](s[reference])
      character *(*) s
      end

      interface to subroutine C_vgetdev[c](s[reference])
      character *(*) s
      end

      interface to subroutine C_vexit[c]()
      end

      interface to subroutine C_clear[c]()
      end

      interface to subroutine C_color[c](i)
      integer *2 i
      end

      interface to subroutine C_mapcolor[c](i, r, g, b)
      integer *2 i, r, g, b
      end

      interface to function C_getdepth[c]()
      integer *2 C_getdepth
      end

      interface to function C_getkey[c]()
      integer *2 C_getkey
      end

      interface to function C_checkkey[c]()
      integer *2 C_checkkey
      end

      interface to function C_locator[c](x[reference],
     +                                   y[reference])
      integer *2 C_locator
      end

      interface to function C_slocator[c](x[reference],
     +                                   y[reference])
      integer *2 C_slocator
      end

      subroutine voutput(s)
      character *(*) s
      character *128 t_string

      call C_voutput(t_string(s))
      end

      subroutine vinit(s)
      character *(*) s
      character *128 t_string

      call C_vinit(t_string(s))
      end

      subroutine vnewdev(s)
      character *(*) s
      character *128 t_string

      call C_vnewdev(t_string(s))
      end

      subroutine vgetdev(s)
      character *(*) s
      call C_vgetdev(s)
c
c	find terminating null and space fill it all
c
      l = len(s)
      do 10 i = 1, l
          if (ichar(s(i : i)) .eq. 0) then
              do 5, j = i, l
                  s(j : j) = ' '
5             continue
          end if
10    continue
      end

      subroutine vexit
      call C_vexit
      end

      subroutine clear
      call C_clear
      end

      subroutine color(i)
      call C_color(i)
      end
  
      subroutine mapcolor(i, r, g, b)
      integer i, r, g, b
      call C_mapcolor(i, r, g, b)
      end

      integer function getdepth()
      integer *2 C_getdepth
      getdepth = C_getdepth()
      end
  
      integer function getkey()
      integer *2 C_getkey
      getkey = C_getkey()
      end
  
      integer function checkkey()
      integer *2 C_checkkey
      checkkey = C_checkkey()
      end

      integer function locator(x, y)
      integer *2 C_locator
      locator = C_locator(x, y)
      end

      integer function slocator(x, y)
      integer *2 C_slocator
      slocator = C_slocator(x, y)
      end
