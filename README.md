# learning-win32
Os exemplos foram executados no Windows, utilizando Visual Studio (não o VSCode) pois garante que realmente tudo está funcionando.  

Nota: Para caso eu esteja no Linux e apenas queira ter certeza que tudo está compilando, adicionei a compilação no Linux.  

## windows install
Using Visual Studio installer:
- MSVC (v143 - VS 2022 C++ x64/x86 build tools)

## windows running
Compiling in Windows using `MSVC`:  
```
cl main.cpp /link User32.lib
```

## linux install
```
sudo apt install mingw-w64
```

## linux compiling
(Não testei para todos os casos e estou utilizando Clang)  

```
clang --target=x86_64-w64-mingw32 -o main.exe main.cpp
```

## references
- https://learn.microsoft.com/en-us/windows/win32/
- https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
- https://learn.microsoft.com/en-us/windows/win32/winmsg/using-hooks