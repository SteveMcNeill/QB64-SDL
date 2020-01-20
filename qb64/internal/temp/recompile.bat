@echo off
cd %0\..\
echo Recompiling...
cd ../c
.\bin\g -fstack-check -w -Wall -I.\i -I..\..\ -L.\l qbx.cpp libqbx.o -mconsole -mwindows .\i686-w64-mingw32\lib\libimm32.a -lwinspool -lmingw32 -ln -lmix -limg -lttf -lSDL -s -o "..\..\QB64(2).exe"
pause
