      interface to subroutine C_rect[c](a, b, c, d)
      real *8 a, b, c, d
      end

      subroutine rect(a, b, c, d)
      call C_rect(a, b, c, d)
      end
