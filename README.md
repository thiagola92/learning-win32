# learning-win32
Visual Studio was used to write the examples (not VSCode).

## windows
Install through Visual Studio installer:
- MSVC (v143 - VS 2022 C++ x64/x86 build tools)

```shell
# Compiling using MSVC.
cl main.cpp /link User32.lib
```

## linux
```shell
# Install Mingw-w64.
sudo apt install mingw-w64

# Compiling using Clang.
clang --target=x86_64-w64-mingw32 -o main.exe main.cpp
```

## references
- https://learn.microsoft.com/en-us/windows/win32/
