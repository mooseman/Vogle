      interface to subroutine C_getgp[c](x[reference],
     +                              y[reference],
     +                              z[reference])
      end

      interface to subroutine C_getgp2[c](x[reference],
     +                               y[reference])
      end

      interface to subroutine C_sgetgp2[c](x[reference],
     +                                y[reference])
      end

      subroutine getgp(x, y, z)
      call C_getgp(x, y, z)
      end

      subroutine getgp2(x, y)
      call C_getgp2(x, y)
      end

      subroutine sgetgp2(x, y)
      call C_sgetgp2(x, y)
      end

