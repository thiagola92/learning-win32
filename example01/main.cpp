#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND handle_window, UINT uMsg, WPARAM wParam,
                                 LPARAM lParam) {
  return DefWindowProc(handle_window, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE handle_instance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  const wchar_t CLASS_NAME[] = L"Window Example";

  WNDCLASS window_class = {};
  window_class.lpfnWndProc = WindowProcedure;
  window_class.hInstance = handle_instance;
  window_class.lpszClassName = CLASS_NAME;

  RegisterClass(&window_class);

  // Create a window linked to this instance.
  HWND handle_window =
      CreateWindowEx(0,                   // Optional window styles
                     CLASS_NAME,          // Window class name
                     L"Window Title",     // Window title
                     WS_OVERLAPPEDWINDOW, // Window style

                     // Size and position.
                     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                     NULL,            // Parent window
                     NULL,            // Menu
                     handle_instance, // Instance handle
                     NULL             // Additional data
      );

  // Check if window was created.
  // NOTE: We don't print any message because when executing "./main.exe"
  // Windows start another instance and finish interacting with the current
  // terminal.
  if (handle_window == NULL) {
    return 0;
  }

  // Show window, but it will close because right after this we end our code.
  ShowWindow(handle_window, nCmdShow);

  return 0;
}
