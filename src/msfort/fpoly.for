      interface to subroutine C_polyfill[c](onoff)
      integer *2 onoff
      end
     
      interface to subroutine C_hatchang[c](angle)
      real *8 angle
      end

      interface to subroutine C_hatchpitch[c](pitch)
      real *8 pitch
      end

      interface to subroutine C_polyhatch[c](onoff)
      integer *2 onoff
      end

      interface to subroutine C_poly2[c](n , p[reference])
      integer *2 n
      real p(1, 1)
      end

      interface to subroutine C_poly[c](n , p[reference])
      integer *2 n
      real p(1, 1)
      end

      interface to subroutine C_makepoly[c]()
      end

      interface to subroutine C_closepoly[c]()
      end

      interface to subroutine C_backface[c](onoff)
      integer *2 onoff
      end

      interface to subroutine C_backfacedir[c](dir)
      integer *2 dir
      end

      subroutine polyfill(onoff)
      integer onoff
      call C_polyfill(onoff)
      end

      subroutine hatchang(ang)
      call C_hatchang(ang)
      end

      subroutine hatchpitch(pitch)
      call C_hatchpitch(pitch)
      end

      subroutine polyhatch(onoff)
      integer onoff
      call C_polyhatch(onoff)
      end

      subroutine poly2(n, p)
      real p(1, 1)
      call C_poly2(n , p)
      end

      subroutine poly(n, p)
      real p(1, 1)
      call C_poly(n , p)
      end

      subroutine makepoly
      call C_makepoly
      end

      subroutine closepoly
      call C_closepoly
      end

      subroutine backface(onoff)
      integer onoff
      call C_backface(onoff)
      end

      subroutine backfacedir(dir)
      integer dir
      call C_backfacedir(dir)
      end

