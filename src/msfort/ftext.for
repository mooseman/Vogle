      interface to subroutine C_font[c](name[reference])
      character *(*) name
      end

      interface to subroutine C_textsize[c](x, y)
      real *8 x, y
      end

      interface to subroutine C_boxtext[c](x, y, a, b,
     +  s[reference])
      real*8	x, y, a, b
      character *(*)	s
      end
      
      interface to subroutine C_boxfit[c](x, y, n)
      real *8 x, y
      integer *2 n
      end

      interface to subroutine C_textang[c](x)
      real *8 x
      end
      
      interface to subroutine	C_drawchar[c](c)
      integer *2 c
      end

      interface to subroutine C_drawstr[c](str[reference])
      character *(*) str
      end
      
      interface to subroutine C_getfontsize[c](x[reference],
     +                                      y[reference])
      real x, y
      end

      interface to subroutine C_getcharsize[c](c, x[reference],
     +                                      y[reference])
      character *1 c
      real x, y
      end

      interface to subroutine C_fixedwidth[c](onoff)
      integer *2 onoff
      end

      interface to subroutine C_centertext[c](onoff)
      integer *2 onoff
      end

      interface to function C_numchars[c]()
      integer *2 C_numchars
      end

      interface to function C_strlength[c](str[reference])
      real C_strlength
      character *(*) str
      end
      
      subroutine font(name)
      character *(*) name
      character *128 t_string
      call C_font(t_string(name))
      return 
      end
      
      subroutine textsize(x, y)
      call C_textsize(x, y)
      end

      subroutine boxtext(a, b, c, d, name)
      character *(*) name
      character *128 t_string
      call C_boxtext(a, b, c, d, t_string(name))
      return 
      end
      
      subroutine boxfit(x, y, n)
      call C_boxfit(x, y, n)
      end
      
      subroutine textang(x)
      call C_textang(x)
      end

      subroutine drawchar(c)
      character *1 c
      call C_drawchar(ichar(c))
      end
      
      subroutine drawstr(name)
      character *(*) name
      character *128 t_string
      call C_drawstr(t_string(name))
      end

      subroutine getfontsize(x, y)
      call C_getfontsize(x, y)
      end

      subroutine getcharsize(c, x, y)
      character *1 c
      call C_getcharsize(c, x, y)
      end

      subroutine fixedwidth(onoff)
      integer onoff
      call C_fixedwidth(onoff)
      end

      subroutine centertext(onoff)
      integer onoff
      call C_centertext(onoff)
      end

      integer function numchars()
      integer*2 C_numchars
      numchars = C_numchars()
      end
      
      real function strlength(name)
      character *(*) name
      character *128 t_string
      real C_strlength
      strlength = C_strlength(t_string(name))
      return
      end


