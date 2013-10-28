      interface to subroutine C_curvebasis[c](
     + b[reference])
      real b(*)
      end

      interface to subroutine C_curveprecision[c](nsegs)
      integer *2 nsegs
      end

      interface to subroutine C_rcurve[c](geom[reference])
      real geom(1,1)
      end

      interface to subroutine C_curve[c](geom[reference])
      real geom(1,1)
      end

      interface to subroutine C_curven[c](n, 
     + geom[reference])
      integer *2 n
      real geom(1,1)
      end

      subroutine curvebasis(basis)
      real basis(4, 4)
      call C_curvebasis(basis)
      end

      subroutine curveprecision(nsegs)
      call C_curveprecision(nsegs)
      end

      subroutine rcurve(geom)
      real geom(4, 4)
      call C_rcurve(geom)
      end

      subroutine curve(geom)
      real geom(4, 3)
      call C_curve(geom)
      end

      subroutine curven(n, geom)
      real geom(1, 1)
      call C_curven(n, geom)
      end
