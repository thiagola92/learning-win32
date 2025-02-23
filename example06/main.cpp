#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK LowLevelKeyboardProcedure(int number_code, WPARAM wParam,
	LPARAM lParam) {
	if (number_code == HC_ACTION) {
		KBDLLHOOKSTRUCT* keyboard_struct = (KBDLLHOOKSTRUCT*)lParam;

		// WM_SYSKEYDOWN and WM_SYSKEYUP are used to detect system keys (like ALT key).
		// 
		// LLKHF_EXTENDED flag is used to check if is extended key, which means 
		// that is a key that already exist in the keyboard but this is a copy of it.
		// For example: CTRL and ALT keys from the right side of the keyboard.
		if (wParam == WM_KEYDOWN) {
			printf("-------- WM_KEYDOWN --------\n");
			printf("Virtual key code: %d\n", keyboard_struct->vkCode);
			printf("Scan code: %d\n", keyboard_struct->scanCode);
			printf("flags: %d\n", keyboard_struct->flags);
			printf("flag LLKHF_EXTENDED: %d\n", (keyboard_struct->flags & LLKHF_EXTENDED) == LLKHF_EXTENDED);
			printf("flag LLKHF_LOWER_IL_INJECTED: %d\n", (keyboard_struct->flags & LLKHF_LOWER_IL_INJECTED) == LLKHF_LOWER_IL_INJECTED);
			printf("flag LLKHF_INJECTED: %d\n", (keyboard_struct->flags & LLKHF_INJECTED) == LLKHF_INJECTED);
			printf("flag LLKHF_UP: %d\n", (keyboard_struct->flags & LLKHF_UP) == LLKHF_UP);
			printf("flag LLKHF_ALTDOWN: %d\n", (keyboard_struct->flags & LLKHF_ALTDOWN) == LLKHF_ALTDOWN);
		}
		else if (wParam == WM_KEYUP) {
			printf("-------- WM_KEYUP --------\n");
			printf("Virtual key code: %d\n", keyboard_struct->vkCode);
			printf("Scan code: %d\n", keyboard_struct->scanCode);
			printf("flags: %d\n", keyboard_struct->flags);
			printf("flag LLKHF_EXTENDED: %d\n", (keyboard_struct->flags & LLKHF_EXTENDED) == LLKHF_EXTENDED);
			printf("flag LLKHF_LOWER_IL_INJECTED: %d\n", (keyboard_struct->flags & LLKHF_LOWER_IL_INJECTED) == LLKHF_LOWER_IL_INJECTED);
			printf("flag LLKHF_INJECTED: %d\n", (keyboard_struct->flags & LLKHF_INJECTED) == LLKHF_INJECTED);
			printf("flag LLKHF_ALTDOWN: %d\n", (keyboard_struct->flags & LLKHF_ALTDOWN) == LLKHF_ALTDOWN);
			printf("flag LLKHF_UP: %d\n", (keyboard_struct->flags & LLKHF_UP) == LLKHF_UP);
		}
		else if (wParam == WM_SYSKEYDOWN) {
			printf("-------- WM_SYSKEYDOWN --------\n");
			printf("Virtual key code: %d\n", keyboard_struct->vkCode);
			printf("Scan code: %d\n", keyboard_struct->scanCode);
			printf("flags: %d\n", keyboard_struct->flags);
			printf("flag LLKHF_EXTENDED: %d\n", (keyboard_struct->flags & LLKHF_EXTENDED) == LLKHF_EXTENDED);
			printf("flag LLKHF_LOWER_IL_INJECTED: %d\n", (keyboard_struct->flags & LLKHF_LOWER_IL_INJECTED) == LLKHF_LOWER_IL_INJECTED);
			printf("flag LLKHF_INJECTED: %d\n", (keyboard_struct->flags & LLKHF_INJECTED) == LLKHF_INJECTED);
			printf("flag LLKHF_ALTDOWN: %d\n", (keyboard_struct->flags & LLKHF_ALTDOWN) == LLKHF_ALTDOWN);
			printf("flag LLKHF_UP: %d\n", (keyboard_struct->flags & LLKHF_UP) == LLKHF_UP);
		}
		else if (wParam == WM_SYSKEYUP) {
			printf("-------- WM_SYSKEYUP --------\n");
			printf("Virtual key code: %d\n", keyboard_struct->vkCode);
			printf("Scan code: %d\n", keyboard_struct->scanCode);
			printf("flags: %d\n", keyboard_struct->flags);
			printf("flag LLKHF_EXTENDED: %d\n", (keyboard_struct->flags & LLKHF_EXTENDED) == LLKHF_EXTENDED);
			printf("flag LLKHF_LOWER_IL_INJECTED: %d\n", (keyboard_struct->flags & LLKHF_LOWER_IL_INJECTED) == LLKHF_LOWER_IL_INJECTED);
			printf("flag LLKHF_INJECTED: %d\n", (keyboard_struct->flags & LLKHF_INJECTED) == LLKHF_INJECTED);
			printf("flag LLKHF_ALTDOWN: %d\n", (keyboard_struct->flags & LLKHF_ALTDOWN) == LLKHF_ALTDOWN);
			printf("flag LLKHF_UP: %d\n", (keyboard_struct->flags & LLKHF_UP) == LLKHF_UP);
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
	}

	UnhookWindowsHookEx(handle_hook);

	return 0;
}
