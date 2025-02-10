#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK KeyboardProcedure(int number_code, WPARAM wParam,
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

// We can use the classic "main()" for hooks.
int main() {
  // Request a hook for keyboard, it return a hook handle linked to our
  // "KeyboardProcedure()".
  HHOOK handle_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProcedure,
                                       GetModuleHandle(NULL), 0);

  if (!handle_hook) {
    printf("Error\n");
    return 0;
  }

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    // We don't need to TranslateMessage() and DispatchMessage()
  }

  // Remove hook.
  UnhookWindowsHookEx(handle_hook);

  return 0;
}
