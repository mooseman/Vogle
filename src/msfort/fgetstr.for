      interface to function C_getstring[c](ibcol, 
     + string[reference])
      integer *2 C_getstring, ibcol
      character *(*) string
      end

      integer function getstring(ibcol, string)
      character *(*) string
      integer *2 C_getstring
      l = len(string)
      i = C_getstring(ibcol, string)
      if (i .lt. l) string(i + 1 : l) = ' '
      getstring = i
      return
      end
