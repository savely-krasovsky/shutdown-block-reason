#include <iostream>

#include <napi.h>
#include <windows.h>
#include <winuser.h>

std::string GetLastErrorAsString() {
  DWORD dLastError = ::GetLastError();
  if (dLastError == 0) {
    return std::string();
  }

  LPSTR msg_buf = nullptr;
  size_t sz = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                               NULL, dLastError, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPSTR) & msg_buf, 0, NULL);
  std::string message(msg_buf, sz);
  LocalFree(msg_buf);

  return message;
}

Napi::Value Create(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    throw Napi::TypeError::New(env, "Wrong number of arguments");
  }

  if (!info[0].IsNumber() || !info[1].IsString()) {
    throw Napi::TypeError::New(env, "Wrong arguments");
  }

  HWND hWnd = reinterpret_cast<HWND>(info[0].As<Napi::Number>().Uint32Value());
  std::u16string u16reason = info[1].As<Napi::String>().Utf16Value();
  LPCWSTR reason = std::wstring(u16reason.begin(), u16reason.end()).c_str();

  // Perform the operation
  BOOL status = ::ShutdownBlockReasonCreate(hWnd, reason);
  if (status == FALSE) {
    throw Napi::TypeError::New(env, GetLastErrorAsString());
  }

  return env.Undefined();
}

Napi::Value Destroy(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    throw Napi::Error::New(env, "Wrong number of arguments");
  }

  if (!info[0].IsNumber()) {
    throw Napi::Error::New(env, "Wrong arguments");
  }

  HWND hWnd = reinterpret_cast<HWND>(info[0].As<Napi::Number>().Uint32Value());

  // Perform the operation
  BOOL status = ::ShutdownBlockReasonDestroy(hWnd);
  if (status == FALSE) {
    throw Napi::Error::New(env, GetLastErrorAsString());
  }

  return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "create"), Napi::Function::New(env, Create));
  exports.Set(Napi::String::New(env, "destroy"), Napi::Function::New(env, Destroy));
  return exports;
}

NODE_API_MODULE(addon, Init)
