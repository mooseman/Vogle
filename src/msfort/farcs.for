      interface to subroutine C_arc[c](x, y, r, s, e)
      real *8 x, y, r, s, e
      end

      interface to subroutine C_sector[c](x, y, r, s, e)
      real *8 x, y, r, s, e
      end

      interface to subroutine C_circle[c](x, y, r)
      real *8 x, y, r
      end

      interface to subroutine C_arcprecision[c](n)
      integer *2 n
      end

      interface to subroutine C_circleprecision[c](n)
      integer *2 n
      end

      subroutine arc(x, y, r, s, e)
      call C_arc(x, y, r, s, e)
      end

      subroutine sector(x, y, r, s, e)
      call C_sector(x, y, r, s, e)
      end

      subroutine circle(x, y, r)
      call C_circle(x, y, r)
      end
 
      subroutine arcprecision(n)
      call C_arcprecision(n)
      end
 
      subroutine circleprecision(n)
      call C_circleprecision(n)
      end
