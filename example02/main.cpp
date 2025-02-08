#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND handle_window, UINT uMsg, WPARAM wParam,
                                 LPARAM lParam) {
  // The minimum you have to include is the response for when the use click to
  // close window. Otherwise, he will need to Ctrl+Alt+Del and search for the
  // program to close (main.exe in this case). NOTE: The user will not be able
  // to delete/overwrite "main.exe" file will is running.
  switch (uMsg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }

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

  HWND handle_window =
      CreateWindowEx(0, CLASS_NAME, L"Window Title",
                     WS_OVERLAPPEDWINDOW

                         CW_USEDEFAULT,
                     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                     NULL, NULL, handle_instance, NULL);

  if (handle_window == NULL) {
    return 0;
  }

  ShowWindow(handle_window, nCmdShow);

  // Loop waiting for event messages.
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(
        &msg); // Translate keystrokes into characters (because you don't know
               // the OS language and the user keyboard layout).
    DispatchMessage(&msg); // Dispatch the message to your callback, in this
                           // case "WindowProcedure()".
  }

  return 0;
}
