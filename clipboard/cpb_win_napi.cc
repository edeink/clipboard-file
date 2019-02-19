#include <node_api.h>
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

// n-api


napi_value GetFunction(napi_env env, napi_callback_info info) {
    napi_value array;
    std::vector<std::wstring> fileVec = GetPaths();
    napi_create_array_with_length(env, fileVec.size(), &array);
    for (int i=0; i<fileVec.size(); i++) {
      napi_value tempStr;
      const char* szFilePath = UnicodeToUtf8(fileVec[i].c_str());
      napi_create_string_utf8(env, szFilePath, strlen(szFilePath), &tempStr);
      napi_get_element(env, tempStr, i, &array);
    }
    return array;
    // napi_value test;
    // HDROP hDrop = HDROP(::GetClipboardData(CF_HDROP));
    // WCHAR szFilePathName[MAX_PATH + 1] = { 0 };
    // UINT nNumOfFiles = DragQueryFileW(hDrop, 0xFFFFFFFF, NULL, 0);
    // napi_get_boolean(env, hDrop == NULL, &test);
    // napi_create_int32(env, nNumOfFiles, &test);
    // napi_get_boolean(env, ::OpenClipboard(NULL), &test);
    // napi_create_string_utf8(env, 'hello', NAPI_AUTO_LENGTH, &test);
    // napi_create_int32(env, fileVec.size(), &test);
    // return test;
}

#define DECLARE_NAPI_METHOD(name, func)                          \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("getClipboardFiles", GetFunction);
  napi_define_properties(env, exports, 1, &desc);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
