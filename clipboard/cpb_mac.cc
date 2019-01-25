#include <nan.h>

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Array> fileArray = Nan::New<v8::Array>();

  info.GetReturnValue().Set(fileArray);
}


void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("getClipboardFiles").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(clipboard, Init)
