      interface to subroutine C_makeobj[c](n)
      integer *2 n
      end

      interface to subroutine C_closeobj[c]()
      end

      interface to subroutine C_delobj[c](n)
      integer *2 n
      end

      interface to function C_genobj[c]()
      integer *2 C_genobj
      end

      interface to function C_getopenobj[c]()
      integer *2 C_getopenobj
      end

      interface to subroutine C_callobj[c](n)
      integer *2 n
      end

      interface to function C_isobj[c](n)
      integer *2 n, C_isobj
      end

      interface to subroutine C_saveobj[c](n, s[reference])
      integer *2 n
      character *(*) s
      end

      interface to subroutine C_loadobj[c](n, s[reference])
      integer *2 n
      character *(*) s
      end

      subroutine makeobj(n)
      call C_makeobj(n)
      end

      subroutine closeobj
      call C_closeobj
      end

      subroutine delobj(n)
      call C_delobj(n)
      end

      integer function genobj()
      integer *2 C_genobj
      genobj = C_genobj()
      end
      
      integer function getopenobj()
      integer *2 C_getopenobj
      getopenobj = C_getopenobj()
      end

      subroutine callobj(n)
      call C_callobj(n)
      end

      integer function isobj(n)
      integer *2 C_isobj
      isobj = C_isobj(n)
      end

      subroutine saveobj(n , s)
      integer n
      character *(*) s
      character *128 t_string
      call C_saveobj(n, t_string(s))
      end

      subroutine loadobj(n , s)
      integer n
      character *(*) s
      character *128 t_string
      call C_loadobj(n, t_string(s))
      end
