@echo off
echo Compiling AI Smart City Navigator...
g++ app.cpp "Data Base/files/Graph.cpp" "Data Base/files/Admin.cpp" "Data Base/files/User.cpp" "Data Base/files/Storage.cpp" -o app.exe

if %errorlevel% == 0 (
    echo Compilation successful!
    echo Running program...
    echo.
    app.exe
) else (
    echo Compilation failed!
    pause
)