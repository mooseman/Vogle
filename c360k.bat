rem echo off
rem
rem	Copies a 1.2M disk of VOGLE onto 3 360K diskettes
rem	Copies 3 360K diskettes onto a 1.2M disk or a Hard disk
rem	(Copy c360k.bat to the hard disk first)
rem
rem	Usage c360k from to
rem	eg:   c:> a:
rem           a:> cd vogle
rem           a:> c360k . b:
rem
rem     or: to get vogle OFF 3 360k disks
rem	      c:> copy b:\vogle\c360k.bat
rem           c:> c360k b:\vogle .            (make a dir .\vogle)
rem           This time you change the source disks!
rem
rem 	Stuff is copied thus: SRC/ Disk 1
rem			      DOCS/ DRIVERS/ and EXAMPLES/ Disk 2
rem			      HERSHEY/ Disk 3
rem
echo PLACE DISK 1 IN DRIVE
pause
echo MAKING DIRECTORIES....
md %2\vogle
md %2\vogle\src
md %2\vogle\src\msfort
md %2\vogle\src\sunfort
copy %1\*.* %2\vogle
echo COPYING SRC....
copy %1\src\*.* %2\vogle\src
echo COPYING SRC\MSFORT\....
copy %1\src\msfort\*.* %2\vogle\src\msfort
echo COPYING SRC\SUNFORT\....
copy %1\src\sunfort\*.* %2\vogle\src\sunfort
echo 'DONE COPYING TO/FROM DISK 1'
echo 'PLACE DISK 2 IN DRIVE'
pause
echo MAKING DIRECTORIES
md %2\vogle
md %2\vogle\docs
md %2\vogle\drivers
md %2\vogle\drivers\ibmpc
md %2\vogle\examples
echo COPYING DOCS....
copy %1\docs\*.* %2\vogle\docs
echo COPYING DRIVERS....
copy %1\drivers\*.* %2\vogle\drivers
echo COPYING DRIVERS\IBMPC....
copy %1\drivers\ibmpc\*.* %2\vogle\drivers\ibmpc
echo COPYING EXAMPLES....
copy %1\examples\*.* %2\vogle\examples
echo 'DONE COPYING TO/FROM DISK 2'
echo PLACE DISK 3 IN DRIVE
pause
echo MAKING DIRECTORIES
md %2\vogle
md %2\vogle\hershey
md %2\vogle\hershey\fonts
md %2\vogle\hershey\data
md %2\vogle\hershey\src
copy %1\hershey\*.* %2\vogle\hershey
echo COPYING FONTS
copy %1\hershey\fonts\*.* %2\vogle\hershey\fonts
echo COPYING DATA
copy %1\hershey\data\*.* %2\vogle\hershey\data
echo COPYING SRC
copy %1\hershey\src\*.* %2\vogle\hershey\src
echo 'DONE COPYING TO/FROM DISK 3'
