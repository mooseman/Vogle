      interface to subroutine C_draw[c](x, y, z)
      real *8 x, y, z
      end

      interface to subroutine C_draw2[c](x, y)
      real *8 x, y
      end

      interface to subroutine C_rdraw[c](x, y, z)
      real *8 x, y, z
      end

      interface to subroutine C_rdraw2[c](x, y)
      real *8 x, y
      end

      interface to subroutine C_sdraw2[c](x, y)
      real *8 x, y
      end

      interface to subroutine C_rsdraw2[c](x, y)
      real *8 x, y
      end

      subroutine draw(x, y, z)
      call C_draw(x, y, z)
      end

      subroutine draw2(x, y)
      call C_draw2(x, y)
      end

      subroutine rdraw(x, y, z)
      call C_rdraw(x, y, z)
      end

      subroutine rdraw2(x, y)
      call C_rdraw2(x, y)
      end

      subroutine sdraw2(x, y)
      call C_sdraw2(x, y)
      end

      subroutine rsdraw2(x, y)
      call C_rsdraw2(x, y)
      end
