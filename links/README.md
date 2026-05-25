# strings
I'm not going to use Windows macros, they make everything much more confuse to me.  

What you need to know:  
- `char` is [UTF-8](https://en.wikipedia.org/wiki/UTF-8)
    - On **Linux**
    - 8 bits
    - Compatible with [ASCII](https://en.wikipedia.org/wiki/ASCII)
- `char` is [ANSI](https://en.wikipedia.org/wiki/Windows_code_page)
    - On **Windows**
    - 8 bits
- `wchar_t` is [UTF-16](https://en.wikipedia.org/wiki/UTF-16)
    - Only exist on **Windows**
    - 16 bits
    - They call it "wide characters" to differ from classic characters

So instead of using the macros like PCWSTR (**P**ointer for a **C**onstant **W**ide **Str**ing), I will just use `const wchar_t*`. Which tells me everything that I want to know about the type without reading between the letters. 

# references
- https://learn.microsoft.com/en-us/windows/win32/learnwin32/initializing-the-com-library
- https://learn.microsoft.com/en-us/windows/win32/shell/links
- https://learn.microsoft.com/en-us/windows/win32/WinProg/windows-data-types
- https://learn.microsoft.com/en-us/windows/win32/learnwin32/working-with-strings