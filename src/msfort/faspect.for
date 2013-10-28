      interface to subroutine C_getfactors[c](x[reference],
     +                                      y[reference])
      real x, y
      end

      interface to function C_getaspect[c]()
      real C_getaspect
      end
      

      interface to subroutine C_getdisplaysize[c](x[reference],
     +                                      y[reference])
      real x, y
      end

      subroutine getfactors(x, y)
      call C_getfactors(x, y)
      end

      real function getaspect()
      real C_getaspect
      getaspect = C_getaspect()
      return
      end

      subroutine getdisplaysize(x, y)
      call C_getdisplaysize(x, y)
      end
