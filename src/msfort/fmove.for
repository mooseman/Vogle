      interface to subroutine C_move[c](x, y, z)
      real *8 x, y, z
      end

      interface to subroutine C_move2[c](x, y)
      real *8 x, y
      end

      interface to subroutine C_rmove[c](x, y, z)
      real *8 x, y, z
      end

      interface to subroutine C_rmove2[c](x, y)
      real *8 x, y
      end

      interface to subroutine C_smove2[c](x, y)
      real *8 x, y
      end

      interface to subroutine C_rsmove2[c](x, y)
      real *8 x, y
      end

      subroutine move(x, y, z)
      call C_move(x, y, z)
      end

      subroutine move2(x, y)
      call C_move2(x, y)
      end

      subroutine rmove(x, y, z)
      call C_rmove(x, y, z)
      end

      subroutine rmove2(x, y)
      call C_rmove2(x, y)
      end

      subroutine smove2(x, y)
      call C_smove2(x, y)
      end

      subroutine rsmove2(x, y)
      call C_rsmove2(x, y)
      end
