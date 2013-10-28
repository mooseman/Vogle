      interface to subroutine C_patchbasis[c](
     + b1[reference], b2[reference])
      real b1(1, 1), b2(1, 1)
      end

      interface to subroutine C_patchprecision[c](n1, n2)
      integer *2 n1, n2
      end

      interface to subroutine C_patchcurves[c](n1, n2)
      integer *2 n1, n2
      end

      interface to subroutine C_rpatch[c](geomx[reference],
     +                                    geomy[reference],
     +                                    geomz[reference],
     +                                    geomw[reference])
      real geomx(1, 1), geomy(1, 1), geomz(1, 1), geomw(1, 1)
      end

      interface to subroutine C_patch[c](geomx[reference],
     +                                    geomy[reference],
     +                                    geomz[reference])
      real geomx(1, 1), geomy(1, 1), geomz(1, 1)
      end

      subroutine patchbasis(basis1, basis2)
      real basis1(4, 4), basis2(4, 4)
      call C_patchbasis(basis1, basis2)
      end

      subroutine patchprecision(n1, n2)
      call C_patchprecision(n1, n2)
      end

      subroutine patchcurves(n1, n2)
      call C_patchcurves(n1, n2)
      end

      subroutine rpatch(geomx, geomy, geomz, geomw)
      real geomx(4, 4),geomy(4, 4),geomz(4, 4),geomw(4, 4)
      call C_rpatch(geomx, geomy, geomz, geomw)
      end

      subroutine patch(geomx, geomy, geomz)
      real geomx(4, 4),geomy(4, 4),geomz(4, 4)
      call C_patch(geomx, geomy, geomz)
      end
