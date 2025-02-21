#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK LowLevelKeyboardProcedure(int number_code, WPARAM wParam,
                                   LPARAM lParam) {
  printf("Hook action: %d\n", number_code);

  if (number_code == HC_ACTION) {
    KBDLLHOOKSTRUCT *keyboard_struct = (KBDLLHOOKSTRUCT *)lParam;

    if (wParam == WM_KEYDOWN) {
      printf("Key pressed: %d\n", keyboard_struct->vkCode);
    } else if (wParam == WM_KEYUP) {
      printf("Key release: %d\n", keyboard_struct->vkCode);
    }
  }

  return CallNextHookEx(NULL, number_code, wParam, lParam);
}

int main() {
  HHOOK handle_hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProcedure,
                                       GetModuleHandle(NULL), 0);

  if (!handle_hook) {
    printf("Error\n");
    return 0;
  }

  MSG msg;
  while (true) {
    PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
    // GetMessage() will block until a message arrive.
    // PeekMessage() is a non-blocking option to check (or consume) message.
  }

  UnhookWindowsHookEx(handle_hook);

  return 0;
}
