      character *128 function t_string(s)
      character *(*) s
c
c  Truncates and NULL terminates a string
c
      t_string = s

      do 10 i = len(s), 1, -1
          if (s(i:i) .ne. ' ') then
	      t_string(i+1 : i+1) = char(0)
              return
          end if
10    continue
      t_string(1 : 1) = char(0)
      end
