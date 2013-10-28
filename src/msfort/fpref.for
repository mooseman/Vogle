      interface to subroutine C_prefposition[c](x, y)
      integer *2 x, y
      end

      interface to subroutine C_prefsize[c](x, y)
      integer *2 x, y
      end

      subroutine prefposition(x, y)
      integer x, y
      call C_prefposition(x, y)
      end

      subroutine prefsize(x, y)
      integer x, y
      call C_prefsize(x, y)
      end
