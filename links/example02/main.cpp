#include <ShObjIdl.h>
#include <ShlGuid.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <strsafe.h>
#include <winnls.h>

#define SIZE 4096

HRESULT CreateLink() {
  const char *link_path = "shortcut.lnk";
  HRESULT handle_result; // For COM functions.
  int result;            // For normal functions.

  // Ensure that link path is in unicode.
  wchar_t unicode_path[MAX_PATH];
  result =
      MultiByteToWideChar(CP_ACP, 0, link_path, -1, unicode_path, MAX_PATH);

  if (result == 0) {
    return GetLastError();
  }

  // Start to loading the shortcut.
  IShellLink *shell_link;     // Interface for Shell Link.
  IPersistFile *persist_file; // Interface for Persist File.

  handle_result = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                                   IID_IShellLink, (LPVOID *)&shell_link);

  if (!SUCCEEDED(handle_result)) {
    return handle_result;
  }

  handle_result =
      shell_link->QueryInterface(IID_IPersistFile, (LPVOID *)&persist_file);

  if (!SUCCEEDED(handle_result)) {
    shell_link->Release();
    return handle_result;
  }

  handle_result = persist_file->Load(unicode_path, STGM_READ);

  if (!SUCCEEDED(handle_result)) {
    persist_file->Release();
    shell_link->Release();
    return handle_result;
  }

  // Attempts to find out the link target (even if it was moved or renamed).
  handle_result = shell_link->Resolve(NULL, 0);

  if (!SUCCEEDED(handle_result)) {
    persist_file->Release();
    shell_link->Release();
    return handle_result;
  }

  // Get link target.
  wchar_t target_path[MAX_PATH];
  WIN32_FIND_DATA find_data;
  handle_result = shell_link->GetPath(target_path, MAX_PATH,
                                      (WIN32_FIND_DATA *)&find_data, 0);

  if (!SUCCEEDED(handle_result)) {
    persist_file->Release();
    shell_link->Release();
    return handle_result;
  }

  setlocale(LC_ALL, "");
  printf("%ls\n", target_path);

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