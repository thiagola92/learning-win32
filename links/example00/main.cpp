#include <ShObjIdl.h>
#include <ShlGuid.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>

int main() {
  // Any program that uses COM (Component Object Model) must initialize the COM
  // library using CoInitializeEx function (Component Object Initialize
  // Extended).
  //
  // NOTE: The original CoInitialize function is single thread only
  //        (not that we care in our example).
  //
  // NOTE: HRESULT originally was suppose to be a pointer so you can handle the
  //        result and every program could append their error. But it cost too
  //        much to let every program add their error, so it was decided to stay
  //        as number and the name was never adjusted...
  HRESULT handle_result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

  if (SUCCEEDED(handle_result)) {
    printf("COM library initialized.");
  }

  // Always uninitialize it.
  CoUninitialize();

  return handle_result;
}