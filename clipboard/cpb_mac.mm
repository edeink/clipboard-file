#include <nan.h>
#include <AppKit/AppKit.h>

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Array> fileArray = Nan::New<v8::Array>();

  NSPasteboard *pboard = [NSPasteboard generalPasteboard];

  // TODO Objective-C++ 自动引用回收问题
  // TODO NSPasteboardTypeFileURL 只支持 10.13 以及以后的版本，是否需要兼容之前的 NSFilenamesPboardType
  NSString *fileURL = [pboard stringForType:NSPasteboardTypeFileURL];
  NSString *fileName = [pboard stringForType:NSPasteboardTypeString];

  if (fileURL != nil) {
    const char *fileUtf8URL = [fileURL UTF8String];
    const char *fileUtf8Name = [fileName UTF8String];
    v8::Local<v8::String> tempPath = Nan::New<v8::String>(fileUtf8URL).ToLocalChecked();
    v8::Local<v8::String> tempName = Nan::New<v8::String>(fileUtf8Name).ToLocalChecked();
    Nan::Set(fileArray, 0, tempPath);
    Nan::Set(fileArray, 1, tempName);
  }

  info.GetReturnValue().Set(fileArray);
}


void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("getClipboardFiles").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(clipboard, Init)
