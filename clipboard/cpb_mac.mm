#include <nan.h>
#include <AppKit/AppKit.h>

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Array> fileArray = Nan::New<v8::Array>();

  NSPasteboard *pboard = [NSPasteboard generalPasteboard];

  // TODO Objective-C++ 自动引用回收问题
  // TODO NSPasteboardTypeFileURL 只支持 10.13 以及以后的版本，是否需要兼容之前的 NSFilenamesPboardType
  // TODO 返回的是 file 开头的 URL，需要在这里处理吧？
  // 目前总是单个路径
  NSString *fileURL = [pboard stringForType:NSPasteboardTypeFileURL];
  uint i = 0;

  if (fileURL != nil) {
    const char *szFilePath = [fileURL UTF8String];
    v8::Local<v8::String> tempPath = Nan::New<v8::String>(szFilePath).ToLocalChecked();
    Nan::Set(fileArray, i, tempPath);
  }

  info.GetReturnValue().Set(fileArray);
}


void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("getClipboardFiles").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(clipboard, Init)
