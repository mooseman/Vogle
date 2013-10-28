cd src\msfort
make F=%1 makefile.msc
if errorlevel > 0 goto end
cd ..
make F=%1 makefile.msc
if errorlevel > 0 goto end
make F=%1 fmakefil.msc
if errorlevel > 0 goto end
cd ..\examples
command /c f_2_for
make F=%1 fmakefil.msc
if errorlevel > 0 goto end
if "%2" == "nofonts" goto end
cd ..\hershey\src
make makefile.msc
if errorlevel > 0 goto end
md c:\lib\hershey
mkfnts c:\lib\hershey
:end
