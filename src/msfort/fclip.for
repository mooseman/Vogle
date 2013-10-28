      interface to subroutine C_clipping[c](onoff)
      integer *2 onoff
      end

      subroutine clipping(onoff)
      integer onoff
      call C_clipping(onoff)
      end
