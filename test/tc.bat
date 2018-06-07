@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
clang -std=%std% -O2 -Wall -Wextra -Wno-unused-parameter -Dlest_FEATURE_COLOURISE=0 -o value_ptr-main.t.exe -I../include/nonstd value_ptr-main.t.cpp value_ptr.t.cpp && value_ptr-main.t.exe
@endlocal

