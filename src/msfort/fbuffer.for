      interface to function C_backbuffer[c]()
      integer *2 C_backbuffer
      end

      interface to subroutine C_frontbuffer[c]()
      end

      interface to subroutine C_swapbuffers[c]()
      end

      integer function backbuffer()
      integer*2 C_backbuffer
      backbuffer = C_backbuffer()
      end

      subroutine frontbuffer
      call C_frontbuffer
      end

      subroutine swapbuffers
      call C_swapbuffers
      end
