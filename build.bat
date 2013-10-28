cd src
make F=%1 makefile.msc
if errorlevel > 0 goto end
cd ..\examples
make F=%1 makefile.msc
if errorlevel > 0 goto end
if "%2" == "nofonts" goto end
cd ..\hershey\src
make makefile.msc
if errorlevel > 0 goto end
md c:\lib\hershey
mkfnts c:\lib\hershey
:end
