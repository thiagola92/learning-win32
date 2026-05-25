#include <ShObjIdl.h>
#include <ShlGuid.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <winnls.h>

#define SIZE 4096

HRESULT CreateLink() {
  // Minimum information to create a shortcut.
  const wchar_t *link_target = L"example.txt";
  const char *link_path = "shortcut.lnk";

  HRESULT handle_result; // For COM functions.
  int result;            // For normal functions.

  // Convert relative path to absolute path.
  wchar_t absolute_path[SIZE];
  result = GetFullPathNameW(link_target, SIZE, absolute_path, NULL);

  if (result == 0) {
    return GetLastError();
  }

  // Ensure that link path is in unicode.
  wchar_t unicode_path[MAX_PATH];
  result =
      MultiByteToWideChar(CP_ACP, 0, link_path, -1, unicode_path, MAX_PATH);

  if (result == 0) {
    return GetLastError();
  }

  // Start to create the shortcut.
  IShellLink *shell_link;     // Interface for Shell Link.
  IPersistFile *persist_file; // Interface for Persist File.

  handle_result = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                                   IID_IShellLink, (LPVOID *)&shell_link);

  if (!SUCCEEDED(handle_result)) {
    return handle_result;
  }

  shell_link->SetPath(absolute_path);

  handle_result =
      shell_link->QueryInterface(IID_IPersistFile, (LPVOID *)&persist_file);

  if (!SUCCEEDED(handle_result)) {
    shell_link->Release();
    return handle_result;
  }

  handle_result = persist_file->Save(unicode_path, TRUE);

  persist_file->Release();
  shell_link->Release();

  return handle_result;
}

int main() {
  HRESULT handle_result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

  if (SUCCEEDED(handle_result)) {
    handle_result = CreateLink();
  }

  CoUninitialize();

  return handle_result;
}