#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK LowLevelKeyboardProcedure(int number_code, WPARAM wParam,
	LPARAM lParam) {
	if (number_code == HC_ACTION) {
		KBDLLHOOKSTRUCT* keyboard_struct = (KBDLLHOOKSTRUCT*)lParam;

		if (wParam == WM_KEYDOWN) {
			printf("Virtual key code: %d\n", keyboard_struct->vkCode);
			printf("Scan code: %d\n", keyboard_struct->scanCode);
			printf("flags: %d\n", keyboard_struct->flags);
		}
		else if (wParam == WM_KEYUP) {
			// Funny fact: Alt key is only process when on release.
			printf("Virtual key code: %d\n", keyboard_struct->vkCode);
			printf("Scan code: %d\n", keyboard_struct->scanCode);
			printf("flags: %d\n", keyboard_struct->flags);
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
