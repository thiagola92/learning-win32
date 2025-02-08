// This macro is important, otherwise windows will attempt to use code that
// expect ANSI strings. All examples will work with unicode code.
#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

// Function called when an event happens in your window.
LRESULT CALLBACK WindowProcedure(HWND handle_window, UINT uMsg, WPARAM wParam,
                                 LPARAM lParam) {
  // Right now, let the default window procedure handle it.
  return DefWindowProc(handle_window, uMsg, wParam, lParam);
}

// After Windows instanciate a program for you, it will call your "wWinMain"
// function passing a bunch of parameters so you know more about your instance.
int WINAPI wWinMain(HINSTANCE handle_instance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  const wchar_t CLASS_NAME[] = L"Window Example";

  // Setup your window informations like:
  //	- Function to be called when an event happen
  //	- Instance identifier
  //	- String to identify your window
  WNDCLASS window_class = {};
  window_class.lpfnWndProc = WindowProcedure;
  window_class.hInstance = handle_instance;
  window_class.lpszClassName = CLASS_NAME;

  // We will register, each means that it will start executing,
  // but our code does nothing more... so it will end right after it.
  RegisterClass(&window_class);

  return 0;
}
