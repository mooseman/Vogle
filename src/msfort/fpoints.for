      interface to subroutine C_point[c](x, y, z)
      real *8 x, y, z
      end

      interface to subroutine C_point2[c](x, y)
      real *8 x, y
      end

      subroutine point(x, y, z)
      call C_point(x, y, z)
      end

      subroutine point2(x, y)
      call C_point2(x, y)
      end
