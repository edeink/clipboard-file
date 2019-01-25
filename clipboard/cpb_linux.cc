#include <nan.h>
// 转成V8所能识别的数据（作为JS调用的返回）
void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Array> fileArray = Nan::New<v8::Array>();

  info.GetReturnValue().Set(fileArray);
}

// 注册JS调用方法
void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("getClipboardFiles").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(clipboard, Init)
