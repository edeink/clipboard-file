#include <nan.h>
#include <oleidl.h>
#include <comdef.h>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::wstring> GetPaths() {
  std::vector<std::wstring> path_list;
  // 打开剪切板
  if (::OpenClipboard(NULL))
  {
    HDROP hDrop = HDROP(::GetClipboardData(CF_HDROP));

    if (hDrop != NULL)
    {
      WCHAR szFilePathName[MAX_PATH + 1] = { 0 };
      
      UINT nNumOfFiles = DragQueryFileW(hDrop, 0xFFFFFFFF, NULL, 0);

      for (UINT nIndex = 0; nIndex < nNumOfFiles; ++nIndex)
      {
        // 获取文件名
        memset(szFilePathName, 0, sizeof(WCHAR)*(MAX_PATH + 1));
        DragQueryFileW(hDrop, nIndex, szFilePathName, MAX_PATH);

        path_list.push_back(szFilePathName);
      }
    }

    ::CloseClipboard();
  }

  return path_list;
}

// 转码：Unicode -> utf-8
char* UnicodeToUtf8(const wchar_t* unicode)
{
    int len;
    len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    char *szUtf8 = (char*)malloc(len + 1);
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
    return szUtf8;
}

// 转成V8所能识别的数据（作为JS调用的返回）
void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  std::vector<std::wstring> fileVec = GetPaths();
  v8::Local<v8::Array> fileArray = Nan::New<v8::Array>();

  for (int i=0; i<fileVec.size(); i++) {
    char *szFilePath = UnicodeToUtf8(fileVec[i].c_str());
    v8::Local<v8::String> tempPath = Nan::New<v8::String>(szFilePath).ToLocalChecked();
    Nan::Set(fileArray, i, tempPath);
    free(szFilePath);
  }

  info.GetReturnValue().Set(fileArray);
}

// 注册JS调用方法
void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("getClipboardFiles").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(clipboard, Init)
