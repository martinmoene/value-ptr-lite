@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -O2 -Wall -Wextra -Wconversion -Wsign-conversion -Wno-unused-parameter -Dlest_FEATURE_COLOURISE=0 -o value-ptr-lite.t.exe -I../include/nonstd value-ptr-lite.t.cpp value-ptr.t.cpp && value-ptr-lite.t.exe
@endlocal

