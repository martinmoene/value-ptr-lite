@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -O2 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wno-unused-parameter -Dlest_FEATURE_COLOURISE=0 -o value_ptr-main.t.exe -I../include/nonstd value_ptr-main.t.cpp value_ptr.t.cpp && value_ptr-main.t.exe
@endlocal

