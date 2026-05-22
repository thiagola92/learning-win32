#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK KeyboardProcedure(int number_code, WPARAM wParam,
                                   LPARAM lParam) {
  printf("Hook action: %d\n", number_code);

  if (number_code == HC_ACTION) {
      // First parameter is not about key pressed/release,
      // but is the virtual keycode.
      WORD virtual_keycode = LOWORD(wParam);

      // Second parameter is a bunch of flags that we will
      // need to extract information from using the AND operator.
      WORD key_flags = HIWORD(lParam);
      WORD repeat_count = LOWORD(lParam);
      WORD scan_code = LOBYTE(key_flags);
      BOOL is_extended_key = (key_flags & KF_EXTENDED) == KF_EXTENDED;
      BOOL is_alt_down = (key_flags & KF_ALTDOWN) == KF_ALTDOWN;
      BOOL was_key_down = (key_flags & KF_REPEAT) == KF_REPEAT;
      BOOL is_key_released = (key_flags & KF_UP) == KF_UP;


      printf("Virtual keycode: %d\n", virtual_keycode);
      printf("Repeat count: %d\n", repeat_count);
      printf("Scan code: %d\n", scan_code);
      printf("Is extended key: %d\n", is_extended_key);
      printf("Is alt down: %d\n", is_alt_down);
      printf("Was key down: %d\n", was_key_down);
      printf("Is key released: %d\n", is_key_released);
  }

  return CallNextHookEx(NULL, number_code, wParam, lParam);
}

int main() {
  // We were listen to low level keyboard inputs (WH_KEYBOARD_LL),
  // now we are going to listen to WH_KEYBOARD which is thread-local,
  // this means that it doesn't work globally and we need to pass GetCurrentThreadId().
  HHOOK handle_hook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProcedure,
                                       GetModuleHandle(NULL), GetCurrentThreadId());

  if (!handle_hook) {
    printf("Error\n");
    return 0;
  }

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    // Changed back to GetMessage()
  }

  UnhookWindowsHookEx(handle_hook);

  return 0;
}
